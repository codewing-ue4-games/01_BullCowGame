#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "Word.h"

using FString = std::string;

class FileReader {
public:
	FileReader();
	~FileReader();

	static std::vector<Word> GetFileContent(FString);
};

