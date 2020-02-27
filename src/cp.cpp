#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fcntl.h>
#include <getopt.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

#define usage() fprintf(stderr, "\033[1;31mUsage: cp [source]... [destination]\033[m\n")

void handle_dir_copy(const char* src, const char* dest);
void handle_file_copy(const char* src, const char* dest, struct stat& status, int fd);

int main(int argc, char** argv)
{
	if(argc < 3)
	{
		usage();
	}

	bool recursive = false;
	std::vector<const char*> sources;
	const char* destination = NULL;
	size_t source_start_index = 1ULL;

	{
		int c;

		while((c = getopt(argc, argv, "r")) != -1)
		{
			switch(c)
			{
				case 'r':
					recursive = true;
					++source_start_index;
					break;
				default: usage();
			}
		}
	}

	// Get the sources into the vector
	for(int i = source_start_index; i < argc - 1; ++i)
		sources.push_back(argv[i]);

	destination = argv[argc - 1];
	for(auto& source: sources)
	{
		int fd = open(source, O_RDONLY);
		if(fd < 0)
		{
			perror("open");
			return 1;
		}

		struct stat status;
		if(fstat(fd, &status) < 0)
		{
			perror("fstat");
			return 1;
		}

		if(S_ISDIR(status.st_mode))
		{
			// Path is a directory, check for -r flag
			if(!recursive)
			{
				fprintf(stderr,
						"cp: recursive flag -r not entered, not copying directory \"%s\"\n",
						source);
				return 1;
			}
			handle_dir_copy(source, destination);
		}
		handle_file_copy(source, destination, status, fd);
	}

	return 0;
}

void handle_dir_copy(const char* src, const char* dest)
{
	if(mkdir(dest, 0775) < 0)
	{
		perror("mkdir");
		return;
	}
	// TODO dirent
}

void handle_file_copy(const char* src, const char* dest, struct stat& status, int fd)
{
	int orig_file_perms = (status.st_mode & S_IRWXU) |
						  (status.st_mode & S_IRWXG) |
						  (status.st_mode & S_IRWXO);
	if(creat(dest, orig_file_perms) < 0)
	{
		perror("creat");
		return;
	}
	// Two Filenames (512) and a slash '/' makes 513
	char rel_path[256 + 1 + 256];
	strcpy(rel_path, dest);
	strncat(rel_path, "/", 1);
	strcat(rel_path, src);
}

