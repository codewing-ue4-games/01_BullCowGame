#include "FileReader.h"



FileReader::FileReader() {
}


FileReader::~FileReader() {
}

std::vector<Word> FileReader::GetFileContent(FString FileName) {
	std::vector<Word> WordList;
	std::ifstream infile;
	infile.open(FileName);
	while (!infile.eof())
	{
		FString str;
		std::getline(infile, str); 
		FString HiddenWord = str.substr(0,str.find(","));
		FString Tries = str.substr(str.find(",")+1, str.length());
		WordList.push_back(Word(HiddenWord, Tries));
	}
	infile.close();
	return WordList;
}
