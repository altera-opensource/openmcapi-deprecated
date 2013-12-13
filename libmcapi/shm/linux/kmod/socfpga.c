/*
 * Copyright (c) 2013, Altera Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the <ORGANIZATION> nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/smp.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/of_platform.h>
#include <linux/mailbox.h>
#include <linux/mailbox_client.h>
#include <linux/altera_hwmutex.h>
#include <asm/io.h>
#include <asm/pgtable.h>


#include "lock.h"
#include "mcomm.h"


#define CPU_ID_MASK 	(0x3)
#define LOCK   			(1)
#define NOTIFY			(1)
#define ALTR_SOFTIP_NAME_MAX_LEN	(32)
#define ALTR_MAILBOX_ELEMENT_LEN	(2)
#define ALTR_MAILBOX_CMD_IDX		(0)
#define ALTR_MAILBOX_PTR_IDX		(1)

struct device_node *dev_node = NULL;
static void *rx_ch = NULL;
static void *tx_ch = NULL;
static struct altera_mutex* lock_handles[LOCK_MAX_NUM];


static pgprot_t mcomm_socfpga_mmap_pgprot(struct vm_area_struct *vma)
{
	printk (KERN_DEBUG "%s\n", __func__);
	return  pgprot_noncached(vma->vm_page_prot);
}

static void __iomem *mcomm_socfpga_ioremap(unsigned long phys_addr, size_t size)
{
	printk (KERN_DEBUG "%s phyaddr = %08lx size = %x\n", __func__, phys_addr,
			size);
	return ioremap_nocache(phys_addr, size);
}


static void mcomm_socfpga_notify(u32 core_nr)
{
	request_token_t token;
	u32 data[ALTR_MAILBOX_ELEMENT_LEN];

	data[ALTR_MAILBOX_CMD_IDX] = NOTIFY;
	data[ALTR_MAILBOX_PTR_IDX] = core_nr;

	do {
		token = ipc_send_message(tx_ch, (void *)data);
	} while (!token);
}

static unsigned long mcomm_socfpga_cpuid(void)
{
    unsigned long cpuid;

    cpuid = smp_processor_id();
    printk (KERN_DEBUG "%s : %ld\n", __func__, cpuid);

    return cpuid;
}

static void mcomm_socfpga_lock(u32 lock_idx, u32 core_nr)
{
	unsigned int index = lock_idx;
	struct altera_mutex *plock = lock_handles[index];
	int ret;

	ret = altera_mutex_lock(plock, core_nr, LOCK);

	if (ret)
		printk (KERN_DEBUG "%s ret %d\n", __func__, ret);
}

static void mcomm_socfpga_unlock(u32 lock_idx, u32 core_nr)
{
	unsigned int index = lock_idx;
	struct altera_mutex *plock = lock_handles[index];
	int ret;

	ret = altera_mutex_unlock(plock, core_nr);

	if (ret)
		printk (KERN_DEBUG "%s ret %d\n", __func__, ret);
}

static struct mcomm_platform_ops mcomm_socfpga_ops = {
	.mmap_pgprot = mcomm_socfpga_mmap_pgprot,
	.map = mcomm_socfpga_ioremap,
	.notify = mcomm_socfpga_notify,
	.cpuid = mcomm_socfpga_cpuid,
	.lock = mcomm_socfpga_lock,
	.unlock = mcomm_socfpga_unlock,
};

void mcomm_socfpga_rx_mbox_cb(void *cl_id, void *mssg)
{
	u32 *data = (u32 *)mssg;

	/* Notification on receiving message */
	mcomm_mbox();
	printk (KERN_DEBUG "Mailbox received CMD 0x%x PTR 0x%x\n", data[0], data[1]);
}

static int mcomm_socfpga_probe(struct platform_device *pdev)
{
	struct device_node *np;
	struct resource *mem;
	struct resource irq;
	unsigned int int_mode = 0;
	int rc = 0;
	struct ipc_client mbox_rx;
	struct ipc_client mbox_tx;
	const char *mbox_name = NULL;
	char mutex_name[ALTR_SOFTIP_NAME_MAX_LEN];
	char mbox_rx_name[ALTR_SOFTIP_NAME_MAX_LEN];
	char mbox_tx_name[ALTR_SOFTIP_NAME_MAX_LEN];
	int i;

	printk (KERN_DEBUG "%s pdev = %x\n", __func__, (u32) pdev);

	/* Interrupt mechanism is using mailbox interrupt */
	irq.start = NO_IRQ;

	if (of_property_read_u32(pdev->dev.of_node, "int_mode", &int_mode)) {
		printk(KERN_DEBUG "Intercore interrupt disabled\n");
	}

	/* Mailbox receiver */
	mbox_rx.txcb = NULL;
	mbox_rx.rxcb = mcomm_socfpga_rx_mbox_cb;
	mbox_rx.cl_id = pdev;
	mbox_rx.tx_block = false;
	mbox_rx.tx_tout = 0;
	mbox_rx.link_data = NULL;
	mbox_rx.knows_txdone = false;

	/* Setup mailbox channel name */
	np = of_parse_phandle(pdev->dev.of_node, "mailbox-rx", 0);
	rc = of_property_read_string(np, "linux,mailbox-name", &mbox_name);
	if (rc) {
		printk(KERN_ERR "mailbox-rx name not found: %d\n", rc);
		return rc;
	}
	sprintf(mbox_rx_name, "%s:0", mbox_name);
	mbox_rx.chan_name = mbox_rx_name;

	rx_ch = ipc_request_channel(&mbox_rx);
	if (!rx_ch) {
		rc = -EBUSY;
		printk(KERN_ERR "Mailbox-RX setup failed: %d\n", rc);
		return rc;
	}

	/* Mailbox sender */
	mbox_tx.txcb = NULL;
	mbox_tx.rxcb = NULL;
	mbox_tx.cl_id = pdev;
	mbox_tx.tx_block = false;
	mbox_tx.tx_tout = 0;
	mbox_tx.link_data = NULL;
	mbox_tx.knows_txdone = false;

	/* Setup mailbox channel name */
	np = of_parse_phandle(pdev->dev.of_node, "mailbox-tx", 0);
	rc = of_property_read_string(np, "linux,mailbox-name", &mbox_name);
	if (rc) {
		printk(KERN_ERR "mailbox-rx name not found: %d\n", rc);
		goto put_mbox_rx;
	}
	sprintf(mbox_tx_name, "%s:0", mbox_name);
	mbox_tx.chan_name = mbox_tx_name;

	tx_ch = ipc_request_channel(&mbox_tx);
	if (!tx_ch) {
		rc = -EINVAL;
		printk(KERN_ERR "Mailbox-TX setup failed: %d\n", rc);
		goto put_mbox_rx;
	}

	/* init lock handle data structure */
	for (i = 0; i < LOCK_MAX_NUM; i++) {
		lock_handles[i] = NULL;
	}

	/* Get init-lock mutex phandle from device tree */
	np = of_parse_phandle(pdev->dev.of_node, "init-lock", 0);
	if (!np) {
		rc = -EINVAL;
		printk(KERN_ERR "init_lock phandle not found: %d\n", rc);
		goto put_mbox_tx;
	}

	/* Get mutex handle */
	lock_handles[INIT_LOCK] = altera_mutex_request(np);
	if (!lock_handles[INIT_LOCK]) {
		rc = -EINVAL;
		printk(KERN_ERR "init_lock request failed: %d\n", rc);
		goto put_mbox_tx;
	}

	/* Get bufq-lock mutex phandle from device tree */
	np = of_parse_phandle(pdev->dev.of_node, "bufq-lock", 0);
	if (!np) {
		rc = -EINVAL;
		printk(KERN_ERR "bufq_lock phandle not found: %d\n", rc);
		goto put_init_lock;
	}

	/* Get mutex handle */
	lock_handles[BUFQ_LOCK] = altera_mutex_request(np);
	if (!lock_handles[BUFQ_LOCK]) {
		rc = -EINVAL;
		printk(KERN_ERR "bufq_lock request failed: %d\n", rc);
		goto put_init_lock;
	}

	/* Get descq-lock mutex phandle from device tree */
	for (i = 0; i < DESCQ_LOCK_NUM; i++) {
		sprintf(mutex_name, "descq-lock-%d", i);
		np = of_parse_phandle(pdev->dev.of_node, mutex_name, 0);
		if (!np) {
			rc = -EINVAL;
			printk(KERN_ERR "descq_lock phandle not found: %d\n", rc);
			goto put_bufq_lock;
		}

		/* Get mutex handle */
		lock_handles[DESCQ_LOCK_BASE + i] = altera_mutex_request(np);
		if (!lock_handles[DESCQ_LOCK_BASE + i]) {
			rc = -EINVAL;
			printk(KERN_ERR "descq_lock request failed: %d\n", rc);
			goto put_descq_lock;
		}
	}

	if (pdev->resource->flags == IORESOURCE_MEM) {
		mem = pdev->resource;
	} else {
		printk (KERN_DEBUG "pdev : %x IO resource error\n", (u32) pdev);
		rc = -EINVAL;
		goto put_descq_lock;
	}
	printk(KERN_DEBUG "Got resource mem:%08x:%08x int_mode:%d\n",
		mem->start, mem->end, int_mode);

	rc = mcomm_new_region(&pdev->dev, mem, &irq, int_mode);

	if (rc)
		goto put_descq_lock;
	else
		return 0;

put_descq_lock:
	for (i = 0; i < DESCQ_LOCK_NUM; i++) {
		if (lock_handles[DESCQ_LOCK_BASE + i])
			altera_mutex_free(lock_handles[DESCQ_LOCK_BASE + i]);
	}
put_bufq_lock:
	altera_mutex_free(lock_handles[BUFQ_LOCK]);
put_init_lock:
	altera_mutex_free(lock_handles[INIT_LOCK]);
put_mbox_tx:
	ipc_free_channel(tx_ch);
put_mbox_rx:
	ipc_free_channel(rx_ch);

	return rc;
}

static int mcomm_socfpga_remove(struct platform_device *pdev)
{
	int i;
	mcomm_remove_region(&pdev->dev);
	ipc_free_channel(rx_ch);
	ipc_free_channel(tx_ch);

	for (i = 0; i < LOCK_MAX_NUM; i++) {
		altera_mutex_free(lock_handles[i]);
		lock_handles[i] = NULL;
	}

	return 0;
}

static const struct of_device_id mcomm_match_table[] = {
	{ .compatible	= "altr,mcomm", },
	{}
};

static struct platform_driver mcomm_driver = {
	.driver = {
		.name = "mcomm",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(mcomm_match_table),
	},

	.probe = mcomm_socfpga_probe,
	.remove = mcomm_socfpga_remove,
};

static int __init mcomm_socfpga_modinit(void)
{
	int rc;

	rc = mcomm_init(&mcomm_socfpga_ops, THIS_MODULE);
	if (rc) {
		printk(KERN_ERR "%s: mcomm_init failed.\n", __func__);
		goto out1;
	}

	rc = platform_driver_register(&mcomm_driver);
	if (rc) {
		printk(KERN_ERR "%s: failed to register platform driver.\n",
			__func__);
		goto out2;
	}

	return 0;

out2:
	mcomm_exit();
out1:
	return rc;
}
module_init(mcomm_socfpga_modinit);

static void mcomm_socfpga_modexit(void)
{
	mcomm_exit();
	return platform_driver_unregister(&mcomm_driver);
}
module_exit(mcomm_socfpga_modexit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Lee Booi Lim <lblim@altera.com>");
MODULE_DESCRIPTION("Altera SoCFPGA platform support for multi-core shared memory channel");

