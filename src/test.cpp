#include "string_utils.hpp"

#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	char str[] = "Hello World!! My name is Onur!!    !Yeah!!Science Bitch!";
	std::vector<const char*> words = split(str, "! ");
	for(auto& word: words)
	{
		printf("%s\n", word);
	}
	printf("Size: %lu\n", words.size());
	return 0;
}

