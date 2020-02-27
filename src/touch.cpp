#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		fprintf(stderr, "\033[1;31mUsage: touch [filename]\033[m\n");
		return 1;
	}

	struct stat status;
	// stat or lstat, any reason to follow links?
	int ret_val = lstat(argv[1], &status);
	if(ret_val == 0)
	{
		// File exists, update time
		// Turns out there is already a function for that
		utime(argv[1], nullptr);
	}
	else if(ret_val < 0)
	{
		if(errno == ENOENT || errno == EACCES)
		{
			int fd = open(argv[1], O_CREAT, 0100664);
			if(fd < 0)
			{
				perror("open");
				return 1;
			}
			close(fd);
		}
	}

	return 0;
}
