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

/************************************************************************
*
*   FILENAME
*
*       client_server_demo.h
*
*
*************************************************************************/

#include <mcapi.h>

/* Check to see if this file has been included already.  */
#ifndef _CLIENT_SERVER_DEMO_H_
#define _CLIENT_SERVER_DEMO_H_

/****** Begin User Configurable Section.  ******/
/****** These values must match on all nodes ******/

/* The node ID of this node. */
#define MCAPI_LOCAL_NODE_ID     0

/* The node IDs for the transmit and receive nodes. */
#define MCAPI_TX_NODE_ID        0
#define MCAPI_RX_NODE_ID        0

/* The pause between sending / receive packets in milliseconds. */
#define MCAPI_DEMO_TX_PKT_PAUSE 125
#define MCAPI_DEMO_RX_PKT_PAUSE 0
#define MCAPI_DEMO_TX_MSG_PAUSE 125
#define MCAPI_DEMO_RX_MSG_PAUSE 0
#define MCAPI_DEMO_TX_SCL_PAUSE 125
#define MCAPI_DEMO_RX_SCL_PAUSE 0

/* Default packet transmission size. */
#define MCAPI_DEMO_TX_LEN       1000

/* The number of packets to transmit from the client. */
#define MCAPI_DEMO_TX_COUNT     100

#define MCAPI_DEMO_8BIT_SCALAR  255
#define MCAPI_DEMO_16BIT_SCALAR 65535
#define MCAPI_DEMO_32BIT_SCALAR 2000000000
#define MCAPI_DEMO_64BIT_SCALAR 2000000000

/**** End User Configurable Section. */

MCAPI_THREAD_ENTRY(MCAPID_Message_Client);
MCAPI_THREAD_ENTRY(MCAPID_Packet_Channel_Client);
MCAPI_THREAD_ENTRY(MCAPID_Scalar_Channel_Client);
MCAPI_THREAD_ENTRY(MCAPID_Message_Server);
MCAPI_THREAD_ENTRY(MCAPID_Packet_Channel_Server);
MCAPI_THREAD_ENTRY(MCAPID_Scalar_Channel_Server);

#endif /* _CLIENT_SERVER_DEMO_H_ */
