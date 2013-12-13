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
#include <mcapi.h>
#include <lock.h>
#include <config.h>
#include "../shm.h"
#include "../shm_os.h"
#include "ucosii_mcomm.h"

OS_FLAG_GRP *mcapi_receive_thread_flag = NULL;
static OS_STK    shm_rx_stack[MCAPI_TASK_STACK_SIZE];
static struct mcomm_init_device mbox_args;
static uint32_t mbox_mapped = 0;


mcapi_status_t openmcapi_shm_lock_init(SHM_MGMT_BLOCK *SHM_Mgmt_Blk)
{
	int i;

	SHM_Mgmt_Blk->shm_init_lock = (shm_lock) INIT_LOCK;
	SHM_Mgmt_Blk->shm_buff_mgmt_blk.lock = (shm_lock) BUFQ_LOCK;

	for (i = 0; i < DESCQ_LOCK_NUM; i++) {
		SHM_Mgmt_Blk->shm_queues[i].lock = DESCQ_LOCK_BASE + i;
	}

	return MCAPI_SUCCESS;
}

mcapi_status_t openmcapi_shm_lock(shm_lock *lock, mcapi_uint32_t node_id)
{
    return ucosii_mcomm_lock(*lock);
}

mcapi_status_t openmcapi_shm_unlock(shm_lock *lock, mcapi_uint32_t node_id)
{
    return ucosii_mcomm_unlock(*lock);
}

mcapi_status_t openmcapi_shm_notify(mcapi_uint32_t unit_id,
                                    mcapi_uint32_t node_id)
{
	if (!UCOSII_MCAPI_MCOMM_MODE_INT)
		return MCAPI_SUCCESS;

	return ucosii_mcomm_notify(unit_id);
}

mcapi_uint32_t openmcapi_shm_schedunitid(void)
{
	return ucosii_mcomm_cpuid();
}

static int shm_ucosii_wait_notify(void)
{
	INT8U status = -1;

	if (!UCOSII_MCAPI_MCOMM_MODE_INT)
		return 0;

	if (mcapi_receive_thread_flag)
		OSFlagPend(mcapi_receive_thread_flag,
			RX_TASK_CONDITION_SUSPEND,
			OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME,
			0, &status);

	return status;
}

void *openmcapi_shm_map(void)
{
	struct _shm_drv_mgmt_struct_ *mgmt = NULL;
	INT8U status;

	/* Initialize the task condition variable with default parameters. */
	mcapi_receive_thread_flag = OSFlagCreate(0, &status);

	if (mcapi_receive_thread_flag == NULL)
		goto fail;

	mbox_args.mbox_id = openmcapi_shm_schedunitid();
	mbox_args.nr_mboxes = CONFIG_SHM_NR_NODES;
	mbox_args.offset = (uint32_t)&mgmt->shm_queues[0].count;
	mbox_args.mbox_size = sizeof(mgmt->shm_queues[0].count);
	mbox_args.mbox_stride = (void *)&mgmt->shm_queues[1].count -
				(void *)&mgmt->shm_queues[0].count;

	mbox_mapped = (uint32_t)ucosii_mcomm_mmap();

	if (ucosii_mcomm_init(mcapi_receive_thread_flag, mbox_mapped, mbox_args)
		!= MCAPI_SUCCESS) {
		OSFlagDel(mcapi_receive_thread_flag,
			OS_DEL_ALWAYS, &status);

		mbox_mapped = 0;
	}

fail:
	return (void *)mbox_mapped;
}

static void mcapi_receive_thread(void *data)
{
	for (;;){
		/* Block until data for this node is available if in interrupt
		 * mode */
		shm_ucosii_wait_notify();

		/* Obtain lock so we can safely manipulate the RX_Queue. */
		MCAPI_Lock_RX_Queue();

		/* Process the incoming data. */
		shm_poll();

		MCAPI_Unlock_RX_Queue(0);
	}
}

/* Now that SM_Mgmt_Blk has been initialized, we can start the RX thread. */
mcapi_status_t openmcapi_shm_os_init(void)
{
#if (OS_TASK_NAME_EN > 0u)
	CPU_INT08U  os_err;
#endif
	INT8U status;



	status  = OSTaskCreate(mcapi_receive_thread, NULL,
			&shm_rx_stack[MCAPI_TASK_STACK_SIZE-1],
			MCAPI_RX_TASK_PRIO);

	if (status != OS_ERR_NONE) {
		 OSFlagDel(mcapi_receive_thread_flag,
			OS_DEL_ALWAYS, &status);
		mcapi_receive_thread_flag = NULL;

		return MCAPI_OS_ERROR;
	}

#if (OS_TASK_NAME_EN > 0u)
	OSTaskNameSet(MCAPI_RX_TASK_PRIO, (INT8U *)"mcapi_receive_thread",
		&os_err);
#endif

	return MCAPI_SUCCESS;
}



/* Finalize the SM driver OS specific layer. */
mcapi_status_t openmcapi_shm_os_finalize(void)
{
	INT8U status;

	OSTaskDel(MCAPI_RX_TASK_PRIO);



	if (mcapi_receive_thread_flag)
		OSFlagDel(mcapi_receive_thread_flag,
			OS_DEL_ALWAYS, &status);

	if (status)
		return MCAPI_OS_ERROR;

	return MCAPI_SUCCESS;
}

void openmcapi_shm_unmap(void *shm)
{
	ucosii_mcomm_stop();
}

