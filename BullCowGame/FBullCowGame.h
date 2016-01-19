#pragma once
#include "FileReader.h"
#include <iostream>
#include <stdio.h> 
#include <cstdlib> 
#include <time.h>
#include <string>
#include <vector>
#include <unordered_set>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	INVALID,
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE_WORD
};

class FBullCowGame
{
private:
	std::vector<Word> HiddenWordList;
	int32 CurrentTry;
	int32 MaxTries;
	bool IsHiddenWordIsogram;
	bool GameIsWon;
	FString HiddenWord;

	bool IsLowercaseText(FString) const;
	bool IsIsogram(FString Guess);

public:
	FBullCowGame();
	~FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool GetIsHiddenWordIsogram() const;
	
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString);
	
	void Reset();
	void IncrementCurrentTry();
	void CheckSubmitGuessResult(FBullCowCount);
	FBullCowCount SubmitValidGuess(FString);
};

