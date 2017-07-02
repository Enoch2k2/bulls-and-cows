/*
	Header file for the FBullCowGame, this holds the
	definitions of the game logic to be used in our
	FBullCowGame class. See FBullCowGame.cpp for game
	logic.
*/
#pragma once

#include <string>

// unreal standard
using FString = std::string;
using int32 = int;

// we set up a simple struct to keep track of bulls and cows
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

// All of our guess status
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

// our predefined list of public and private methods / variables
class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetWord(int32) const;
	FString GetRandomWord(FString LetterArray[]) const;
	// TODO Create Function to get random word based on length chosen;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(int32);
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};