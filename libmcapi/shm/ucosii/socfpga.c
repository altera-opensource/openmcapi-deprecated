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
#include <stdint.h>
#include <stdio.h>
#include "config.h"
#include "mcapi.h"
#include "ucosii_mcomm.h"
#include "ucos_ii.h"
#include "lock.h"
#include "altera_avalon_mutex.h"
#include "altera_avalon_mailbox_simple.h"


#define CPU_ID_MASK 	(0x3)
#define LOCK   			(1)
#define NOTIFY			(1)
#define NO_TIMEOUT		(0)
#define ALTR_MAILBOX_ELEMENT_LEN	(2)
#define ALTR_MAILBOX_CMD_IDX		(0)
#define ALTR_MAILBOX_PTR_IDX		(1)
#define BYPASS_DCACHE_MASK   (0x1 << 31)
/* Hard code for window bridge mapping
 * ToDo: Need to be replaced when BSP editor expose this definition in BSP
 */
#define ADDRESS_SPAN_EXTENDER_NIOS2SDRAM1G_RESET_MAP     (0x30000000)

/* Need to increase number of mutex (descqlock) if more than 2 MCAPI nodes
 * are supported
 */
char descqlock[DESCQ_LOCK_NUM][100] = {
		UCOSII_MCAPI_MCOMM_DESQ_LOCK0,
		UCOSII_MCAPI_MCOMM_DESQ_LOCK1};

OS_FLAG_GRP *rx_thread_flag = NULL;
static altera_avalon_mailbox_dev* mbox_rx = NULL;
static altera_avalon_mailbox_dev* mbox_tx = NULL;
static alt_mutex_dev* lock_handles[LOCK_MAX_NUM];

struct mcomm_devdata {
	INT32U mbox_id;
	INT32U mbox_mapped;
	INT32U irq;
	INT32U int_mode;
	INT32U nr_mboxes;
	INT32U mbox_size;
	INT32U mbox_stride;
};

/* Only supports a single mcomm region. */
static struct mcomm_devdata _mcomm_devdata;

/* Get the ID of this unit */
mcapi_uint32_t ucosii_mcomm_cpuid()
{
    unsigned long cpuid;
	NIOS2_READ_CPUID(cpuid);

    return cpuid;
}

/* Gate the base address of the shared memory */
void *ucosii_mcomm_mmap(){
	unsigned int mcomm_base;
	unsigned int offset;
	/* Convert mcomm base address into addr seeing by Nios-II through
	 * address span extender; now default to upper 256M */
	offset = UCOSII_MCAPI_MCOMM_PHYS_BASE
			 - ADDRESS_SPAN_EXTENDER_NIOS2SDRAM1G_RESET_MAP;
	mcomm_base = ADDRESS_SPAN_EXTENDER_NIOS2SDRAM1G_BASE + offset;

	/* Set bit 31 of address to bypass D-cache */
	mcomm_base =  mcomm_base | BYPASS_DCACHE_MASK;
	return (void *)mcomm_base;
}

static void
ucosii_mcomm_mbox(void *arg)
{
	struct mcomm_devdata *devdata = &_mcomm_devdata;
	INT32U *mbox = (INT32U *) (devdata->mbox_mapped +
				(devdata->mbox_stride * devdata->mbox_id));

	INT32U active = 0;
	INT8U activeb = 0;
	INT8U status;

	OSIntEnter();

	if (devdata->mbox_size == 1) {
		activeb = (INT8U) *mbox;
	} else if (devdata->mbox_size == 4) {
		active = *mbox;
	}

	if (activeb || active)
		OSFlagPost(rx_thread_flag,
				RX_TASK_CONDITION_SUSPEND,
				OS_FLAG_SET,
				&status);

	OSIntExit();
}

/* Send notification */
mcapi_status_t ucosii_mcomm_notify(mcapi_uint32_t core_nr)
{
	mcapi_uint32_t cpuid = ucosii_mcomm_cpuid();
	INT32U data[ALTR_MAILBOX_ELEMENT_LEN];
	INT8U status;
	int ret;

	/* If the target is a local core, call the interrupt handler directly */
	if (core_nr == cpuid) {
		ucosii_mcomm_mbox(NULL);
	} else {
		data[ALTR_MAILBOX_CMD_IDX] = NOTIFY;
		data[ALTR_MAILBOX_PTR_IDX] = core_nr;

		do {
			ret = altera_avalon_mailbox_send(mbox_tx,
					(void *)data, NO_TIMEOUT, ISR);
		} while (ret);
	}

	return MCAPI_SUCCESS;
}

/* Lock resource using mutex */
mcapi_status_t ucosii_mcomm_lock(uint32_t lock_idx)
{
	INT32U index = lock_idx;
	alt_mutex_dev *plock = lock_handles[index];
	int ret;

	altera_avalon_mutex_lock(plock, LOCK);

	return MCAPI_SUCCESS;
}

mcapi_status_t ucosii_mcomm_unlock(uint32_t lock_idx)
{
	INT32U index = lock_idx;
	alt_mutex_dev *plock = lock_handles[index];
	int ret;

	altera_avalon_mutex_unlock(plock);

	return MCAPI_SUCCESS;
}


void rx_callback(void *message)
{
	/* Notification on receiving message */
	ucosii_mcomm_mbox(NULL);
}


/* Register interrupt handler for uC/OS-II mcomm driver */
mcapi_status_t ucosii_mcomm_init(OS_FLAG_GRP *flag,
	uint32_t mbox_mapped, struct mcomm_init_device args)
{
	struct mcomm_devdata *devdata = &_mcomm_devdata;
	int i;

	rx_thread_flag = flag;

	devdata->mbox_mapped = mbox_mapped + args.offset;
	devdata->mbox_id = args.mbox_id;
	devdata->mbox_size = args.mbox_size;
	devdata->mbox_stride = args.mbox_stride;
	devdata->nr_mboxes = args.nr_mboxes;

	/* Setup receiver mailbox */
	mbox_rx = altera_avalon_mailbox_open(UCOSII_MCAPI_MCOMM_MBOX_RX,
			NULL, rx_callback);

	/* Setup sender mailbox */
	mbox_tx = altera_avalon_mailbox_open(UCOSII_MCAPI_MCOMM_MBOX_TX,
			NULL, NULL);

	/* init lock handle data structure */
	for (i = 0; i < LOCK_MAX_NUM; i++) {
		lock_handles[i] = NULL;
	}

	/* Get mutex handle */
	lock_handles[INIT_LOCK]
		= altera_avalon_mutex_open(UCOSII_MCAPI_INIT_LOCK);
	if (!lock_handles[INIT_LOCK]) {
		printf("init_lock request failed\n");
		goto put_mbox_tx;
	}

	/* Get mutex handle */
	lock_handles[BUFQ_LOCK]
		= altera_avalon_mutex_open(UCOSII_MCAPI_MCOMM_BUFQ_LOCK);
	if (!lock_handles[BUFQ_LOCK]) {
		printf("bufq_lock request failed\n");
		goto put_init_lock;
	}

	for (i = 0; i < DESCQ_LOCK_NUM; i++) {
		lock_handles[DESCQ_LOCK_BASE + i]
			= altera_avalon_mutex_open(descqlock[i]);
		if (!lock_handles[DESCQ_LOCK_BASE + i]) {
			printf("descq_lock request failed\n");
			goto put_descq_lock;
		}
	}

	return MCAPI_SUCCESS;

put_descq_lock:
	for (i = 0; i < DESCQ_LOCK_NUM; i++) {
		if (lock_handles[DESCQ_LOCK_BASE + i])
			altera_avalon_mutex_close(
				lock_handles[DESCQ_LOCK_BASE + i]);
	}
put_bufq_lock:
	altera_avalon_mutex_close(lock_handles[BUFQ_LOCK]);
put_init_lock:
	altera_avalon_mutex_close(lock_handles[INIT_LOCK]);
put_mbox_tx:
	altera_avalon_mailbox_close(mbox_tx);
put_mbox_rx:
	altera_avalon_mailbox_close(mbox_rx);

	return MCAPI_ENO_INIT;
}

/* Unregister interrupt handler for uC/OS-II mcomm driver */
mcapi_status_t ucosii_mcomm_stop(void)
{
	int i;
	rx_thread_flag = NULL;

	altera_avalon_mailbox_close(mbox_rx);
	altera_avalon_mailbox_close(mbox_tx);

	for (i = 0; i < LOCK_MAX_NUM; i++) {
		altera_avalon_mutex_close(lock_handles[i]);
		lock_handles[i] = NULL;
	}

	return MCAPI_SUCCESS;
}
