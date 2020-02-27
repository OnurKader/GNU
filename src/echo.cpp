#include <cstdio>
#include <getopt.h>
#include <unistd.h>

/*
 * No -e, ANSI Escape character support, just a simple echo
 * with a newline option available, might use this one meself
 */

void usage()
{
	fprintf(stderr,
			"echo [text]...\n"
			"Can also be called with '-n' to not print a newline character "
			"at the end\n");
}

int main(int argc, char **argv)
{
	bool new_line = true;

	int opt;
	while((opt = getopt(argc, argv, "hn")) != -1)
	{
		switch(opt)
		{
			case 'n': new_line = false; break;
			case 'h':
			default: usage(); return 1;
		}
	}

	int start_index = new_line ? 1 : 2;
	for(int i = start_index; i < argc; ++i)
	{
		fputs(argv[i], stdout);
		if(i != argc - 1)
			fputc(' ', stdout);
	}

	if(new_line)
		printf("\n");

	return 0;
}
