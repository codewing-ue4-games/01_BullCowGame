#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();
void PrintGameSummary();


FBullCowGame BCGame;


int main() {

	do {
		BCGame.Reset();
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	return 0;
}

bool AskToPlayAgain() {
	std::cout << std::endl << "Do you want to play again (Y/n)?" << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);
	if (Response.empty() || Response[0] == 'Y') {
		return true;
	}
	else {
		return false;
	}
}

FText GetGuess() {
	std::cout << std::endl << "Try " << BCGame.GetCurrentTry() << "/" << BCGame.GetMaxTries() << ": Enter your guess: ";
	FText Guess = "";
	std::getline(std::cin, Guess);
	return Guess;
}

FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus GuessStatus = EGuessStatus::INVALID;
	do {
		Guess = GetGuess();
		std::cout << "You guessed: " << Guess << std::endl;

		GuessStatus = BCGame.CheckGuessValidity(Guess);
		switch (GuessStatus) {
		case EGuessStatus::WRONG_LENGTH:
		{
			std::cout << "Length of your guess does not match the length of the hidden word (" << BCGame.GetHiddenWordLength() << ")." << std::endl;
		}break;

		case EGuessStatus::NOT_ISOGRAM:
		{
			std::cout << "The word is not an isogram (" << Guess << ")." << std::endl;
		}break;

		case EGuessStatus::NOT_LOWERCASE_WORD:
		{
			std::cout << "The word must only contain lowercase letters (" << Guess << ")." << std::endl;
		}break;

		default:
		{
			if (GuessStatus != EGuessStatus::OK) {
				std::cout << "Unknown GuessStatus" << std::endl;
			}
		}

		}

	} while (GuessStatus != EGuessStatus::OK);

	return Guess;
}

void PlayGame() {
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FString ValidGuess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(ValidGuess);
		BCGame.CheckSubmitGuessResult(BullCowCount);
	}

	PrintGameSummary();
}

void PrintIntro() {
	const int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << "    ,           ," << std::endl;
	std::cout << "   /             \\" << std::endl;
	std::cout << "  ((__-^^-,-^^-__))" << std::endl;
	std::cout << "   `-_---' `---_-'" << std::endl;
	std::cout << "    <__|o` 'o|__>" << std::endl;
	std::cout << "       \\  `  /" << std::endl;
	std::cout << "        ): :(" << std::endl;
	std::cout << "        :o_o:" << std::endl;
	std::cout << "         \"-\"" << std::endl;
	std::cout << "Welcome to Bulls and Cows!" << std::endl;
	FString WordOrIsogramm = "word";
	if (BCGame.GetIsHiddenWordIsogram()) {
		WordOrIsogramm = "isogram";
	}
	std::cout << "Can you guess the " << WORD_LENGTH << " letter " << WordOrIsogramm << " I'm thinking of?" << std::endl;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "You won! #Tries: " << BCGame.GetCurrentTry() - 1 << ". Well done!" << std::endl;
	} else {
		std::cout << "You lost! Looks like " << BCGame.GetMaxTries() << " were not enough for you to guess the hidden word." << std::endl;
	}
}
