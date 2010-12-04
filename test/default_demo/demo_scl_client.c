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
*       demo_scl_client.c
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
*       MCAPID_Scalar_Channel_Client
*
*   DESCRIPTION
*
*       This function creates an endpoint and opens the endpoint as the
*       sending side of a scalar channel.  It then sends a specified
*       amount of data, closes the send side and deletes the endpoint.
*
*************************************************************************/
MCAPI_THREAD_ENTRY(MCAPID_Scalar_Channel_Client)
{
    int                 i;
    MCAPID_STRUCT       *mcapi_struct = (MCAPID_STRUCT*)argv;

    /* Send data to the other side of the connection. */
    for (i = 0; i < MCAPI_DEMO_TX_COUNT; i += 4)
    {
        /* Transmit an 8-bit scalar. */
        mcapi_sclchan_send_uint8(mcapi_struct->scl_tx_handle,
                                 MCAPI_DEMO_8BIT_SCALAR,
                                 &mcapi_struct->status);

        if (mcapi_struct->status != MCAPI_SUCCESS)
            break;

        MCAPID_Sleep(MCAPI_DEMO_TX_SCL_PAUSE);

        /* Transmit a 16-bit scalar. */
        mcapi_sclchan_send_uint16(mcapi_struct->scl_tx_handle,
                                  MCAPI_DEMO_16BIT_SCALAR,
                                  &mcapi_struct->status);

        if (mcapi_struct->status != MCAPI_SUCCESS)
            break;

        MCAPID_Sleep(MCAPI_DEMO_TX_SCL_PAUSE);

        /* Transmit a 32-bit scalar. */
        mcapi_sclchan_send_uint32(mcapi_struct->scl_tx_handle,
                                  MCAPI_DEMO_32BIT_SCALAR,
                                  &mcapi_struct->status);

        if (mcapi_struct->status != MCAPI_SUCCESS)
            break;

        MCAPID_Sleep(MCAPI_DEMO_TX_SCL_PAUSE);

        /* Transmit a 64-bit scalar. */
        mcapi_sclchan_send_uint64(mcapi_struct->scl_tx_handle,
                                  MCAPI_DEMO_64BIT_SCALAR,
                                  &mcapi_struct->status);

        if (mcapi_struct->status != MCAPI_SUCCESS)
            break;

        MCAPID_Sleep(MCAPI_DEMO_TX_SCL_PAUSE);
    }

    /* Output the number of scalars sent */
    printf("MCAPID_Scalar_Channel_Client Scalars Sent:             %u\r\n", i);

    /* Close the send side of the channel. */
    mcapi_sclchan_send_close_i(mcapi_struct->scl_tx_handle, &mcapi_struct->request,
                               &mcapi_struct->status);

    /* Set the state of the test to completed. */
    mcapi_struct->state = 0;

} /* MCAPID_Scalar_Channel_Client */
