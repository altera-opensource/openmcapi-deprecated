/*
 * Copyright (c) 2010, Mentor Graphics Corporation
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
#include "../shm.h"
#include "../shm_os.h"

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

typedef uint32_t mcomm_core_t;
typedef uint32_t mcomm_mbox_t;

/* Specify the layout of the mailboxes in shared memory */
#define MCOMM_INIT       _IOW('*', 0, struct mcomm_init_device)
/* All values in bytes */
struct mcomm_init_device {
    mcomm_mbox_t nr_mboxes;
    uint32_t offset; /* Offset from base of shared memory to first mailbox */
    uint32_t mbox_size;
    uint32_t mbox_stride; /* Offset from mailbox N to mailbox N+1 */
};

/* Get hardware-defined number for the current core */
#define MCOMM_CPUID      _IOR('*', 1, mcomm_core_t)

/* Block until data is available for specified mailbox */
#define MCOMM_WAIT_READ  _IOW('*', 2, mcomm_mbox_t)

/* Notify the specified core that data has been made available to it */
#define MCOMM_NOTIFY     _IOW('*', 3, mcomm_core_t)


static pthread_t shm_rx_thread;

/* XXX must close mcomm_fd somewhere */
static int mcomm_fd;
static size_t shm_bytes;

#define MCOMM_DEVICE "/dev/mcomm0"

static size_t shm_linux_read_size(void)
{
    unsigned long size;
    FILE *f;
    int rc;

    f = fopen("/sys/devices/platform/mcomm.0/size", "r");
    if (!f)
        f = fopen("/sys/devices/mcomm.0/size", "r");
    if (!f)
        return errno;

    rc = fscanf(f, "%lx", &size);
    if (rc < 0)
        size = errno;

    fclose(f);

    return size;
}

mcapi_status_t openmcapi_shm_notify(mcapi_uint32_t unitId)
{
    mcapi_status_t mcapi_status = MCAPI_SUCCESS;
    int rc;

    rc = ioctl(mcomm_fd, MCOMM_NOTIFY, &unitId);
    if (rc)
        mcapi_status = MCAPI_OS_ERROR;

    return mcapi_status;
}

mcapi_uint32_t openmcapi_shm_schedunitid(void)
{
    mcapi_uint32_t core_id;
    int rc;

    rc = ioctl(mcomm_fd, MCOMM_CPUID, &core_id);
    if (rc)
        return MCAPI_OS_ERROR;

    return core_id;
}

static int shm_linux_wait_notify(mcapi_uint32_t unitId)
{
    return ioctl(mcomm_fd, MCOMM_WAIT_READ, &unitId);
}

static int shm_linux_init_device(int fd)
{
    struct mcomm_init_device args;
    struct _shm_drv_mgmt_struct_ *mgmt = NULL;

    args.nr_mboxes = SMDRV_NODE_COUNT;
    args.offset = (unsigned int)&mgmt->shm_queues[0].count;
    args.mbox_size = sizeof(mgmt->shm_queues[0].count);
    args.mbox_stride = (void *)&mgmt->shm_queues[1].count -
                       (void *)&mgmt->shm_queues[0].count;

    return ioctl(fd, MCOMM_INIT, &args);
}

void *openmcapi_shm_map(void)
{
    void *shm;
    int fd;
    int rc;

    shm_bytes = shm_linux_read_size();
    if (shm_bytes <= 0) {
        perror("read shared memory size");
        return NULL;
    }

    fd = open(MCOMM_DEVICE, O_RDWR);
    if (fd < 0) {
        perror("open " MCOMM_DEVICE);
        goto out1;
    }

    /* Get the new file descriptor for the initialized device. */
    rc = shm_linux_init_device(fd);
    if (rc < 0) {
        perror("couldn't initialize device");
        goto out2;
    }

    mcomm_fd = rc;

    shm = mmap(NULL, shm_bytes, PROT_READ|PROT_WRITE, MAP_SHARED, mcomm_fd, 0);
    if (shm == MAP_FAILED) {
        perror("mmap shared memory");
        goto out3;
    }

    /* Don't need the original fd around any more. */
    close(fd);

    return shm;

out3:
    close(mcomm_fd);
out2:
    close(fd);
out1:
    return NULL;
}

static void *mcapi_receive_thread(void *data)
{
    int rc;

    do {
        /* Block until data for this node is available. */
        rc = shm_linux_wait_notify(MCAPI_Node_ID);
        if (rc < 0) {
            perror("wait ioctl");
            break;
        }

        /* Obtain lock so we can safely manipulate the RX_Queue. */
        MCAPI_Lock_RX_Queue();

        /* Process the incoming data. */
        shm_poll();

        MCAPI_Unlock_RX_Queue(0);

    } while (1);

    printf("%s exiting!\n", __func__);
    return NULL;
}

/* Now that SM_Mgmt_Blk has been initialized, we can start the RX thread. */
mcapi_status_t openmcapi_shm_os_init(void)
{
    mcapi_status_t mcapi_status = MCAPI_SUCCESS;
    int rc;

    rc = pthread_create(&shm_rx_thread, NULL, mcapi_receive_thread, NULL);
    if (rc) {
        perror("couldn't create pthread");
        mcapi_status = MCAPI_OS_ERROR;
    }

    return mcapi_status;
}

/* Finalize the SM driver OS specific layer. */
mcapi_status_t openmcapi_shm_os_finalize(void)
{
    mcapi_status_t mcapi_status = MCAPI_SUCCESS;
    int rc;

    rc = pthread_cancel(shm_rx_thread);
    if (rc) {
        perror("couldn't cancel thread");
        mcapi_status = MCAPI_OS_ERROR;
    }

    return mcapi_status;
}

void openmcapi_shm_unmap(void *shm)
{
    munmap(shm, shm_bytes);

    close(mcomm_fd);
}
