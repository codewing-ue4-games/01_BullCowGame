#include "FBullCowGame.h"

#define TSet std::unordered_set


FBullCowGame::FBullCowGame() {
	HiddenWordList = FileReader::GetFileContent("HiddenWords.txt");
	
	srand(time(NULL));
}


FBullCowGame::~FBullCowGame() {
}

void FBullCowGame::Reset() {
	Word SelectedWord = HiddenWordList.at(rand() % HiddenWordList.size());
	HiddenWord = SelectedWord.GetWord();
	MaxTries = SelectedWord.GetTries();
	IsHiddenWordIsogram = IsIsogram(HiddenWord);
	CurrentTry = 1;
	GameIsWon = false;
}

int32 FBullCowGame::GetMaxTries() const {
	return MaxTries;
}

int32 FBullCowGame::GetCurrentTry() const {
	return CurrentTry;
}

void FBullCowGame::IncrementCurrentTry() {
	CurrentTry++;
}

void FBullCowGame::CheckSubmitGuessResult(FBullCowCount BullCowCount) {
	std::cout << "Bulls: " << BullCowCount.Bulls << std::endl;
	std::cout << "Cows: " << BullCowCount.Cows << std::endl;
	if (BullCowCount.Bulls == GetHiddenWordLength()) {
		GameIsWon = true;
	}
}

bool FBullCowGame::IsGameWon() const {
	return GameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) {
	if (Guess.length() != HiddenWord.length()) {
		return EGuessStatus::WRONG_LENGTH;
	}

	if (!IsLowercaseText(Guess)) {
		return EGuessStatus::NOT_LOWERCASE_WORD;
	}

	if (IsHiddenWordIsogram && !IsIsogram(Guess)) {
		return EGuessStatus::NOT_ISOGRAM;
	}
	
	return EGuessStatus::OK;
}

bool FBullCowGame::IsIsogram(FString Guess) {

	TSet<char> SeenLetters;
	for (auto Letter : Guess ) {
		Letter = tolower(Letter);
		if(SeenLetters.find(Letter) == SeenLetters.end()) {
			SeenLetters.insert(Letter);
		} else {
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercaseText(const FString Str) const {
	return Str.find_first_not_of("abcdefghijklmnopqrstuvwxyz") == FString::npos;
}

//Recieve valid guess + increments count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	IncrementCurrentTry();

	FBullCowCount count;
	for (int32 h = 0; h < GetHiddenWordLength(); h++) {
		for (int32 g = 0; g < (int32) Guess.length(); g++) {
			if (Guess[g] == HiddenWord[h]) {
				if (h == g) {
					count.Bulls++;
				}
				else {
					count.Cows++;
				}
			}
		}
	}

	return count;
}

int32 FBullCowGame::GetHiddenWordLength() const {
	return HiddenWord.length();
}

bool FBullCowGame::GetIsHiddenWordIsogram() const {
	return IsHiddenWordIsogram;
}
