#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		fprintf(stderr, "\033[31;1mUsage: mkdir [directory]...\033[m\n");
		return 1;
	}

	for(int i = 1; i < argc; ++i)
	{
		if(mkdir(argv[i], 0775) < 0)
		{
			perror("mkdir");
			return 1;
		}
	}

	return 0;
}
