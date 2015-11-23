#ifndef _12LOG_
#define _12LOG_
extern int utcstr(char *buf, size_t len);
char timestr[64];
#define LOG(_fmt, ...) do {                                 \
	utcstr(timestr, sizeof(timestr));                   \
	printf("[%s] "_fmt "\n", timestr, __VA_ARGS__);    \
} while (0)
#endif
