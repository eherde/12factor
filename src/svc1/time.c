#include <time.h>

#define UTC_FMT "%a %b %e %H:%M:%S UTC %Y"

int utcstr(char *buf, size_t len)
{
	time_t now = 0;
	struct tm nowtm;
	int rv = -1;
	if (!buf)
		goto out;
	now = time(NULL);
	if (now == 0)
		goto out;
	if (gmtime_r(&now, &nowtm) == NULL)
		goto out;
	if (strftime(buf, len, UTC_FMT, &nowtm) == 0)
		goto out;
	rv = 0;
out:
	return rv;
}
