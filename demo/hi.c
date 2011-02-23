#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

#include <mcapi.h>

#define WAIT_TIMEOUT 0xFFFFFFFF

#define mcapi_assert_success(s) \
	if (s != MCAPI_SUCCESS) { printf("%s:%d status %d\n", __FILE__, __LINE__, s); abort(); }
	
static const struct {
	int tx;
	int rx;
} ports[2] = {
	{ 1000, 1001 },
	{ 2000, 2001 },
};

mcapi_pktchan_recv_hndl_t	send_handle;
mcapi_pktchan_recv_hndl_t	recv_handle;

static void connect(int local, int remote)
{
	mcapi_endpoint_t local_send_endpoint; 
	mcapi_endpoint_t local_recv_endpoint;
	mcapi_endpoint_t remote_recv_endpoint;
	mcapi_request_t  request;
	mcapi_request_t  send_request;
	mcapi_request_t  recv_request;
	mcapi_status_t   status;
	size_t           size;
	int              i;
	
	printf("\nLinux: MCAPI Initialization \n");

	printf("Linux: Creating tx port %d\n", ports[local].tx);
	local_send_endpoint = mcapi_create_endpoint(ports[local].tx, &status);
	mcapi_assert_success(status);

	printf("Linux: Creating rx port %d\n", ports[local].rx);
	local_recv_endpoint = mcapi_create_endpoint(ports[local].rx, &status);
	mcapi_assert_success(status);

	for (i = 0; i < 60; i++) {
		remote_recv_endpoint = mcapi_get_endpoint(remote, ports[remote].rx,
		                                          &status);
		if (!status)
			break;

		printf("Linux: Waiting for remote RX endpoint %d (status %d)\n",
		       ports[remote].rx, status);

		sleep(1);
	}
	mcapi_assert_success(status);

	printf("Linux: Connecting %d:%d to %d:%d\n", local, ports[local].tx,
	       remote, ports[remote].rx);
	mcapi_connect_pktchan_i(local_send_endpoint, remote_recv_endpoint,
	                        &request, &status);
	mcapi_assert_success(status);

	mcapi_wait(&request, &size, &status, WAIT_TIMEOUT);	
	mcapi_assert_success(status);

	printf("Linux: Connection complete\n");

	printf("Linux: Opening send endpoint\n");
	mcapi_open_pktchan_send_i(&send_handle, local_send_endpoint, &send_request,
							  &status);

	printf("Linux: Opening receive endpoint\n");
	mcapi_open_pktchan_recv_i(&recv_handle, local_recv_endpoint, &recv_request,
							  &status);

	mcapi_wait(&send_request, &size, &status, WAIT_TIMEOUT);	
	mcapi_assert_success(status);

	mcapi_wait(&recv_request, &size, &status, WAIT_TIMEOUT);	
	mcapi_assert_success(status);
	
	printf("Linux: MCAPI negotiation complete! \n");
}

void startup(unsigned int local)
{
	mcapi_status_t status;
	mcapi_version_t version;
	unsigned int remote;

	remote = !local;
	local = !remote; /* ensure it's either 0 or 1 */

	mcapi_initialize(local, &version, &status);
	mcapi_assert_success(status);

	connect(local, remote);
}

void demo(int node)
{
	char outgoing[16];
	char *incoming;
	size_t bytes;
	mcapi_status_t status;

	memset(outgoing, 0, 16);
	sprintf(outgoing, "hi from node %d", node);

	mcapi_pktchan_send(send_handle, outgoing, strlen(outgoing)+1, &status);
	mcapi_assert_success(status);

	mcapi_pktchan_recv(recv_handle, (void *)&incoming, &bytes, &status);
	printf("received message: %s\n", incoming);
}
