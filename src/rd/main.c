#include <hiredis/hiredis.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <log.h>

extern int  simple_signum(void);
extern void simple_handler(int);
extern void simple_signal(int, void(*)(int));

extern redisContext *rd_connect(const char *ip, int port);
extern void rd_free(redisContext *ctx);

/* global config options */
unsigned int lint = 0;    /* logging interval */
char        *home = NULL; /* home directory */
char        *user = NULL; /* current user */

/* redis options */
char         *rd_ip   = NULL; /* redis ip address */
int           rd_port = 0;    /* redis port */
redisContext *rd_ctx    = NULL; /* redis connection context */

static void cleanup(void)
{
	free(home);
	free(user);
	home = user = NULL;
	rd_free(rd_ctx);
	rd_ctx = NULL;
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

	/* redis IP */
	key = getenv("_12RDIP");
	if (key) {
		rd_ip = strdup(key);
	} else {
		rd_ip = strdup("127.0.0.1");
	}

	/* redis port */
	key = getenv("_12RDPORT");
	if (key) {
		rd_port = atoi(key);
	} else {
		rd_port = 6379;
	}
}

int main(int argc, char *argv[])
{
	argc = argc;
	simple_signal(SIGINT,  simple_handler);
	simple_signal(SIGTERM, simple_handler);
	simple_signal(SIGALRM, simple_handler);
	int signum = 0;

	/* From 12 factor:
	   "each running process writes its event stream, unbuffered, to stdout" */
	setvbuf(stdout, NULL, _IONBF, 0);
	LOG("--- %s (%d) starting ---", argv[0], getpid());
	configure();
	rd_ctx = rd_connect(rd_ip, rd_port);
	while (1) {
		LOG("%s running ...", argv[0]);
		alarm(lint);
		pause();
		signum = simple_signum();
		if (signum && signum != SIGALRM)
			break;
	}
	LOG("--- %s (%d) stopping ---", argv[0], getpid());
	cleanup();
	return 128 + signum;
}
