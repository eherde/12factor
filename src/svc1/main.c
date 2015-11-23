#include <stdlib.h>
#include <unistd.h>

char *home = NULL;
char *user = NULL;

int main(void)
{
	home = getenv("HOME");
	user = getenv("USER");
	pause();
	return 0;
}
