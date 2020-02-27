#pragma once
#include <cstring>
#include <vector>

void replace(char* str, char removal, char added)
{
	while(*(str++) != '\0')
		if(*str == removal)
			*str = added;
}

std::vector<const char*> split(const char* str, const char* delimiter)
{
	std::vector<const char*> parts;

	char* dup_str = strdup(str);
	const char* tok = strtok(dup_str, delimiter);
	parts.push_back(tok);
	while((tok = strtok(nullptr, delimiter)))
		parts.push_back(tok);
	return parts;
}

std::vector<const char*> split(const char* str, const char c)
{
	const char delimiter[1] = {c};
	return split(str, delimiter);
}

