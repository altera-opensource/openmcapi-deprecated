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
#ifndef UCOSII_MCOMM_H
#define UCOSII_MCOMM_H

#include <mcapi.h>

#ifndef NO_IRQ
#define NO_IRQ  (-1)
#endif

/* Mask for MCAPI receive thread flag */
#define RX_TASK_CONDITION_SUSPEND	(0x1)


typedef uint32_t mcomm_mbox_t;

/* All values in bytes */
struct mcomm_init_device {
    uint32_t mbox_id;
    mcomm_mbox_t nr_mboxes;
    uint32_t offset; /* Offset from base of shared memory to first mailbox */
    uint32_t mbox_size;
    uint32_t mbox_stride; /* Offset from mailbox N to mailbox N+1 */
};

/* Get the ID of this unit */
extern mcapi_uint32_t ucosii_mcomm_cpuid(void);

/* Gate the base address of the shared memory */
extern void *ucosii_mcomm_mmap(void);

/* Send notification */
extern mcapi_status_t ucosii_mcomm_notify(mcapi_uint32_t core_nr);

/* Start the receive notifier */
extern mcapi_status_t ucosii_mcomm_init(OS_FLAG_GRP *flag,
	uint32_t mbox_mapped, struct mcomm_init_device args);

/* Stop the receive notifier */
extern mcapi_status_t ucosii_mcomm_stop(void);

#endif //UCOSII_MCOMM_H
