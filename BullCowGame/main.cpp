/* This file is used for the view part of the MVC structure
	See FBullCowGame.cpp for game logic.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Unreal standard
using FText = std::string;
using int32 = int;

void PrintIntro();
void PrintGameSummery();
void PlayGame();
FText GetValidGuess();
int32 GetNewWordLength();
bool AskToPlayAgain();

FBullCowGame BCGame; // C++ Instantiation'

//intro point for the app
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	}
	while(AskToPlayAgain());
	// will ask the user to play again and keep it in a loop if 'y'
	return 0;
}


void PrintIntro()
{
	// prints an introduction (terrible ASCII)
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "|-----, " << " ,----," << std::endl;
	std::cout << "| |__| |" << "| |---'" << std::endl;
	std::cout << "|  __  |" << "| |    " << std::endl;
	std::cout << "| |__| |" << "| |---," << std::endl;
	std::cout << "|_____/ " << " \\___/" << std::endl;
	return;
}

// Gives details of how the game ended (win / lose)
void PrintGameSummery()
{
	if (BCGame.IsGameWon()) {
		std::cout << "Congratulations, you won!\n";
	} else {
		std::cout << "Sorry, better luck yet next time!\n";
	}
	return;
}

// players a single game to completion
void PlayGame()
{
	// ask player of how long of letters, 3-7
	int32 GetWordLength = GetNewWordLength();
	// resets game back to beginning state
	BCGame.Reset(GetWordLength);
	std::cout << "Can you guess a " << BCGame.GetHiddenWordLength() << " letter word I am thinking of?" << std::endl << std::endl;
	// while the game is NOT won and there are still remaining tries
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}
	// at this point the game is over and we'll tell the user how it ended.
	PrintGameSummery();
	return;
}

// get a random number between two integers
int32 GetRandomNumber(int32 min, int32 max)
{
	int32 n = max - min + 1;
	int32 remainder = RAND_MAX % n;
	int32 x;
	do {
		x = rand();
	} while (x >= RAND_MAX - remainder);
	return min + x % n;
}

// allow player to choose length of word
int32 GetNewWordLength()
{
	std::cout << "Would you like to choose a word length?(y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);
	if (Response == "y" || Response == "Y") {
		std::cout << "\n How long of word? Enter 3-7 :";
		Response = "";
		std::getline(std::cin, Response);
		if (Response == "3") {
			return 3;
		}
		else if (Response == "4") {
			return 4;
		}
		else if (Response == "5") {
			return 5;
		}
		else if (Response == "6") {
			return 6;
		}
		else if (Response == "7") {
			return 7;
		}
		else {
			std::cout << "Invalid input\n";
			GetNewWordLength();
		}
	}
	else {
		return GetRandomNumber(3, 7);
	}
}


FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		// get guess
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter Guess: ";
		std::getline(std::cin, Guess);

		// check guess validity
		Status = BCGame.CheckGuessValidity(Guess);
		
		// check for guess errors
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use lowercase characters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);
	// if the Guess is not valid then restart try
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}

