#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

int main(int argc, char** argv)
{
	std::vector<int> fd_vec;
	if(argc > 1)
	{
		for(int i = 1; i < argc; ++i)
		{
			int fd;
			if((fd = open(argv[i], O_RDONLY)) == -1)
			{
				fprintf(stderr, "Could not open file: %s: %s\n", argv[i], strerror(errno));
				continue;
			}
			fd_vec.push_back(fd);
		}
	}
	else
		// Just read from STDIN
		fd_vec.push_back(0);

	for(const int& fd: fd_vec)
	{
		while(true)
		{
			char buffer[1U << 15U];
			ssize_t read_count = read(fd, buffer, sizeof(buffer));
			if(read_count < 0)
			{
				perror("read");
				return errno;
			}
			if(read_count == 0)	   // Reached the End
				break;
			ssize_t write_count = write(STDOUT_FILENO, buffer, read_count);
			if(write_count < 0)
			{
				perror("write");
				return errno;
			}
			if(read_count != write_count)
			{
				fprintf(stderr, "Something went wrong!\n");
				return 2;
			}
		}
		close(fd);
		printf("\n");
	}

	return 0;
}

