#include "Word.h"


Word::Word(FString HiddenWord, FString Tries) {
	this->HiddenWord = HiddenWord;
	this->Tries = std::stoi(Tries);
}


Word::~Word() {
}

FString Word::GetWord() {
	return HiddenWord;
}

int Word::GetTries() {
	return Tries;
}
