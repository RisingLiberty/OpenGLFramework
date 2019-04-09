#include "FileReader.h"

#include <fstream>
#include <iostream>
#include <vector>

std::string FileReader::ReadFile(const std::string& path)
{
	// Start reading at the end of the file
	std::ifstream file(path, std::ios::in | std::ios::ate);

	// If file can't be found, return NULL
	if (!file.is_open())
	{
		std::cout << "Warning: unable to open file at location: \n" << path << "\n";
		return {};
	}

	// Because our read position is at the end,
	// we can detemine the size of the file and allocate a buffer
	size_t size = (size_t)file.tellg();
	std::vector<char> buffer(size);

	// set the read position to the first char.
	file.seekg(0);
	file.read(buffer.data(), size);

	file.close();

	return buffer.data();
}