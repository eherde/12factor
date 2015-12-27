#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <log.h>

#define ENVMAX 64

extern size_t strlcpy(char *dst, const char *src, size_t dsize);

int load_env(const char *keys[], char *vals[], const char *defaults[])
{
	int i;
	char *val;
	for (i = 0; keys[i]; i++) {
		val = getenv(keys[i]);
		if (val) {
			if (strlen(val) > ENVMAX) {
				LOG("value of env var %s too large, truncating",
					keys[i]);
			}
			strlcpy(vals[i], val, ENVMAX);
		} else {
			LOG("missing environment variable %s", keys[i]);
			if (defaults[i]) {
				strlcpy(vals[i], defaults[i], ENVMAX);
			} else {
				vals[i][0] = '\0';
			}
		}
	}
	return 0;
}
