#include <cstdio>
#include <cstdlib>
#include <string>
#include "string_utils.hpp"

int main()
{
	char* path = getenv("PATH");
	if(!path)
	{
		fprintf(stderr, "Couldn't get $PATH\n");
		return 1;
	}

	replace(path, ':', '\n');

	printf("%s\n", path);

	return 0;
}
