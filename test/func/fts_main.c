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
*       fts_main.c
*
*
*************************************************************************/
#include <stdio.h>
#include <mcapi.h>
#include "fts_defs.h"
#include "support_suite/mcapid_support.h"
#include "mcapid.h"

MCAPID_USER_STRUCT MCAPI_FTS_User_Services[MCAPID_FTS_COUNT] =
{
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.3.1", MCAPI_FTS_Tx_2_3_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.3.2", MCAPI_FTS_Tx_2_3_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.3.3", MCAPI_FTS_Tx_2_3_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.4.1", MCAPI_FTS_Tx_2_4_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.4.2", MCAPI_FTS_Tx_2_4_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.4.3", MCAPI_FTS_Tx_2_4_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.5.1", MCAPI_FTS_Tx_2_5_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.5.2", MCAPI_FTS_Tx_2_5_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.6.1", MCAPI_FTS_Tx_2_6_1},
    {MCAPI_CHAN_PKT_TX_TYPE, MCAPI_PORT_ANY, "pkt_svr", 0xffffffff, "2.6.2", MCAPI_FTS_Tx_2_6_2},
    {MCAPI_CHAN_SCL_TX_TYPE, MCAPI_PORT_ANY, "scl_svr", 0xffffffff, "2.6.3", MCAPI_FTS_Tx_2_6_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.6.4", MCAPI_FTS_Tx_2_6_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.6.5", MCAPI_FTS_Tx_2_6_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.7.1", MCAPI_FTS_Tx_2_7_1},
    {MCAPI_CHAN_PKT_TX_TYPE, MCAPI_PORT_ANY, "pkt_svr", 0xffffffff, "2.7.2", MCAPI_FTS_Tx_2_7_2},
    {MCAPI_CHAN_PKT_TX_TYPE, MCAPI_PORT_ANY, "pkt_svr", 0xffffffff, "2.7.3", MCAPI_FTS_Tx_2_7_3},
    {MCAPI_CHAN_PKT_TX_TYPE, MCAPI_PORT_ANY, "pkt_svr", 0xffffffff, "2.7.4", MCAPI_FTS_Tx_2_7_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.8.1", MCAPI_FTS_Tx_2_8_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "msg_echo_svr", 0xffffffff, "2.9.1", MCAPI_FTS_Tx_2_9_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.9.2", MCAPI_FTS_Tx_2_9_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.9.3", MCAPI_FTS_Tx_2_9_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "msg_echo_svr", 0xffffffff, "2.10.1", MCAPI_FTS_Tx_2_10_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.10.2", MCAPI_FTS_Tx_2_10_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.10.3", MCAPI_FTS_Tx_2_10_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.11.1", MCAPI_FTS_Tx_2_11_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.11.2", MCAPI_FTS_Tx_2_11_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.11.3", MCAPI_FTS_Tx_2_11_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.12.1", MCAPI_FTS_Tx_2_12_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.12.2", MCAPI_FTS_Tx_2_12_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.12.3", MCAPI_FTS_Tx_2_12_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.13.1", MCAPI_FTS_Tx_2_13_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.13.2", MCAPI_FTS_Tx_2_13_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.13.3", MCAPI_FTS_Tx_2_13_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.1", MCAPI_FTS_Tx_2_14_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.2", MCAPI_FTS_Tx_2_14_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.3", MCAPI_FTS_Tx_2_14_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.4", MCAPI_FTS_Tx_2_14_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.5", MCAPI_FTS_Tx_2_14_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.6", MCAPI_FTS_Tx_2_14_6},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.7", MCAPI_FTS_Tx_2_14_7},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.8", MCAPI_FTS_Tx_2_14_8},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.9", MCAPI_FTS_Tx_2_14_9},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.10", MCAPI_FTS_Tx_2_14_10},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.11", MCAPI_FTS_Tx_2_14_11},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.12", MCAPI_FTS_Tx_2_14_12},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.13", MCAPI_FTS_Tx_2_14_13},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.14", MCAPI_FTS_Tx_2_14_14},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.14.15", MCAPI_FTS_Tx_2_14_15},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.15.1", MCAPI_FTS_Tx_2_15_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.15.2", MCAPI_FTS_Tx_2_15_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.15.3", MCAPI_FTS_Tx_2_15_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.15.4", MCAPI_FTS_Tx_2_15_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.15.5", MCAPI_FTS_Tx_2_15_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.16.1", MCAPI_FTS_Tx_2_16_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.16.2", MCAPI_FTS_Tx_2_16_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.16.3", MCAPI_FTS_Tx_2_16_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.16.4", MCAPI_FTS_Tx_2_16_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "pkt_svr", 0xffffffff, "2.16.5", MCAPI_FTS_Tx_2_16_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "pkt_svr", 0xffffffff, "2.17.1", MCAPI_FTS_Tx_2_17_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "pkt_svr", 0xffffffff, "2.17.2", MCAPI_FTS_Tx_2_17_2},
    {MCAPI_CHAN_PKT_TX_TYPE, MCAPI_PORT_ANY, "pkt_svr", 0xffffffff, "2.17.3", MCAPI_FTS_Tx_2_17_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "pkt_svr", 0xffffffff, "2.18.1", MCAPI_FTS_Tx_2_18_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "pkt_svr", 0xffffffff, "2.18.2", MCAPI_FTS_Tx_2_18_2},
    {MCAPI_CHAN_PKT_TX_TYPE, MCAPI_PORT_ANY, "pkt_svr", 0xffffffff, "2.18.3", MCAPI_FTS_Tx_2_18_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.19.1", MCAPI_FTS_Tx_2_19_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.19.2", MCAPI_FTS_Tx_2_19_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.19.3", MCAPI_FTS_Tx_2_19_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.20.1", MCAPI_FTS_Tx_2_20_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.20.2", MCAPI_FTS_Tx_2_20_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.20.3", MCAPI_FTS_Tx_2_20_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.21.1", MCAPI_FTS_Tx_2_21_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.21.2", MCAPI_FTS_Tx_2_21_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.21.3", MCAPI_FTS_Tx_2_21_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.22.1", MCAPI_FTS_Tx_2_22_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.22.2", MCAPI_FTS_Tx_2_22_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.22.3", MCAPI_FTS_Tx_2_22_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.23.1", MCAPI_FTS_Tx_2_23_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.23.2", MCAPI_FTS_Tx_2_23_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.23.3", MCAPI_FTS_Tx_2_23_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.23.4", MCAPI_FTS_Tx_2_23_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.23.5", MCAPI_FTS_Tx_2_23_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.23.6", MCAPI_FTS_Tx_2_23_6},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.23.7", MCAPI_FTS_Tx_2_23_7},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.24.1", MCAPI_FTS_Tx_2_24_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.24.2", MCAPI_FTS_Tx_2_24_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.24.3", MCAPI_FTS_Tx_2_24_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.24.4", MCAPI_FTS_Tx_2_24_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.24.5", MCAPI_FTS_Tx_2_24_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.24.6", MCAPI_FTS_Tx_2_24_6},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.24.7", MCAPI_FTS_Tx_2_24_7},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.1", MCAPI_FTS_Tx_2_25_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.2", MCAPI_FTS_Tx_2_25_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.3", MCAPI_FTS_Tx_2_25_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.4", MCAPI_FTS_Tx_2_25_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.5", MCAPI_FTS_Tx_2_25_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.6", MCAPI_FTS_Tx_2_25_6},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.7", MCAPI_FTS_Tx_2_25_7},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.8", MCAPI_FTS_Tx_2_25_8},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.9", MCAPI_FTS_Tx_2_25_9},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.10", MCAPI_FTS_Tx_2_25_10},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.11", MCAPI_FTS_Tx_2_25_11},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.12", MCAPI_FTS_Tx_2_25_12},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.13", MCAPI_FTS_Tx_2_25_13},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.14", MCAPI_FTS_Tx_2_25_14},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.25.15", MCAPI_FTS_Tx_2_25_15},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.26.1", MCAPI_FTS_Tx_2_26_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.26.2", MCAPI_FTS_Tx_2_26_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.26.3", MCAPI_FTS_Tx_2_26_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.26.4", MCAPI_FTS_Tx_2_26_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.26.5", MCAPI_FTS_Tx_2_26_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.27.1", MCAPI_FTS_Tx_2_27_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.27.2", MCAPI_FTS_Tx_2_27_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.27.3", MCAPI_FTS_Tx_2_27_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.27.4", MCAPI_FTS_Tx_2_27_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "scl_svr", 0xffffffff, "2.27.5", MCAPI_FTS_Tx_2_27_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "scl_svr", 0xffffffff, "2.28.1", MCAPI_FTS_Tx_2_28_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "scl_svr", 0xffffffff, "2.28.2", MCAPI_FTS_Tx_2_28_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.29.1", MCAPI_FTS_Tx_2_29_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.29.2", MCAPI_FTS_Tx_2_29_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.29.3", MCAPI_FTS_Tx_2_29_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.30.1", MCAPI_FTS_Tx_2_30_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.30.2", MCAPI_FTS_Tx_2_30_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.30.3", MCAPI_FTS_Tx_2_30_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.31.1", MCAPI_FTS_Tx_2_31_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.31.2", MCAPI_FTS_Tx_2_31_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.31.3", MCAPI_FTS_Tx_2_31_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.31.4", MCAPI_FTS_Tx_2_31_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.31.5", MCAPI_FTS_Tx_2_31_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.31.6", MCAPI_FTS_Tx_2_31_6},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.31.7", MCAPI_FTS_Tx_2_31_7},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.32.1", MCAPI_FTS_Tx_2_32_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.32.2", MCAPI_FTS_Tx_2_32_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.32.3", MCAPI_FTS_Tx_2_32_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.32.4", MCAPI_FTS_Tx_2_32_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.32.5", MCAPI_FTS_Tx_2_32_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.32.6", MCAPI_FTS_Tx_2_32_6},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.32.7", MCAPI_FTS_Tx_2_32_7},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.1", MCAPI_FTS_Tx_2_33_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.2", MCAPI_FTS_Tx_2_33_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.3", MCAPI_FTS_Tx_2_33_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "msg_echo_svr", 0xffffffff, "2.33.4", MCAPI_FTS_Tx_2_33_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.33.5", MCAPI_FTS_Tx_2_33_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.6", MCAPI_FTS_Tx_2_33_6},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.7", MCAPI_FTS_Tx_2_33_7},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.8", MCAPI_FTS_Tx_2_33_8},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.9", MCAPI_FTS_Tx_2_33_9},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.10", MCAPI_FTS_Tx_2_33_10},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.11", MCAPI_FTS_Tx_2_33_11},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.12", MCAPI_FTS_Tx_2_33_12},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.13", MCAPI_FTS_Tx_2_33_13},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.14", MCAPI_FTS_Tx_2_33_14},
    {MCAPI_CHAN_PKT_TX_TYPE, MCAPI_PORT_ANY, "pkt_svr", 0xffffffff, "2.33.15", MCAPI_FTS_Tx_2_33_15},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.16", MCAPI_FTS_Tx_2_33_16},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.17", MCAPI_FTS_Tx_2_33_17},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.18", MCAPI_FTS_Tx_2_33_18},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.33.19", MCAPI_FTS_Tx_2_33_19},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.20", MCAPI_FTS_Tx_2_33_20},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.21", MCAPI_FTS_Tx_2_33_21},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.22", MCAPI_FTS_Tx_2_33_22},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.23", MCAPI_FTS_Tx_2_33_23},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.24", MCAPI_FTS_Tx_2_33_24},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.25", MCAPI_FTS_Tx_2_33_25},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.26", MCAPI_FTS_Tx_2_33_26},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.27", MCAPI_FTS_Tx_2_33_27},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.28", MCAPI_FTS_Tx_2_33_28},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.29", MCAPI_FTS_Tx_2_33_29},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.30", MCAPI_FTS_Tx_2_33_30},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.31", MCAPI_FTS_Tx_2_33_31},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.32", MCAPI_FTS_Tx_2_33_32},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.33", MCAPI_FTS_Tx_2_33_33},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.34", MCAPI_FTS_Tx_2_33_34},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.35", MCAPI_FTS_Tx_2_33_35},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.36", MCAPI_FTS_Tx_2_33_36},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.33.37", MCAPI_FTS_Tx_2_33_37},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.34.1", MCAPI_FTS_Tx_2_34_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "lcl_mgmt", 0xffffffff, "2.34.2", MCAPI_FTS_Tx_2_34_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.3", MCAPI_FTS_Tx_2_34_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.4", MCAPI_FTS_Tx_2_34_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "msg_echo_svr", 0xffffffff, "2.34.5", MCAPI_FTS_Tx_2_34_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.34.6", MCAPI_FTS_Tx_2_34_6},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.7", MCAPI_FTS_Tx_2_34_7},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.8", MCAPI_FTS_Tx_2_34_8},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.9", MCAPI_FTS_Tx_2_34_9},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.34.10", MCAPI_FTS_Tx_2_34_10},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.11", MCAPI_FTS_Tx_2_34_11},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.12", MCAPI_FTS_Tx_2_34_12},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.13", MCAPI_FTS_Tx_2_34_13},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.14", MCAPI_FTS_Tx_2_34_14},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.15", MCAPI_FTS_Tx_2_34_15},
    {MCAPI_CHAN_PKT_TX_TYPE, MCAPI_PORT_ANY, "pkt_svr", 0xffffffff, "2.34.16", MCAPI_FTS_Tx_2_34_16},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.17", MCAPI_FTS_Tx_2_34_17},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.18", MCAPI_FTS_Tx_2_34_18},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.19", MCAPI_FTS_Tx_2_34_19},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.34.20", MCAPI_FTS_Tx_2_34_20},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.21", MCAPI_FTS_Tx_2_34_21},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.22", MCAPI_FTS_Tx_2_34_22},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.34.23", MCAPI_FTS_Tx_2_34_23},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.24", MCAPI_FTS_Tx_2_34_24},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.25", MCAPI_FTS_Tx_2_34_25},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.26", MCAPI_FTS_Tx_2_34_26},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.27", MCAPI_FTS_Tx_2_34_27},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.28", MCAPI_FTS_Tx_2_34_28},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.29", MCAPI_FTS_Tx_2_34_29},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.30", MCAPI_FTS_Tx_2_34_30},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.31", MCAPI_FTS_Tx_2_34_31},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.32", MCAPI_FTS_Tx_2_34_32},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.33", MCAPI_FTS_Tx_2_34_33},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.34", MCAPI_FTS_Tx_2_34_34},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.35", MCAPI_FTS_Tx_2_34_35},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.36", MCAPI_FTS_Tx_2_34_36},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.37", MCAPI_FTS_Tx_2_34_37},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.34.38", MCAPI_FTS_Tx_2_34_38},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.35.1", MCAPI_FTS_Tx_2_35_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "lcl_mgmt", 0xffffffff, "2.35.2", MCAPI_FTS_Tx_2_35_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.3", MCAPI_FTS_Tx_2_35_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.4", MCAPI_FTS_Tx_2_35_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "msg_echo_svr", 0xffffffff, "2.35.5", MCAPI_FTS_Tx_2_35_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.35.6", MCAPI_FTS_Tx_2_35_6},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.7", MCAPI_FTS_Tx_2_35_7},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.8", MCAPI_FTS_Tx_2_35_8},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.9", MCAPI_FTS_Tx_2_35_9},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.35.10", MCAPI_FTS_Tx_2_35_10},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.11", MCAPI_FTS_Tx_2_35_11},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.12", MCAPI_FTS_Tx_2_35_12},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.13", MCAPI_FTS_Tx_2_35_13},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.14", MCAPI_FTS_Tx_2_35_14},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.15", MCAPI_FTS_Tx_2_35_15},
    {MCAPI_CHAN_PKT_TX_TYPE, MCAPI_PORT_ANY, "pkt_svr", 0xffffffff, "2.35.16", MCAPI_FTS_Tx_2_35_16},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.17", MCAPI_FTS_Tx_2_35_17},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.18", MCAPI_FTS_Tx_2_35_18},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.19", MCAPI_FTS_Tx_2_35_19},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.35.20", MCAPI_FTS_Tx_2_35_20},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.21", MCAPI_FTS_Tx_2_35_21},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.22", MCAPI_FTS_Tx_2_35_22},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.35.23", MCAPI_FTS_Tx_2_35_23},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.24", MCAPI_FTS_Tx_2_35_24},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.25", MCAPI_FTS_Tx_2_35_25},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.26", MCAPI_FTS_Tx_2_35_26},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.35.27", MCAPI_FTS_Tx_2_35_27},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.28", MCAPI_FTS_Tx_2_35_28},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.29", MCAPI_FTS_Tx_2_35_29},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.35.30", MCAPI_FTS_Tx_2_35_30},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.31", MCAPI_FTS_Tx_2_35_31},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.32", MCAPI_FTS_Tx_2_35_32},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.35.33", MCAPI_FTS_Tx_2_35_33},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.34", MCAPI_FTS_Tx_2_35_34},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.35", MCAPI_FTS_Tx_2_35_35},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.35.36", MCAPI_FTS_Tx_2_35_36},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.37", MCAPI_FTS_Tx_2_35_37},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.38", MCAPI_FTS_Tx_2_35_38},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.35.39", MCAPI_FTS_Tx_2_35_39},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "lcl_mgmt", 0xffffffff, "2.35.40", MCAPI_FTS_Tx_2_35_40},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.41", MCAPI_FTS_Tx_2_35_41},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "lcl_mgmt", 0xffffffff, "2.35.42", MCAPI_FTS_Tx_2_35_42},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.43", MCAPI_FTS_Tx_2_35_43},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.35.44", MCAPI_FTS_Tx_2_35_44},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "lcl_mgmt", 0xffffffff, "2.35.45", MCAPI_FTS_Tx_2_35_45},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.46", MCAPI_FTS_Tx_2_35_46},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "lcl_mgmt", 0xffffffff, "2.35.47", MCAPI_FTS_Tx_2_35_47},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.48", MCAPI_FTS_Tx_2_35_48},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.35.49", MCAPI_FTS_Tx_2_35_49},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "lcl_mgmt", 0xffffffff, "2.35.50", MCAPI_FTS_Tx_2_35_50},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.51", MCAPI_FTS_Tx_2_35_51},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "lcl_mgmt", 0xffffffff, "2.35.52", MCAPI_FTS_Tx_2_35_52},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.53", MCAPI_FTS_Tx_2_35_53},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.54", MCAPI_FTS_Tx_2_35_54},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.55", MCAPI_FTS_Tx_2_35_55},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.56", MCAPI_FTS_Tx_2_35_56},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.57", MCAPI_FTS_Tx_2_35_57},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.58", MCAPI_FTS_Tx_2_35_58},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, MCAPI_NULL, 0xffffffff, "2.35.59", MCAPI_FTS_Tx_2_35_59},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "lcl_mgmt", 0xffffffff, "2.35.60", MCAPI_FTS_Tx_2_35_60},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.61", MCAPI_FTS_Tx_2_35_61},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "lcl_mgmt", 0xffffffff, "2.35.62", MCAPI_FTS_Tx_2_35_62},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.63", MCAPI_FTS_Tx_2_35_63},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.64", MCAPI_FTS_Tx_2_35_64},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.65", MCAPI_FTS_Tx_2_35_65},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.35.66", MCAPI_FTS_Tx_2_35_66},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.36.1", MCAPI_FTS_Tx_2_36_1},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.36.2", MCAPI_FTS_Tx_2_36_2},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.36.3", MCAPI_FTS_Tx_2_36_3},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.36.4", MCAPI_FTS_Tx_2_36_4},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.36.5", MCAPI_FTS_Tx_2_36_5},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.36.6", MCAPI_FTS_Tx_2_36_6},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.36.7", MCAPI_FTS_Tx_2_36_7},
    {MCAPI_MSG_TX_TYPE, MCAPI_PORT_ANY, "mgmt_svc", 0xffffffff, "2.36.8", MCAPI_FTS_Tx_2_36_8}
};

MCAPID_STRUCT   MCAPI_FTS_Services[MCAPID_FTS_COUNT];
MCAPI_MUTEX     MCAPID_FTS_Mutex;
unsigned        MCAPID_Failures = 0;
MCAPID_STRUCT   MCAPID_Reg_Struct, MCAPID_Mgmt_Struct, MCAPID_Echo_Struct[4];

extern  MCAPI_GLOBAL_DATA           MCAPI_Global_Struct;


int mcapi_test_start(int argc, char *argv[])
{
    mcapi_status_t      status;
    mcapi_version_t     version;
    int                 i, endp_count;
    unsigned            error_count = 0;

    /* Initialize MCAPI on the node. */
    mcapi_initialize(MCAPI_LOCAL_NODE_ID, &version, &status);

    /* If an error occurred, the demo has failed. */
    if (status != MCAPI_SUCCESS) {
        printf("%s\n", "mcapi_initialize() failed!");
        MCAPID_Failures++;
        goto out;
    }

    MCAPI_Create_Mutex(&MCAPID_FTS_Mutex, "fts_mutex");

#if (MCAPID_REG_SERVER_NODE == MCAPI_LOCAL_NODE_ID)

    /* Start the registration server. */
    MCAPID_Create_Thread(&MCAPID_Registration_Server, &MCAPID_Reg_Struct);

#endif

    /* Let the registration server come up. */
    MCAPID_Sleep(2000);

    /* Set up the structure for the management service. */
    MCAPID_Mgmt_Struct.type = MCAPI_MSG_RX_TYPE;
    MCAPID_Mgmt_Struct.local_port = MCAPI_PORT_ANY;
    MCAPID_Mgmt_Struct.service = "mgmt_svc";
    MCAPID_Mgmt_Struct.thread_entry = MCAPID_Mgmt_Service;

    /* Start the management server. */
    MCAPID_Create_Service(&MCAPID_Mgmt_Struct, 1);

    /* Set up the structure for the message echo server. */
    MCAPID_Echo_Struct[0].type = MCAPI_MSG_RX_TYPE;
    MCAPID_Echo_Struct[0].local_port = MCAPI_PORT_ANY;
    MCAPID_Echo_Struct[0].service = "msg_echo_svr";
    MCAPID_Echo_Struct[0].thread_entry = MCAPI_FTS_Msg_Echo_Server;

    /* Set up the structure for the packet discard server. */
    MCAPID_Echo_Struct[1].type = MCAPI_CHAN_PKT_RX_TYPE;
    MCAPID_Echo_Struct[1].local_port = MCAPI_PORT_ANY;
    MCAPID_Echo_Struct[1].service = "pkt_svr";
    MCAPID_Echo_Struct[1].thread_entry = MCAPI_FTS_Pkt_Server;

    /* Set up the structure for the scalar discard server. */
    MCAPID_Echo_Struct[2].type = MCAPI_MSG_RX_TYPE;
    MCAPID_Echo_Struct[2].local_port = MCAPI_PORT_ANY;
    MCAPID_Echo_Struct[2].service = "scl_svr";
    MCAPID_Echo_Struct[2].thread_entry = MCAPI_FTS_Scl_Server;

    /* Set up the structure for the local services server. */
    MCAPID_Echo_Struct[3].type = MCAPI_MSG_RX_TYPE;
    MCAPID_Echo_Struct[3].local_port = MCAPI_PORT_ANY;
    MCAPID_Echo_Struct[3].service = "lcl_mgmt";
    MCAPID_Echo_Struct[3].thread_entry = MCAPI_FTS_Local_Services;

    /* Start the servers. */
    MCAPID_Create_Service(MCAPID_Echo_Struct, 4);

    /* Run each test and wait for it to complete before moving on to the
     * next test.
     */
    for (i = CFG_NU_TF_KERN_1_MCAPI_START;
         (i <= CFG_NU_TF_KERN_1_MCAPI_FINISH) && (i < MCAPID_FTS_COUNT);
         i ++)
    {
        MCAPI_FTS_Services[i].type = MCAPI_FTS_User_Services[i].type;
        MCAPI_FTS_Services[i].local_port = MCAPI_FTS_User_Services[i].local_port;
        MCAPI_FTS_Services[i].service = MCAPI_FTS_User_Services[i].service;
        MCAPI_FTS_Services[i].retry = MCAPI_FTS_User_Services[i].retry;
        MCAPI_FTS_Services[i].thread_entry = MCAPI_FTS_User_Services[i].thread_entry;
        MCAPI_FTS_Services[i].state = -1;

        mcapi_lock_node_data();

        /* Get the current endpoint count. */
        endp_count = MCAPI_Global_Struct.mcapi_node_list[0].mcapi_endpoint_count;

        mcapi_unlock_node_data();

        /* Start the service. */
        MCAPID_Create_Service(&MCAPI_FTS_Services[i], 1);

        if (MCAPI_FTS_Services[i].status == MCAPI_SUCCESS)
        {
			/* Wait for the service to complete. */
			while (MCAPI_FTS_Services[i].state != 0)
			{
				MCAPID_Sleep(250);
			}
        }

        if (MCAPI_FTS_Services[i].status != MCAPI_SUCCESS)
        {
            MCAPID_Failures ++;
        }

        /* Print the number of errors with this test. */
        printf("MCAPI Functional Test %s complete - %u errors\r\n", MCAPI_FTS_User_Services[i].test_name, MCAPID_Failures - error_count);
        error_count = MCAPID_Failures;

        /* Let the control tasks run to clean up anything using the endpoint from the
         * old connections.
         */
        MCAPID_Sleep(1500);

        MCAPID_Cleanup(&MCAPI_FTS_Services[i]);

        /* Let the tasks run that mcapi_delete_endpoint may have resumed. */
        MCAPID_Sleep(1500);

        mcapi_lock_node_data();

        /* Ensure the endpoint count is the same as before the test. */
        if (endp_count != MCAPI_Global_Struct.mcapi_node_list[0].mcapi_endpoint_count)
        {
            if (MCAPI_Global_Struct.mcapi_node_list[0].mcapi_endpoint_count > endp_count)
            {
                /* Print the number of endpoints lost */
                printf("MCAPI Functional Test %s lost %u endpoints\r\n", MCAPI_FTS_User_Services[i].test_name, MCAPI_Global_Struct.mcapi_node_list[0].mcapi_endpoint_count - endp_count);
            }

            else
            {
                /* Print the number of endpoints lost */
                printf("MCAPI Functional Test %s lost %u endpoints\r\n", MCAPI_FTS_User_Services[i].test_name, endp_count - MCAPI_Global_Struct.mcapi_node_list[0].mcapi_endpoint_count);
            }
        }

        mcapi_unlock_node_data();
    }

    printf("MCAPI Functional Test Complete with, %u errors\r\n", MCAPID_Failures);

out:
    return MCAPID_Failures;
} /* MCAPID_Test_Init */

/************************************************************************
*
*   FUNCTION
*
*       MCAPI_FTS_Msg_Server
*
*   DESCRIPTION
*
*       Listen on an endpoint for incoming messages, and echo back the
*       data.
*
*************************************************************************/
MCAPI_THREAD_ENTRY(MCAPI_FTS_Msg_Echo_Server)
{
    MCAPID_STRUCT       *mcapi_struct = (MCAPID_STRUCT*)argv;
    char                buffer[MCAPID_MSG_LEN];
    size_t              rx_len;
    mcapi_status_t      status;

    for (;;)
    {
        /* Wait for a message. */
        mcapi_msg_recv(mcapi_struct->local_endp, buffer, MCAPID_MSG_LEN, &rx_len,
                       &status);

        if (status == MCAPI_SUCCESS)
        {
            /* Echo the message. */
            mcapi_msg_send(mcapi_struct->local_endp,
                           mcapi_get32((unsigned char*)buffer, MCAPID_MGMT_LOCAL_ENDP_OFFSET),
                           buffer, MCAPID_MSG_LEN,
                           MCAPI_DEFAULT_PRIO, &status);
        }
    }

} /* MCAPI_FTS_Msg_Echo_Server */

/************************************************************************
*
*   FUNCTION
*
*       MCAPI_FTS_Pkt_Server
*
*   DESCRIPTION
*
*       Open the receive side of a connection, wait for a connection,
*       listen on an endpoint for incoming messages.
*
*************************************************************************/
MCAPI_THREAD_ENTRY(MCAPI_FTS_Pkt_Server)
{
    MCAPID_STRUCT               *mcapi_struct = (MCAPID_STRUCT*)argv;
    char                        *buffer;
    size_t                      rx_len;

    for (;;)
    {
        /* Wait for a connection to be established. */
        mcapi_wait(&mcapi_struct->request, &rx_len, &mcapi_struct->status,
                   MCAPI_INFINITE);

        for (;;)
        {
            /* Wait for an incoming message. */
            mcapi_pktchan_recv(mcapi_struct->pkt_rx_handle, (void**)&buffer,
                               &rx_len, &mcapi_struct->status);

            /* If data was received. */
            if (mcapi_struct->status == MCAPI_SUCCESS)
            {
                /* Free the buffer. */
                mcapi_pktchan_free(buffer, &mcapi_struct->status);
            }

            /* If the connection has been closed. */
            else
            {
                /* Close the receive side. */
                mcapi_packetchan_recv_close_i(mcapi_struct->pkt_rx_handle,
                                              &mcapi_struct->request,
                                              &mcapi_struct->status);

                break;
            }
        }

        /* Open the local endpoint back up as the receiver. */
        mcapi_open_pktchan_recv_i(&mcapi_struct->pkt_rx_handle,
                                  mcapi_struct->local_endp,
                                  &mcapi_struct->request, &mcapi_struct->status);
    }

} /* MCAPI_FTS_Pkt_Server */

/************************************************************************
*
*   FUNCTION
*
*       MCAPI_FTS_Scl_Server
*
*   DESCRIPTION
*
*       Open the receive side of a connection, wait for a connection,
*       listen on an endpoint for incoming messages.
*
*************************************************************************/
MCAPI_THREAD_ENTRY(MCAPI_FTS_Scl_Server)
{
    MCAPID_STRUCT   *mcapi_struct = (MCAPID_STRUCT*)argv;
    size_t          rx_len;
    char            buffer[MCAPID_MGMT_PKT_LEN];
    mcapi_uint32_t  type;
    mcapi_uint64_t  recv_64;
    mcapi_uint32_t  recv_32;
    mcapi_uint16_t  recv_16;
    mcapi_uint8_t   recv_8;
    mcapi_status_t  status;

    for (;;)
    {
        /* Wait for a message indicating the type of receive to perform. */
        mcapi_msg_recv(mcapi_struct->local_endp, buffer, MCAPID_MGMT_PKT_LEN,
                       &rx_len, &mcapi_struct->status);

        if (mcapi_struct->status == MCAPI_SUCCESS)
        {
            type = mcapi_get32((unsigned char*)buffer, MCAPID_MGMT_TYPE_OFFSET);

            /* Check the receive type to ensure it is valid. */
            if ( (type == MCAPID_RX_64_BIT_SCL) ||
                 (type == MCAPID_RX_32_BIT_SCL) ||
                 (type == MCAPID_RX_16_BIT_SCL) ||
                 (type == MCAPID_RX_8_BIT_SCL) )
            {
                /* Send a successful status. */
                status = MCAPI_SUCCESS;
            }

            else
            {
                /* Send an error, but continue with opening the receive
                 * side and closing in case the other side wants to send
                 * data over a closed connection.
                 */
                status = -1;
            }

            /* Put the status in the packet. */
            mcapi_put32((unsigned char*)buffer, MCAPID_MGMT_STATUS_OFFSET, status);

            /* Send the response. */
            mcapi_msg_send(mcapi_struct->local_endp,
                           mcapi_get32((unsigned char*)buffer, MCAPID_MGMT_LOCAL_ENDP_OFFSET),
                           buffer, rx_len, MCAPI_DEFAULT_PRIO,
                           &mcapi_struct->status);

            /* Open the local endpoint up as the receiver. */
            mcapi_open_sclchan_recv_i(&mcapi_struct->scl_rx_handle,
                                      mcapi_struct->local_endp,
                                      &mcapi_struct->request,
                                      &mcapi_struct->status);

            /* Wait for a connection to be established. */
            mcapi_wait(&mcapi_struct->request, &rx_len, &mcapi_struct->status,
                       MCAPI_INFINITE);

            if (mcapi_struct->status == MCAPI_SUCCESS)
            {
                switch (type)
                {
                    case MCAPID_RX_64_BIT_SCL:

                        /* Wait for an incoming message. */
                        recv_64 = mcapi_sclchan_recv_uint64(mcapi_struct->scl_rx_handle,
                                                            &mcapi_struct->status);

                        if ( (mcapi_struct->status == MCAPI_SUCCESS) &&
                             (recv_64 != MCAPI_FTS_64BIT_SCALAR) )
                        {
                            MCAPID_Failures ++;
                        }

                        /* Close the receive side. */
                        mcapi_sclchan_recv_close_i(mcapi_struct->scl_rx_handle,
                                                   &mcapi_struct->request,
                                                   &mcapi_struct->status);

                        break;

                    case MCAPID_RX_32_BIT_SCL:

                        /* Wait for an incoming message. */
                        recv_32 = mcapi_sclchan_recv_uint32(mcapi_struct->scl_rx_handle,
                                                            &mcapi_struct->status);

                        if ( (mcapi_struct->status == MCAPI_SUCCESS) &&
                             (recv_32 != MCAPI_FTS_32BIT_SCALAR) )
                        {
                            MCAPID_Failures ++;
                        }

                        /* Close the receive side. */
                        mcapi_sclchan_recv_close_i(mcapi_struct->scl_rx_handle,
                                                   &mcapi_struct->request,
                                                   &mcapi_struct->status);

                        break;

                    case MCAPID_RX_16_BIT_SCL:

                        /* Wait for an incoming message. */
                        recv_16 = mcapi_sclchan_recv_uint16(mcapi_struct->scl_rx_handle,
                                                            &mcapi_struct->status);

                        if ( (mcapi_struct->status == MCAPI_SUCCESS) &&
                             (recv_16 != MCAPI_FTS_16BIT_SCALAR) )
                        {
                            MCAPID_Failures ++;
                        }

                        /* Close the receive side. */
                        mcapi_sclchan_recv_close_i(mcapi_struct->scl_rx_handle,
                                                   &mcapi_struct->request,
                                                   &mcapi_struct->status);

                        break;

                    case MCAPID_RX_8_BIT_SCL:

                        /* Wait for an incoming message. */
                        recv_8 = mcapi_sclchan_recv_uint8(mcapi_struct->scl_rx_handle,
                                                          &mcapi_struct->status);

                        if ( (mcapi_struct->status == MCAPI_SUCCESS) &&
                             (recv_8 != MCAPI_FTS_8BIT_SCALAR) )
                        {
                            MCAPID_Failures ++;
                        }

                        /* Close the receive side. */
                        mcapi_sclchan_recv_close_i(mcapi_struct->scl_rx_handle,
                                                   &mcapi_struct->request,
                                                   &mcapi_struct->status);

                        break;

                    default:

                        /* Close the receive side. */
                        mcapi_sclchan_recv_close_i(mcapi_struct->scl_rx_handle,
                                                   &mcapi_struct->request,
                                                   &mcapi_struct->status);

                        break;
                }

                /* Put the status in the packet. */
                mcapi_put32((unsigned char*)buffer, MCAPID_MGMT_STATUS_OFFSET, mcapi_struct->status);

                /* Send the response. */
                mcapi_msg_send(mcapi_struct->local_endp,
                               mcapi_get32((unsigned char*)buffer, MCAPID_MGMT_LOCAL_ENDP_OFFSET),
                               buffer, rx_len, MCAPI_DEFAULT_PRIO,
                               &mcapi_struct->status);
            }

            else
            {
                /* Close the receive side. */
                mcapi_sclchan_recv_close_i(mcapi_struct->scl_rx_handle,
                                           &mcapi_struct->request,
                                           &mcapi_struct->status);
            }
        }
    }

} /* MCAPI_FTS_Scl_Server */

/************************************************************************
*
*   FUNCTION
*
*       MCAPI_FTS_Local_Services
*
*   DESCRIPTION
*
*       This function processes incoming packets instructing the node
*       to create an endpoint, delete an endpoint, etc.
*
*************************************************************************/
MCAPI_THREAD_ENTRY(MCAPI_FTS_Local_Services)
{
    size_t          rx_len;
    MCAPID_STRUCT   *mcapi_struct = (MCAPID_STRUCT*)argv;
    char            buffer[MCAPID_MGMT_PKT_LEN];

    for (;;)
    {
        /* Wait for a message. */
        mcapi_msg_recv(mcapi_struct->local_endp, buffer, MCAPID_MGMT_PKT_LEN,
                       &rx_len, &mcapi_struct->status);

        if (mcapi_struct->status == MCAPI_SUCCESS)
        {
            /* Sleep the appropriate amount of time - this gives the other side
             * time to issue a command before the management task causes an
             * action.
             */
            MCAPID_Sleep(mcapi_get32((unsigned char*)buffer, MCAPID_MGMT_PAUSE_OFFSET));

            /* Determine the type of message. */
            switch (mcapi_get32((unsigned char*)buffer, MCAPID_MGMT_TYPE_OFFSET))
            {
                case MCAPID_CANCEL_REQUEST:

                    /* Cancel the pending local request. */
                    mcapi_cancel((mcapi_request_t*)(mcapi_get32((unsigned char*)buffer, MCAPID_MGMT_STATUS_OFFSET)),
                                 &mcapi_struct->status);

                    break;

                case MCAPID_WAIT_REQUEST:

                    /* Wait for the specified request. */
                    mcapi_wait((mcapi_request_t*)(mcapi_get32((unsigned char*)buffer, MCAPID_MGMT_STATUS_OFFSET)),
                               &rx_len, &mcapi_struct->status, MCAPI_INFINITE);

                    break;

                default:

                    mcapi_struct->status = -1;
                    break;
            }

            /* Put the status in the packet. */
            mcapi_put32((unsigned char*)buffer, MCAPID_MGMT_STATUS_OFFSET, mcapi_struct->status);

            /* Send the response using the specified priority. */
            mcapi_msg_send(mcapi_struct->local_endp,
                           mcapi_get32((unsigned char*)buffer, MCAPID_MGMT_LOCAL_ENDP_OFFSET),
                           buffer, rx_len, mcapi_get32((unsigned char*)buffer, MCAPID_MGMT_PRIO_OFFSET),
                           &mcapi_struct->status);
        }
    }

} /* MCAPI_FTS_Local_Services */

