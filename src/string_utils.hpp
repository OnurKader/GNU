#pragma once

#include <cstring>
#include <vector>

void replace(char* str, char removal, char added)
{
	while(*(str++) != '\0')
		if(*str == removal)
			*str = added;
}

std::vector<const char*> split(char* str, const char* delimiter)
{
	std::vector<const char*> parts;

	const char* tok = strtok(str, delimiter);
	parts.push_back(tok);
	while((tok = strtok(nullptr, delimiter)))
		parts.push_back(tok);
	return parts;
}

std::vector<const char*> split(char* str, const char c)
{
	const char delimiter[2] = {c, 0};
	return split(str, delimiter);
}

