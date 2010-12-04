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
*       demo_msg_server.c
*
*
*************************************************************************/
#include <stdio.h>
#include "support_suite/mcapid_support.h"
#include "mcapid.h"
#include "client_server_demo.h"

/************************************************************************
*
*   FUNCTION
*
*       MCAPID_Message_Server
*
*   DESCRIPTION
*
*       This function creates an endpoint, receives a specified
*       amount of data and deletes the endpoint.
*
*************************************************************************/
MCAPI_THREAD_ENTRY(MCAPID_Message_Server)
{
    int                 i;
    size_t              rx_len;
    MCAPID_STRUCT       *mcapi_struct = (MCAPID_STRUCT*)argv;
    char                buffer[MCAPI_DEMO_TX_LEN];

    /* Receive data from the other side of the connection. */
    for (i = 0; i < MCAPI_DEMO_TX_COUNT; i++)
    {
        /* Receive the data. */
        mcapi_msg_recv(mcapi_struct->local_endp, buffer, MCAPI_DEMO_TX_LEN,
                       &rx_len, &mcapi_struct->status);

        if (mcapi_struct->status != MCAPI_SUCCESS)
            break;

        MCAPID_Sleep(MCAPI_DEMO_RX_MSG_PAUSE);
    }

    /* Output the number of messages received */
    printf("MCAPID_Message_Server Messages Received:               %u\r\n", i);

    /* Set the state of the test to completed. */
    mcapi_struct->state = 0;

} /* MCAPID_Message_Server */
