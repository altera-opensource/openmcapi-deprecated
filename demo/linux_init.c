#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include <mcapi.h>

extern void startup(int node);
extern void demo(int node);

static struct sigaction oldactions[32];

static void cleanup(void)
{
	mcapi_status_t status;

	printf("%s\n", __func__);
	mcapi_finalize(&status);
}

static void signalled(int signal, siginfo_t *info, void *context)
{
	struct sigaction *action;

	cleanup();

	action = &oldactions[signal];

	if ((action->sa_flags & SA_SIGINFO) && action->sa_sigaction)
		action->sa_sigaction(signal, info, context);
	else if (action->sa_handler)
		action->sa_handler(signal);
	
	exit(signal);
}

struct sigaction action = {
	.sa_sigaction = signalled,
	.sa_flags = SA_SIGINFO,
};

int main(int argc, char *argv[])
{
	unsigned long node;

	if (argc < 2) {
		printf("Usage: %s <node id>\n", argv[0]);
		return -1;
	}

	atexit(cleanup);
	sigaction(SIGQUIT, &action, &oldactions[SIGQUIT]);
	sigaction(SIGABRT, &action, &oldactions[SIGABRT]);
	sigaction(SIGTERM, &action, &oldactions[SIGTERM]);
	sigaction(SIGINT,  &action, &oldactions[SIGINT]);

	node = strtoul(argv[1], NULL, 0);
	printf("node %ld\n", node);

	startup(node);

	demo(node);

	return 0;
}
