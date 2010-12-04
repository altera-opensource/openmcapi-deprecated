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
extern mcapi_uint32_t   MCAPI_Buf_Count;
#endif

/*************************************************************************
*
*   FUNCTION
*
*       mcapi_loop_init
*
*   DESCRIPTION
*
*       Initialize the loopback interface.
*
*   INPUTS
*
*       node_id                 The local node ID.
*       *int_ptr                A pointer to the interface being
*                               initialized.
*
*   OUTPUTS
*
*       MCAPI_SUCCESS           Loopback is enabled and initialization
*                               was successful.
*       1                       Loopback is not enabled.
*
*************************************************************************/
mcapi_status_t mcapi_loop_init(mcapi_node_t node_id, MCAPI_INTERFACE *int_ptr)
{
#if (MCAPI_ENABLE_LOOPBACK == 1)

    unsigned int    length;

    /* Get the length of the interface name. */
    length = strlen(MCAPI_LOOPBACK_NAME);

    /* If it's too long, truncate it. */
    if (length > (MCAPI_INT_NAME_LEN - 1))
    {
        length = MCAPI_INT_NAME_LEN - 1;
    }

    /* Store the name of this interface. */
    memcpy(int_ptr->mcapi_int_name, MCAPI_LOOPBACK_NAME,
               length);

    /* Terminate the string. */
    int_ptr->mcapi_int_name[length] = 0;

    /* Set the maximum buffer size for incoming / outgoing data. */
    int_ptr->mcapi_max_buf_size = MCAPI_MAX_DATA_LEN;

    /* Set up function pointers for sending data, reserving an outgoing
     * driver buffer, returning the buffer to the free list, and
     * issuing ioctl commands.
     */
    int_ptr->mcapi_tx_output = mcapi_loop_tx;
    int_ptr->mcapi_get_buffer = mcapi_reserve_buffer;
    int_ptr->mcapi_recover_buffer = mcapi_recover_buffer;
    int_ptr->mcapi_ioctl = mcapi_loop_ioctl;

    return (MCAPI_SUCCESS);

#else

    return (1);

#endif

}

#if (MCAPI_ENABLE_LOOPBACK == 1)

/*************************************************************************
*
*   FUNCTION
*
*       mcapi_loop_tx
*
*   DESCRIPTION
*
*       Transmit data over the loopback interface.
*
*   INPUTS
*
*       *buffer                 A pointer to the buffer of data to
*                               transmit.
*       len                     The length of data to transmit.
*       priority                The priority of the outgoing data.
*       *tx_end_ptr             A pointer to the sending endpoint.
*
*   OUTPUTS
*
*       MCAPI_SUCCESS           The transmission was successful.
*       MCAPI_ENOT_ENDP         The receive endpoint is invalid.
*       MCAPI_ENO_BUFFER        There are no available buffers for
*                               receiving data.
*
*************************************************************************/
mcapi_status_t mcapi_loop_tx(MCAPI_BUFFER *buffer, size_t len,
                             mcapi_priority_t priority,
                             MCAPI_ENDPOINT *tx_end_ptr)
{
    MCAPI_BUFFER        *new_buf;
    mcapi_status_t      status = MCAPI_SUCCESS;
    MCAPI_ENDPOINT      *rx_end_ptr;
    MCAPI_GLOBAL_DATA   *node_data;

    /* Get a pointer to the node data. */
    node_data = mcapi_get_node_data();

    /* Get a pointer to the endpoint. */
    rx_end_ptr = mcapi_find_local_endpoint(node_data,
                                           tx_end_ptr->mcapi_foreign_node_id,
                                           tx_end_ptr->mcapi_foreign_port_id);

    /* If the endpoint was found. */
    if (rx_end_ptr)
    {
        /* Get a buffer for this data. */
        new_buf = tx_end_ptr->mcapi_route->mcapi_rt_int->
            mcapi_get_buffer(tx_end_ptr->mcapi_foreign_node_id, buffer->buf_size, priority);

        /* If there is a buffer available. */
        if (new_buf)
        {
            /* Save a pointer to the rx interface. */
            new_buf->mcapi_dev_ptr =
                (MCAPI_POINTER)(tx_end_ptr->mcapi_route->mcapi_rt_int);

            /* Copy the data into the new buffer. */
            memcpy(new_buf->buf_ptr, buffer->buf_ptr, buffer->buf_size);

            /* Set the length. */
            new_buf->buf_size = buffer->buf_size;

            /* Enqueue the new buffer onto the receive buffer. */
            mcapi_enqueue(&rx_end_ptr->mcapi_rx_queue, new_buf);

            /* Check if any tasks are waiting for data to be transmitted from
             * this endpoint.
             */
            mcapi_check_resume(MCAPI_REQ_TX_FIN, tx_end_ptr->mcapi_endp_handle,
                               MCAPI_NULL, buffer->buf_size - MCAPI_HEADER_LEN,
                               MCAPI_SUCCESS);

            /* Check if any tasks are waiting to receive data on this
             * endpoint.
             */
            mcapi_check_resume(MCAPI_REQ_RX_FIN, rx_end_ptr->mcapi_endp_handle,
                               rx_end_ptr, new_buf->buf_size - MCAPI_HEADER_LEN,
                               MCAPI_SUCCESS);

            /* Free the buffer that has been successfully transmitted. */
            ((MCAPI_INTERFACE*)(buffer->mcapi_dev_ptr))->
                mcapi_recover_buffer(buffer);
        }

        else
        {
            status = MCAPI_ENO_BUFFER;
        }
    }

    /* The port is invalid. */
    else
    {
        status = MCAPI_ENOT_ENDP;
    }

    return (status);

}

/*************************************************************************
*
*   FUNCTION
*
*       mcapi_loop_ioctl
*
*   DESCRIPTION
*
*       IOCTL routine for the loopback interface.
*
*   INPUTS
*
*       optname                 The name of the IOCTL option.
*       *option                 A pointer to memory that will be
*                               filled in if this is a GET option
*                               or the new value if this is a SET
*                               option.
*       optlen                  The length of the memory at option.
*
*   OUTPUTS
*
*       MCAPI_SUCCESS           The call was successful.
*       MCAPI_EATTR_NUM         Unrecognized option.
*       MCAPI_EATTR_SIZE        The size of option is invalid.
*
*************************************************************************/
mcapi_status_t mcapi_loop_ioctl(mcapi_uint_t optname, void *option,
                                size_t optlen)
{
    mcapi_status_t  status = MCAPI_SUCCESS;

    switch (optname)
    {
        /* The total number of buffers in the system. */
        case MCAPI_ATTR_NO_BUFFERS:

            /* Ensure the buffer can hold the value. */
            if (optlen >= sizeof(mcapi_uint32_t))
            {
                *(mcapi_uint32_t *)option = MCAPI_BUF_COUNT;
            }

            else
            {
                status = MCAPI_EATTR_SIZE;
            }

            break;

        /* The maximum size of an interface buffer. */
        case MCAPI_ATTR_BUFFER_SIZE:

            /* Ensure the buffer can hold the value. */
            if (optlen >= sizeof(mcapi_uint32_t))
            {
                *(mcapi_uint32_t *)option = MCAPI_MAX_DATA_LEN;
            }

            else
            {
                status = MCAPI_EATTR_SIZE;
            }

            break;

        /* The number of buffers available for receiving data. */
        case MCAPI_ATTR_RECV_BUFFERS_AVAILABLE:

            /* Ensure the buffer can hold the value. */
            if (optlen >= sizeof(mcapi_uint32_t))
            {
                *(mcapi_uint32_t *)option = MCAPI_Buf_Count;
            }

            else
            {
                status = MCAPI_EATTR_SIZE;
            }

            break;

        case MCAPI_ATTR_NO_PRIORITIES:

            /* Ensure the buffer can hold the value. */
            if (optlen >= sizeof(mcapi_uint32_t))
            {
                /* The loopback interface does not prioritize packets. */
                *(mcapi_uint32_t *)option = 1;
            }

            else
            {
                status = MCAPI_EATTR_SIZE;
            }

            break;

        default:

            status = MCAPI_EATTR_NUM;
            break;
    }

    return (status);

}

#endif
