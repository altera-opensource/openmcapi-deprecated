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



#ifndef MCAPI_EXTR_H
#define MCAPI_EXTR_H

#include <mcapi_os.h>
#include <openmcapi_cfg.h>

#ifdef          __cplusplus
extern  "C" {                               /* C declarations in C++     */
#endif /* _cplusplus */

#define MCAPI_MSG_TYPE          0
#define MCAPI_CHAN_PKT_TYPE     1
#define MCAPI_CHAN_SCAL_TYPE    2

#define MCAPI_SUCCESS           0
#define MCAPI_ENO_INIT          -200
#define MCAPI_INITIALIZED       -201
#define MCAPI_ENODE_NOTVALID    -202
#define MCAPI_EPARAM            -203
#define MCAPI_ENO_FINAL         -204
#define MCAPI_ENODE_NOTINIT     -205
#define MCAPI_EPORT_NOTVALID    -206
#define MCAPI_EENDP_ISCREATED   -207
#define MCAPI_EENDP_LIMIT       -208
#define MCAPI_EEP_NOTALLOWED    -209
#define MCAPI_ENOT_ENDP         -210
#define MCAPI_ECHAN_OPEN        -211
#define MCAPI_ENOT_OWNER        -212
#define MCAPI_EATTR_NUM         -213
#define MCAPI_EATTR_SIZE        -214
#define MCAPI_ECONNECTED        -215
#define MCAPI_EREAD_ONLY        -216
#define MCAPI_EMESS_LIMIT       -217
#define MCAPI_ENO_BUFFER        -218
#define MCAPI_ENO_REQUEST       -219
#define MCAPI_ENO_MEM           -220
#define MCAPI_EPRIO             -221
#define MCAPI_ETRUNCATED        -222
#define MCAPI_EATTR_INCOMP      -223
#define MCAPI_ENOT_CONNECTED    -224
#define MCAPI_ECHAN_TYPE        -225
#define MCAPI_EDIR              -226
#define MCAPI_ENOT_HANDLE       -227
#define MCAPI_EPACK_LIMIT       -228
#define MCAPI_ENOT_VALID_BUF    -229
#define MCAPI_ENOT_OPEN         -230
#define MCAPI_ESCL_SIZE         -231
#define MCAPI_EREQ_CANCELED     -232
#define MCAPI_EREQ_TIMEOUT      -233
#define MCAPI_EREQ_PENDING      -234
#define MCAPI_ENOTREQ_HANDLE    -235
#define MCAPI_INCOMPLETE        -236
#define MCAPI_EREQ_ERROR        -237
#define MCAPI_OS_ERROR          -238

/* Macro for specifying that the next available port should be used when
 * creating a new endpoint.
 */
#define MCAPI_PORT_ANY          0xffffffff

/* Macro for specifying that an infinite timeout should be used in the
 * blocking operation.
 */
#define MCAPI_INFINITE          0xffffffff

extern mcapi_node_t MCAPI_Node_ID;

/*
 * NOTE: Application code should consider this type opaque, and must not
 * directly access these members.
 */
typedef struct
{
    mcapi_cond_t    mcapi_cond;
    mcapi_cond_t    *mcapi_cond_ptr;
} MCAPI_COND_STRUCT;

/* Data structure that is used in non-blocking operations.  The fields are
 * populated for later use to check the status of the original non-blocking
 * call.
 *
 * NOTE: Application code should consider this type opaque, and must not
 * directly access these members.
 */
struct _mcapi_request
{
    struct _mcapi_request   *mcapi_next;
    struct _mcapi_request   *mcapi_prev;
    mcapi_status_t          mcapi_status;
    mcapi_uint8_t           mcapi_type;
    mcapi_uint8_t           mcapi_chan_type;
	mcapi_node_t            mcapi_local_node_id;    /* The node ID of the node
                                                     * making the call. */
    mcapi_endpoint_t        mcapi_target_endp;
    mcapi_endpoint_t        *mcapi_endp_ptr;        /* The application's
                                                     * pointer to an endpoint
                                                     * structure. */

    mcapi_node_t            mcapi_target_node_id;   /* The target node ID. */

    mcapi_port_t            mcapi_target_port_id;   /* The target endpoint
                                                     * port. */
    size_t                  mcapi_byte_count;
    void                    *mcapi_buffer;          /* Application buffer to
                                                     * fill in. */

    size_t                  mcapi_buf_size;         /* Application buffer
                                                     * size. */

    void                    **mcapi_pkt;            /* Application packet
                                                     * pointer to fill in. */
    mcapi_uint32_t          mcapi_pending_count;
    MCAPI_COND_STRUCT       mcapi_cond;
};
typedef struct  _mcapi_request      mcapi_request_t;

void mcapi_cancel(mcapi_request_t *, mcapi_status_t *);
void mcapi_connect_pktchan_i(mcapi_endpoint_t, mcapi_endpoint_t, mcapi_request_t *,
                             mcapi_status_t *);
void mcapi_connect_sclchan_i(mcapi_endpoint_t, mcapi_endpoint_t, mcapi_request_t *,
                             mcapi_status_t *);
void mcapi_delete_endpoint(mcapi_endpoint_t, mcapi_status_t *);
void mcapi_finalize(mcapi_status_t *);
void mcapi_get_endpoint_attribute(mcapi_endpoint_t, mcapi_uint_t, void *, size_t,
                                  mcapi_status_t *);
void mcapi_get_endpoint_i(mcapi_node_t, mcapi_port_t, mcapi_endpoint_t *,
                          mcapi_request_t *, mcapi_status_t *);
void mcapi_initialize(mcapi_node_t, mcapi_version_t *, mcapi_status_t *);
void mcapi_msg_recv_i(mcapi_endpoint_t, void *, size_t, mcapi_request_t *,
                      mcapi_status_t *);
void mcapi_msg_recv(mcapi_endpoint_t, void *, size_t, size_t *, mcapi_status_t *);
void mcapi_msg_send_i(mcapi_endpoint_t, mcapi_endpoint_t, void *, size_t,
                      mcapi_priority_t, mcapi_request_t *, mcapi_status_t *);
void mcapi_msg_send(mcapi_endpoint_t, mcapi_endpoint_t, void *, size_t,
                    mcapi_priority_t, mcapi_status_t *);
void mcapi_open_pktchan_recv_i(mcapi_pktchan_recv_hndl_t *, mcapi_endpoint_t,
                               mcapi_request_t *, mcapi_status_t *);
void mcapi_open_pktchan_send_i(mcapi_pktchan_send_hndl_t *, mcapi_endpoint_t,
                               mcapi_request_t *, mcapi_status_t *);
void mcapi_open_sclchan_recv_i(mcapi_sclchan_recv_hndl_t *, mcapi_endpoint_t,
                               mcapi_request_t *, mcapi_status_t *);
void mcapi_open_sclchan_send_i(mcapi_sclchan_send_hndl_t *, mcapi_endpoint_t,
                               mcapi_request_t *, mcapi_status_t *);
void mcapi_packetchan_recv_close_i(mcapi_pktchan_recv_hndl_t, mcapi_request_t *,
                                   mcapi_status_t *);
void mcapi_pktchan_recv_i(mcapi_pktchan_recv_hndl_t, void **, mcapi_request_t *,
                          mcapi_status_t *);
void mcapi_pktchan_recv(mcapi_pktchan_recv_hndl_t, void **, size_t *, mcapi_status_t *);
void mcapi_packetchan_send_close_i(mcapi_pktchan_send_hndl_t, mcapi_request_t *,
                                   mcapi_status_t *);
void mcapi_pktchan_send_i(mcapi_pktchan_send_hndl_t, void *, size_t,
                          mcapi_request_t *, mcapi_status_t *);
void mcapi_pktchan_send(mcapi_pktchan_send_hndl_t, void *, size_t, mcapi_status_t *);
void mcapi_sclchan_recv_close_i(mcapi_sclchan_recv_hndl_t, mcapi_request_t *,
                               mcapi_status_t *);
void mcapi_sclchan_send_close_i(mcapi_sclchan_send_hndl_t, mcapi_request_t *,
                                mcapi_status_t *);
void mcapi_sclchan_send_uint16(mcapi_sclchan_send_hndl_t, mcapi_uint16_t,
                               mcapi_status_t *);
void mcapi_sclchan_send_uint32(mcapi_sclchan_send_hndl_t, mcapi_uint32_t,
                               mcapi_status_t *);
void mcapi_sclchan_send_uint64(mcapi_sclchan_send_hndl_t, mcapi_uint64_t,
                               mcapi_status_t *);
void mcapi_sclchan_send_uint8(mcapi_sclchan_send_hndl_t, mcapi_uint8_t,
                              mcapi_status_t *);
void mcapi_set_endpoint_attribute(mcapi_endpoint_t, mcapi_uint_t, void *,
                                  size_t, mcapi_status_t *);

mcapi_endpoint_t mcapi_get_endpoint(mcapi_node_t, mcapi_port_t, mcapi_status_t *);
mcapi_endpoint_t mcapi_create_endpoint(mcapi_port_t, mcapi_status_t *);

mcapi_boolean_t mcapi_test(mcapi_request_t *, size_t *, mcapi_status_t *);
mcapi_boolean_t mcapi_wait(mcapi_request_t *, size_t *, mcapi_status_t *,
                           mcapi_timeout_t);

mcapi_uint_t mcapi_get_node_id(mcapi_status_t *);
mcapi_uint_t mcapi_msg_available(mcapi_endpoint_t, mcapi_status_t *);
mcapi_uint_t mcapi_pktchan_available(mcapi_pktchan_recv_hndl_t, mcapi_status_t *);
void mcapi_pktchan_free(void *, mcapi_status_t *);
mcapi_uint_t mcapi_sclchan_available(mcapi_sclchan_recv_hndl_t, mcapi_status_t *);

mcapi_uint16_t mcapi_sclchan_recv_uint16(mcapi_sclchan_recv_hndl_t, mcapi_status_t *);
mcapi_uint32_t mcapi_sclchan_recv_uint32(mcapi_sclchan_recv_hndl_t, mcapi_status_t *);
mcapi_uint64_t mcapi_sclchan_recv_uint64(mcapi_sclchan_recv_hndl_t, mcapi_status_t *);
mcapi_uint8_t mcapi_sclchan_recv_uint8(mcapi_sclchan_recv_hndl_t, mcapi_status_t *);
mcapi_int_t mcapi_wait_any(size_t, mcapi_request_t **, size_t *, mcapi_status_t *,
                           mcapi_timeout_t);

#ifdef          __cplusplus
}
#endif /* _cplusplus */

#endif /* MCAPI_EXTR_H */
