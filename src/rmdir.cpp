#include <cerrno>
#include <cstdio>
#include <unistd.h>

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		fprintf(stderr, "\033[31;1mUsage: rmdir [directory]...\033[m\n");
		return 1;
	}
	for(int i = 1; i < argc; ++i)
	{
		if(rmdir(argv[i]) < 0)
		{
			perror("rmdir");
			return 1;
		}
	}

	return 0;
}
