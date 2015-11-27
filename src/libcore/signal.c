#include <signal.h>
#include <strings.h>

static volatile int _simple_signum;

int simple_signum(void)
{
	return _simple_signum;
}

void simple_handler(int signum)
{
	_simple_signum = signum;
}

void simple_signal(int signum, void(*handler)(int))
{
	struct sigaction sigact;
	bzero(&sigact, sizeof(struct sigaction));
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigact.sa_handler = handler;
	sigaction(signum, &sigact, 0);
	return;
}
