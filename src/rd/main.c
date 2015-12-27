#include <hiredis/hiredis.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <log.h>

extern int load_env(const char *[], char *[], const char *[]);

extern int  simple_signum(void);
extern void simple_handler(int);
extern void simple_signal(int, void(*)(int));

extern redisContext *rd_connect(const char *ip, int port);
extern void rd_free(redisContext *ctx);

/* global config options */
char lint[64]; /* logging interval */
char home[64]; /* home directory */
char user[64]; /* current user */

/* redis options */
char          rd_ip[64];     /* redis ip address */
char          rd_port[64];   /* redis port */
redisContext *rd_ctx = NULL; /* redis connection context */

static void cleanup(void)
{
	rd_free(rd_ctx);
	rd_ctx = NULL;
}

static void configure(void)
{
	const char *keys[] = {
		"HOME",
		"USER",
		"_12LINT",
		"_12RDIP",
		"_12RDPORT",
		NULL
	};
	char *vals[] = {
		home,
		user,
		lint,
		rd_ip,
		rd_port,
		NULL
	};
	const char *defaults[] = {
		NULL,
		NULL,
		"1",
		"localhost",
		"6379",
		NULL
	};
	load_env(keys, vals, defaults);
}

int main(int argc, char *argv[])
{
	argc = argc;
	simple_signal(SIGINT,  simple_handler);
	simple_signal(SIGTERM, simple_handler);
	simple_signal(SIGALRM, simple_handler);
	int signum = 0;
	int interval = 0;
	int port = 0;

	/* From 12 factor:
	   "each running process writes its event stream, unbuffered, to stdout" */
	setvbuf(stdout, NULL, _IONBF, 0);
	LOG("--- %s (%d) starting ---", argv[0], getpid());
	configure();
	if (lint[0] != '\0') {
		interval = atoi(lint);
	}
	if (rd_port[0] != '\0') {
		port = atoi(rd_port);
	}
	rd_ctx = rd_connect(rd_ip, port);
	while (1) {
		LOG("%s running ...", argv[0]);
		alarm(interval);
		pause();
		signum = simple_signum();
		if (signum && signum != SIGALRM)
			break;
	}
	LOG("--- %s (%d) stopping ---", argv[0], getpid());
	cleanup();
	return 128 + signum;
}
