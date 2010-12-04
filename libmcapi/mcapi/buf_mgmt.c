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



#include <openmcapi.h>

#if (MCAPI_ENABLE_LOOPBACK == 1)

extern MCAPI_BUF_QUEUE  MCAPI_Buf_Queue;
mcapi_uint32_t  MCAPI_Buf_Count = MCAPI_BUF_COUNT;

/*************************************************************************
*
*   FUNCTION
*
*       mcapi_recover_buffer
*
*   DESCRIPTION
*
*       Returns a buffer to the list of free buffers in the system.
*
*   INPUTS
*
*       *buffer                 Pointer to the buffer to return to
*                               the system.
*
*   OUTPUTS
*
*       None.
*
*************************************************************************/
void mcapi_recover_buffer(MCAPI_BUFFER *buffer)
{
    /* Return the transmission buffer to the respective deallocation
     * list.
     */
    mcapi_enqueue(&MCAPI_Buf_Queue, buffer);

    /* Increment the count of loopback buffers in the system. */
    MCAPI_Buf_Count ++;

}

/*************************************************************************
*
*   FUNCTION
*
*       mcapi_reserve_buffer
*
*   DESCRIPTION
*
*       Reserves a buffer from the free list of buffers for use in sending
*       or receiving data.
*
*   INPUTS
*
*       node_id                 The node ID of the destination of the
*                               buffer.
*       size                    The desired size of the buffer.
*
*   OUTPUTS
*
*       A pointer to the buffer that can be used by the caller, or
*       MCAPI_NULL if no buffers exist in the system.
*
*************************************************************************/
MCAPI_BUFFER *mcapi_reserve_buffer(mcapi_node_t node_id, size_t size,
                                   mcapi_uint32_t priority)
{
    MCAPI_BUFFER    *buffer;

    /* Get a buffer from the global buffer list. */
    buffer = mcapi_dequeue(&MCAPI_Buf_Queue);

    if (buffer)
    {
        /* Initialize the size to zero. */
        buffer->buf_size = 0;

        /* Decrement the count of buffers in the system. */
        MCAPI_Buf_Count --;
    }

    return (buffer);

}
#endif
