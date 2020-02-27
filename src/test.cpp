#include <cstdio>
#include <cstdlib>
#include "string_utils.hpp"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	const char* str = "Hello World!! My name is Onur!! Yeah!!Science Bitch!";
	std::vector<const char*> words = split(str, "! ");
	for(auto& word: words)
	{
		printf("%s\n", word);
	}
	printf("Size: %lu\n", words.size());
	return 0;
}

