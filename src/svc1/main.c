#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <log.h>

/* global config options */
unsigned int lint = 0;    /* logging interval */
char        *home = NULL; /* home directory */
char        *user = NULL; /* current user */

int g_signum = 0;

static void handler(int signum)
{
	g_signum = signum;
}

static void cleanup(void)
{
	free(home);
	free(user);
	home = user = NULL;
}

static void configure(void)
{
	char *key = NULL;

	key = getenv("HOME");
	if (key)
		home = strdup(key);

	key = getenv("USER");
	if (key)
		user = strdup(key);

	/* logging interval */
	key = getenv("_12LINT");
	if (key) {
		lint = atoi(key);
	} else {
		lint = 1;
	}
}

int main(int argc, char *argv[])
{
	argc = argc;
	struct sigaction sigact;
	sigact.sa_handler = handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGTERM, &sigact, NULL);
	sigaction(SIGALRM, &sigact, NULL);

	/* From 12 factor:
	   "each running process writes its event stream, unbuffered, to stdout" */
	setvbuf(stdout, NULL, _IONBF, 0);

	LOG("--- %s (%d) starting ---", argv[0], getpid());
	configure();
	while (1) {
		LOG("%s running ...", argv[0]);
		alarm(lint);
		pause();
		if (g_signum && g_signum != SIGALRM)
			break;
	}
	LOG("--- %s (%d) stopping ---", argv[0], getpid());
	cleanup();
	return 128 + g_signum;
}
