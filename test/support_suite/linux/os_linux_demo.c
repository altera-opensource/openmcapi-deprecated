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
*       os_linux_demo.c
*
*
*************************************************************************/
#include <pthread.h>
#include "mcapid.h"
#include "support_suite/mcapid_support.h"

/************************************************************************
*
*   FUNCTION
*
*       MCAPID_Create_Thread
*
*   DESCRIPTION
*
*       This routine creates a Linux thread.
*
*************************************************************************/
mcapi_status_t MCAPID_Create_Thread(MCAPI_THREAD_PTR_ENTRY(thread_entry), MCAPID_STRUCT *mcapi_struct)
{
    int             status;

    /* Initialize the state. */
    mcapi_struct->state = -1;

    /* Create the thread, passing the mcapi_struct parameter into
     * the new thread.
     */
    status = pthread_create(&mcapi_struct->task_ptr, NULL,
                            thread_entry, (void*)mcapi_struct);

    mcapi_struct->status = status;

    return (status);

} /* MCAPID_Create_Thread */

/************************************************************************
*
*   FUNCTION
*
*       MCAPID_Cleanup
*
*   DESCRIPTION
*
*       This routine destroys a Linux thread.  Since Linux threads
*       are destroyed upon completion, there is no work required
*       of this routine.
*
*************************************************************************/
void MCAPID_Cleanup(MCAPID_STRUCT *mcapi_struct)
{
    /* Delete the local endpoint. */
    mcapi_delete_endpoint(mcapi_struct->local_endp, &mcapi_struct->status);

} /* MCAPID_Cleanup */

/************************************************************************
*
*   FUNCTION
*
*       MCAPID_Sleep
*
*   DESCRIPTION
*
*       Sleep routine used for pausing as indicated by the user.
*
*************************************************************************/
void MCAPID_Sleep(unsigned how_long)
{
    if (how_long)
    {
        sleep((how_long/1000));
    }

} /* MCAPID_Sleep */
