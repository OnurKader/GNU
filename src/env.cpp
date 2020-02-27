#include <cstdio>
#include <unistd.h>

int main()
{
	printf("\033[38;2;226;255;230m");
	for(size_t i = 0ULL; environ[i]; ++i)
		printf("%s\n", environ[i]);

	printf("\033[m");

	return 0;
}
