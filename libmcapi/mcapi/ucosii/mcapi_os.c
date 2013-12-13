/*
 * Copyright (c) 2013, Altera Corportation
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
#include <ucos_ii.h>

#define DEF_TIME_NBR_mS_PER_SEC		(1000)
#define TASK_CONDITION_SUSPEND		(0x2)
#define TIMEOUT_INFINITE		(0)
#define MCAPI_MUTEX_PIP			(2)

MCAPI_MUTEX MCAPI_Mutex;

static OS_STK task_stack[MCAPI_TASK_STACK_SIZE] __attribute__ ((aligned (4)));


/*
 * Inline function to convert time to clock ticks
 */
static inline int ms_to_ticks(int ms)
{
	return ((ms * OS_TICKS_PER_SEC + (DEF_TIME_NBR_mS_PER_SEC - 1))
		/ DEF_TIME_NBR_mS_PER_SEC);
}

/*************************************************************************
*
*   FUNCTION
*
*       MCAPI_Init_OS
*
*   DESCRIPTION
*
*       Initializes OS specific data structures.
*
*   INPUTS
*
*       None.
*
*   OUTPUTS
*
*       MCAPI_SUCCESS
*       MCAPI_OS_ERROR
*
*************************************************************************/
mcapi_status_t MCAPI_Init_OS(void)
{
#if (OS_TASK_NAME_EN > 0u)
	CPU_INT08U  os_err;
#endif
	INT8U status;

	/* Create the task that will be used for receiving status
	 * messages.
	 */
	status = OSTaskCreate(mcapi_process_ctrl_msg, NULL,
			&task_stack[MCAPI_TASK_STACK_SIZE -1 ],
			MCAPI_CONTROL_TASK_PRIO);

	if (status != OS_ERR_NONE)
		return MCAPI_OS_ERROR;

#if (OS_TASK_NAME_EN > 0u)
	OSTaskNameSet(MCAPI_CONTROL_TASK_PRIO, (INT8U *)"mcapi_proc_ctrl_msg",
		&os_err);
#endif

	return MCAPI_SUCCESS;
}

/*************************************************************************
*
*   FUNCTION
*
*       MCAPI_Exit_OS
*
*   DESCRIPTION
*
*       Release OS specific data structures.
*
*   INPUTS
*
*       None.
*
*   OUTPUTS
*
*       None.
*
*************************************************************************/
void MCAPI_Exit_OS(void)
{
}

/*************************************************************************
*
*   FUNCTION
*
*       MCAPI_Resume_Task
*
*   DESCRIPTION
*
*       Resumes a suspended system task.
*
*   INPUTS
*
*       *request                The request structure on which the
*                               suspended task is suspended.
*
*   OUTPUTS
*
*       MCAPI_SUCCESS
*       MCAPI_OS_ERROR
*
*************************************************************************/
mcapi_status_t MCAPI_Resume_Task(mcapi_request_t *request)
{
	INT8U status;

	/* If multiple requests are suspending on the same condition, we use
	 * mcapi_cond_ptr. */
	if (request->mcapi_cond.mcapi_cond_ptr)
		OSFlagPost(*request->mcapi_cond.mcapi_cond_ptr,
			TASK_CONDITION_SUSPEND,
			OS_FLAG_SET,
			&status);
	else
		OSFlagPost(request->mcapi_cond.mcapi_cond,
			TASK_CONDITION_SUSPEND,
			OS_FLAG_SET,
			&status);

	if (status != OS_ERR_NONE)
		return MCAPI_OS_ERROR;

	return MCAPI_SUCCESS;
}

/*************************************************************************
*
*   FUNCTION
*
*       MCAPI_Suspend_Task
*
*   DESCRIPTION
*
*       Suspends a system task.
*
*   INPUTS
*
*       *node_data              A pointer to the global node data
*                               structure.
*       *request                A pointer to the request associated
*                               with the thread being suspended.
*       *mcapi_os               A pointer to the OS specific structure
*                               containing suspend/resume data.
*       timeout                 The number of milliseconds to suspend
*                               pending completion of the request.
*
*   OUTPUTS
*
*       MCAPI_SUCCESS
*       MCAPI_OS_ERROR
*
*************************************************************************/
mcapi_status_t MCAPI_Suspend_Task(MCAPI_GLOBAL_DATA *node_data,
                                  mcapi_request_t *request,
                                  MCAPI_COND_STRUCT *condition,
                                  mcapi_timeout_t timeout)
{
	INT8U status = -1;
	INT16U os_timeout;

	/* If a request structure was passed into the routine. */
	if (request)
	{
		MCAPI_Init_Condition(&request->mcapi_cond);

		if (request->mcapi_cond.mcapi_cond)
		{
			status = 0;

			/* Add the request to the queue of pending requests. */
			mcapi_enqueue(&node_data->mcapi_local_req_queue,
					request);
		}
	}

	if (status == 0)
	{
		/* If no timeout value was specified. */
		if (timeout == MCAPI_INFINITE)
		{
			os_timeout = 0;
		}
		else
		{
			/* Convert timeout in ms to OS timer ticks, OSFlagPend
			   operate on timer ticks */
			os_timeout =  ms_to_ticks(timeout);
		}

		MCAPI_Release_Mutex(&MCAPI_Mutex);

		OSFlagPend(request->mcapi_cond.mcapi_cond,
			TASK_CONDITION_SUSPEND,
			OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME,
			os_timeout, &status);

		MCAPI_Obtain_Mutex(&MCAPI_Mutex);

		/* Uninitialize the condition variable. */
		MCAPI_Destroy_Condition(&request->mcapi_cond);
	}

	if (status != OS_ERR_NONE)
		return MCAPI_OS_ERROR;

	return MCAPI_SUCCESS;
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       MCAPI_Cleanup_Task
 *
 *   DESCRIPTION
 *
 *       Terminates the current thread.
 *
 *   INPUTS
 *
 *       None.
 *
 *   OUTPUTS
 *
 *       None.
 *
 *************************************************************************/
void MCAPI_Cleanup_Task(void)
{
	OSTaskDel(MCAPI_CONTROL_TASK_PRIO);
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       MCAPI_Init_Condition
 *
 *   DESCRIPTION
 *
 *       Sets an OS specific condition for resuming a task in the future.
 *
 *   INPUTS
 *
 *       *os_cond                A pointer to the OS specific structure
 *                               containing suspend/resume data.
 *
 *   OUTPUTS
 *
 *       None.
 *
 *************************************************************************/
void MCAPI_Init_Condition(MCAPI_COND_STRUCT *condition)
{
	INT8U status;
	/* Initialize the condition variable with default parameters. */
	condition->mcapi_cond = OSFlagCreate(0, &status);
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       MCAPI_Destroy_Condition
 *
 *   DESCRIPTION
 *
 *       Destroy an OS specific condition.
 *
 *   INPUTS
 *
 *       *os_cond                A pointer to the OS specific structure
 *                               containing suspend/resume data.
 *
 *   OUTPUTS
 *
 *       OS_ERR_NONE
 *
 *************************************************************************/
mcapi_status_t MCAPI_Destroy_Condition(MCAPI_COND_STRUCT *condition)
{
	INT8U status;

	if (condition->mcapi_cond != MCAPI_NULL) {
		condition->mcapi_cond = OSFlagDel(condition->mcapi_cond,
			OS_DEL_NO_PEND, &status);
	}

	if (status != OS_ERR_NONE)
		return MCAPI_OS_ERROR;

	return MCAPI_SUCCESS;
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       MCAPI_Set_Condition
 *
 *   DESCRIPTION
 *
 *       Sets an OS specific condition for resuming a task in the future.
 *
 *   INPUTS
 *
 *       *request                A request structure that will trigger
 *                               a future task resume.
 *       *os_cond                The condition to use for resuming the
 *                               task.
 *
 *   OUTPUTS
 *
 *       None.
 *
 *************************************************************************/
void MCAPI_Set_Condition(mcapi_request_t *request, MCAPI_COND_STRUCT *condition)
{
	request->mcapi_cond.mcapi_cond_ptr = &condition->mcapi_cond;
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       MCAPI_Clear_Condition
 *
 *   DESCRIPTION
 *
 *       Clears a previously set OS condition.
 *
 *   INPUTS
 *
 *       *request                A request structure that will trigger
 *                               a future task resume.
 *
 *   OUTPUTS
 *
 *       None.
 *
 *************************************************************************/
void MCAPI_Clear_Condition(mcapi_request_t *request)
{
	request->mcapi_cond.mcapi_cond_ptr = MCAPI_NULL;
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       MCAPI_Create_Mutex
 *
 *   DESCRIPTION
 *
 *       Creates a system mutex.
 *
 *   INPUTS
 *
 *       *mutex                  Pointer to the mutex control block.
 *       *name                   Name of the mutex.
 *
 *   OUTPUTS
 *
 *       MCAPI_SUCCESS
 *
 *************************************************************************/
mcapi_status_t MCAPI_Create_Mutex(MCAPI_MUTEX *mutex, char *name)
{
	INT8U status;

	*mutex = OSMutexCreate(MCAPI_MUTEX_PIP, &status);

	if (status != OS_ERR_NONE)
		return MCAPI_OS_ERROR;

	return MCAPI_SUCCESS;
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       MCAPI_Delete_Mutex
 *
 *   DESCRIPTION
 *
 *       Destroyes a system mutex.
 *
 *   INPUTS
 *
 *       *mutex                  Pointer to the mutex control block.
 *
 *   OUTPUTS
 *
 *       MCAPI_SUCCESS
 *       MCAPI_OS_ERROR
 *
 *************************************************************************/
mcapi_status_t MCAPI_Delete_Mutex(MCAPI_MUTEX *mutex)
{
	INT8U status;

	OSMutexDel(*mutex, OS_DEL_NO_PEND, &status);

	if (status != OS_ERR_NONE)
		return MCAPI_OS_ERROR;

	return MCAPI_SUCCESS;
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       MCAPI_Obtain_Mutex
 *
 *   DESCRIPTION
 *
 *       Obtains a system mutex.
 *
 *   INPUTS
 *
 *       *mutex              Pointer to the mutex control block.
 *
 *   OUTPUTS
 *
 *       MCAPI_SUCCESS
 *       MCAPI_OS_ERROR
 *
 *************************************************************************/
mcapi_status_t MCAPI_Obtain_Mutex(MCAPI_MUTEX *mutex)
{
	INT8U status;

	OSMutexPend(*mutex, TIMEOUT_INFINITE, &status);
	if (status != OS_ERR_NONE)
		return MCAPI_OS_ERROR;

	return MCAPI_SUCCESS;
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       MCAPI_Release_Mutex
 *
 *   DESCRIPTION
 *
 *       Releases a system mutex.
 *
 *   INPUTS
 *
 *       *mutex              Pointer to the mutex control block.
 *
 *   OUTPUTS
 *
 *       MCAPI_SUCCESS
 *       MCAPI_OS_ERROR
 *
 *************************************************************************/
mcapi_status_t MCAPI_Release_Mutex(MCAPI_MUTEX *mutex)
{
	if (OSMutexPost(*mutex) != OS_ERR_NONE)
		return MCAPI_OS_ERROR;

	return MCAPI_SUCCESS;
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       MCAPI_Set_RX_Event
 *
 *   DESCRIPTION
 *
 *       Sets an event indicating that data is ready to be received.
 *
 *   INPUTS
 *
 *       None.
 *
 *   OUTPUTS
 *
 *       MCAPI_SUCCESS
 *
 *************************************************************************/
mcapi_status_t MCAPI_Set_RX_Event(void)
{
	mcapi_rx_data();

	return MCAPI_SUCCESS;
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       MCAPI_Lock_RX_Queue
 *
 *   DESCRIPTION
 *
 *       Protect RX queue from concurrent accesses.  No work is required
 *       in this routine since Linux receives data from the context of
 *       the driver RX thread.
 *
 *   INPUTS
 *
 *       None.
 *
 *   OUTPUTS
 *
 *       Unused.
 *
 *************************************************************************/
mcapi_int_t MCAPI_Lock_RX_Queue(void)
{
	return 0;
}

/*************************************************************************
 *
 *   FUNCTION
 *
 *       MCAPI_Unlock_RX_Queue
 *
 *   DESCRIPTION
 *
 *       Protect RX queue from concurrent accesses.  No work is required
 *       in this routine since Linux receives data from the context of
 *       the driver RX thread.
 *
 *   INPUTS
 *
 *       cookie                  Unused.
 *
 *   OUTPUTS
 *
 *       None.
 *
 *************************************************************************/
void MCAPI_Unlock_RX_Queue(mcapi_int_t cookie)
{
}

void MCAPI_Sleep(unsigned int secs)
{
	OSTimeDlyHMSM(0, 0, secs, 0);
}

