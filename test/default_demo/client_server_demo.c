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
*       demo.c
*
*
*************************************************************************/
#include <stdio.h>
#include "client_server_demo.h"
#include "support_suite/mcapid_support.h"
#include "mcapi_os.h"
#include "mcapid.h"

MCAPID_STRUCT       MCAPID_Reg_Struct;
MCAPID_STRUCT       MCAPID_Cli_Struct[3];
MCAPID_STRUCT       MCAPID_Srv_Struct[3];

/************************************************************************
*
*   FUNCTION
*
*       MCAPID_Test_Init
*
*   DESCRIPTION
*
*       Starts all demo threads and performs channel connection if
*       necessary.
*
*************************************************************************/
MCAPID_TEST_ENTRY(MCAPID_Test_Init)
{
    mcapi_status_t      status;
    mcapi_version_t     version;

    /* Initialize MCAPI on the node. */
    mcapi_initialize(MCAPI_LOCAL_NODE_ID, &version, &status);

    /* If an error occurred, the demo has failed. */
    if (status != MCAPI_SUCCESS)
        MCAPID_Finished();

#if (MCAPID_REG_SERVER_NODE == MCAPI_LOCAL_NODE_ID)

    /* Start the registration server. */
    MCAPID_Create_Thread(&MCAPID_Registration_Server, &MCAPID_Reg_Struct);

    /* Let the server come up. */
    MCAPID_Sleep(2000);

#endif

#if (MCAPI_RX_NODE_ID == MCAPI_LOCAL_NODE_ID)

    /* Set up the structure for the packet channel server. */
    memset(&MCAPID_Srv_Struct[0], 0, sizeof(MCAPID_STRUCT));
    MCAPID_Srv_Struct[0].type = MCAPI_CHAN_PKT_RX_TYPE;
    MCAPID_Srv_Struct[0].local_port = MCAPI_PORT_ANY;
    MCAPID_Srv_Struct[0].service = "mgc_default_demo_pkt_channel_comm";

    /* Set up the structure for the scalar channel server. */
    memset(&MCAPID_Srv_Struct[1], 0, sizeof(MCAPID_STRUCT));
    MCAPID_Srv_Struct[1].type = MCAPI_CHAN_SCL_RX_TYPE;
    MCAPID_Srv_Struct[1].local_port = MCAPI_PORT_ANY;
    MCAPID_Srv_Struct[1].service = "mgc_default_demo_scl_channel_comm";

    /* Set up the structure for the message server. */
    memset(&MCAPID_Srv_Struct[2], 0, sizeof(MCAPID_STRUCT));
    MCAPID_Srv_Struct[2].type = MCAPI_MSG_RX_TYPE;
    MCAPID_Srv_Struct[2].local_port = MCAPI_PORT_ANY;
    MCAPID_Srv_Struct[2].service = "mgc_default_demo_message_comm";

    /* Create the three server services. */
    MCAPID_Create_Service(MCAPID_Srv_Struct, 3);

    /* Start the packet channel server. */
    MCAPID_Create_Thread(&MCAPID_Packet_Channel_Server, &MCAPID_Srv_Struct[0]);

    /* Start the scalar channel server. */
    MCAPID_Create_Thread(&MCAPID_Scalar_Channel_Server, &MCAPID_Srv_Struct[1]);

    /* Start the message server. */
    MCAPID_Create_Thread(&MCAPID_Message_Server, &MCAPID_Srv_Struct[2]);

#endif

#if (MCAPI_TX_NODE_ID == MCAPI_LOCAL_NODE_ID)

    /* Set up the structure for the packet channel client. */
    memset(&MCAPID_Cli_Struct[0], 0, sizeof(MCAPID_STRUCT));
    MCAPID_Cli_Struct[0].type = MCAPI_CHAN_PKT_TX_TYPE;
    MCAPID_Cli_Struct[0].local_port = MCAPI_PORT_ANY;
    MCAPID_Cli_Struct[0].service = "mgc_default_demo_pkt_channel_comm";
    MCAPID_Cli_Struct[0].retry = 65535;

    /* Set up the structure for the scalar channel client. */
    memset(&MCAPID_Cli_Struct[1], 0, sizeof(MCAPID_STRUCT));
    MCAPID_Cli_Struct[1].type = MCAPI_CHAN_SCL_TX_TYPE;
    MCAPID_Cli_Struct[1].local_port = MCAPI_PORT_ANY;
    MCAPID_Cli_Struct[1].service = "mgc_default_demo_scl_channel_comm";
    MCAPID_Cli_Struct[1].retry = 65535;

    /* Set up the structure for the message client. */
    memset(&MCAPID_Cli_Struct[2], 0, sizeof(MCAPID_STRUCT));
    MCAPID_Cli_Struct[2].type = MCAPI_MSG_TX_TYPE;
    MCAPID_Cli_Struct[2].local_port = MCAPI_PORT_ANY;
    MCAPID_Cli_Struct[2].service = "mgc_default_demo_message_comm";
    MCAPID_Cli_Struct[2].retry = 65535;

    /* Create the three client services. */
    MCAPID_Create_Service(MCAPID_Cli_Struct, 3);

    /* Start the packet channel client. */
    MCAPID_Create_Thread(&MCAPID_Packet_Channel_Client, &MCAPID_Cli_Struct[0]);

    /* Start the scalar channel client. */
    MCAPID_Create_Thread(&MCAPID_Scalar_Channel_Client, &MCAPID_Cli_Struct[1]);

    /* Start the message client. */
    MCAPID_Create_Thread(&MCAPID_Message_Client, &MCAPID_Cli_Struct[2]);

#endif

#if (MCAPI_TX_NODE_ID == MCAPI_LOCAL_NODE_ID)
    /* Wait for each client thread to complete. */
    while ( (MCAPID_Cli_Struct[0].state != 0) ||
            (MCAPID_Cli_Struct[1].state != 0) ||
            (MCAPID_Cli_Struct[2].state != 0) )
    {
        MCAPID_Sleep(1000);
    }
#endif

#if (MCAPI_RX_NODE_ID == MCAPI_LOCAL_NODE_ID)
    /* Wait for each server thread to complete. */
    while ( (MCAPID_Srv_Struct[0].state != 0) ||
            (MCAPID_Srv_Struct[1].state != 0) ||
            (MCAPID_Srv_Struct[2].state != 0) )
    {
        MCAPID_Sleep(1000);
    }
#endif

    /* Clean up the demo threads. */
#if (MCAPI_TX_NODE_ID == MCAPI_LOCAL_NODE_ID)
    MCAPID_Cleanup(&MCAPID_Cli_Struct[0]);
    MCAPID_Cleanup(&MCAPID_Cli_Struct[1]);
    MCAPID_Cleanup(&MCAPID_Cli_Struct[2]);
#endif

#if (MCAPI_RX_NODE_ID == MCAPI_LOCAL_NODE_ID)
    MCAPID_Cleanup(&MCAPID_Srv_Struct[0]);
    MCAPID_Cleanup(&MCAPID_Srv_Struct[1]);
    MCAPID_Cleanup(&MCAPID_Srv_Struct[2]);
#endif

    printf("MCAPI Default Demonstration Complete\r\n");

    MCAPID_Finished();

} /* MCAPID_Test_Init */

