#pragma once
#include <string>

using FString = std::string;

class Word {

private:
	FString HiddenWord;
	int Tries;

public:
	Word::Word(FString HiddenWord, FString Tries);
	~Word();

	FString GetWord();
	int GetTries();
};

