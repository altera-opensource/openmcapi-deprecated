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

/*
*   FILENAME
*
*       demo_scl_server.c
*
*
*************************************************************************/
#include <stdio.h>
#include "support_suite/mcapid_support.h"
#include "client_server_demo.h"
#include "mcapid.h"

/************************************************************************
*
*   FUNCTION
*
*       MCAPID_Scalar_Channel_Server
*
*   DESCRIPTION
*
*       This function creates an endpoint and opens the endpoint as the
*       receiving side of a scalar channel.  It then receives a specified
*       amount of data, closes the receive side and deletes the endpoint.
*
*************************************************************************/
MCAPI_THREAD_ENTRY(MCAPID_Scalar_Channel_Server)
{
    size_t                      size;
    int                         i = 0;
    MCAPID_STRUCT               *mcapi_struct = (MCAPID_STRUCT*)argv;
    mcapi_uint8_t               scalar_8;
    mcapi_uint16_t              scalar_16;
    mcapi_uint32_t              scalar_32;
    mcapi_uint64_t              scalar_64;

    /* Wait for the connection to open completely. */
    mcapi_wait(&mcapi_struct->request, &size, &mcapi_struct->status,
               MCAPI_INFINITE);

    if (mcapi_struct->status == MCAPI_SUCCESS)
    {
        /* Receive data from the other side of the connection. */
        for (; i < MCAPI_DEMO_TX_COUNT; i += 4)
        {
            /* Receive an 8-bit scalar. */
            scalar_8 = mcapi_sclchan_recv_uint8(mcapi_struct->scl_rx_handle,
                                                &mcapi_struct->status);

            if ( (scalar_8 != MCAPI_DEMO_8BIT_SCALAR) ||
                 (mcapi_struct->status != MCAPI_SUCCESS) )
                break;

            MCAPID_Sleep(MCAPI_DEMO_RX_SCL_PAUSE);

            /* Receive a 16-bit scalar. */
            scalar_16 = mcapi_sclchan_recv_uint16(mcapi_struct->scl_rx_handle,
                                                  &mcapi_struct->status);

            if ( (scalar_16 != MCAPI_DEMO_16BIT_SCALAR) ||
                 (mcapi_struct->status != MCAPI_SUCCESS) )
                break;

            MCAPID_Sleep(MCAPI_DEMO_RX_SCL_PAUSE);

            /* Receive a 32-bit scalar. */
            scalar_32 = mcapi_sclchan_recv_uint32(mcapi_struct->scl_rx_handle,
                                                  &mcapi_struct->status);

            if ( (scalar_32 != MCAPI_DEMO_32BIT_SCALAR) ||
                 (mcapi_struct->status != MCAPI_SUCCESS) )
                break;

            MCAPID_Sleep(MCAPI_DEMO_RX_SCL_PAUSE);

            /* Receive a 64-bit scalar. */
            scalar_64 = mcapi_sclchan_recv_uint64(mcapi_struct->scl_rx_handle,
                                                  &mcapi_struct->status);

            if ( (scalar_64 != MCAPI_DEMO_64BIT_SCALAR) ||
                 (mcapi_struct->status != MCAPI_SUCCESS) )
                break;

            MCAPID_Sleep(MCAPI_DEMO_RX_SCL_PAUSE);
        }
    }

    /* Output the number of scalars received */
    printf("MCAPID_Scalar_Channel_Server Scalars Received:         %u\r\n", i);

    /* Close the receive side of the connection. */
    mcapi_sclchan_recv_close_i(mcapi_struct->scl_rx_handle, &mcapi_struct->request,
                               &mcapi_struct->status);

    /* Set the state of the test to completed. */
    mcapi_struct->state = 0;

} /* MCAPID_Scalar_Channel_Server */
