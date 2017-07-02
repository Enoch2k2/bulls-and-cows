/*
	This file contains the logic of the game itself, it
	is the game controller. See the header file for a
	list of game definitions, or the main.cpp file for
	the view logic.
*/
#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

// unreal standard
using FString = std::string;
using int32 = int;

// instantiates the game with a fresh state
FBullCowGame::FBullCowGame(){ Reset(3); }

// getters
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

// get random word to be the hidden word randomly
FString FBullCowGame::GetWord(int32 WordLength) const
{
	// create arrays of words based on length
	FString FiveLetterWords[3] = { "plane", "smile", "giant" };
	FString ThreeLetterWords[3] = { "and", "get", "sea" };
	FString FourLetterWords[3] = { "love", "grow", "tire" };
	FString SexLetterWords[3] = { "beauty", "flower", "string" };
	FString SevenLetterWords[3] = { "alchemy", "machine", "sardine" };
	if (WordLength == 3) {
		return GetRandomWord(ThreeLetterWords);
	}
	else if (WordLength == 4) {
		return GetRandomWord(FourLetterWords);
	}
	else if (WordLength == 5) {
		return GetRandomWord(FiveLetterWords);
	}
	else if (WordLength == 6) {
		return GetRandomWord(SexLetterWords);
	}
	else {
		return GetRandomWord(SevenLetterWords);
	}
}

// used to get a random word out of an array with a length of 3 elements
FString FBullCowGame::GetRandomWord(FString LetterArray[]) const
{
	int32 n = 2 - 0 + 1;
	int32 remainder = RAND_MAX % n;
	int32 x;
	do {
		x = rand();
	} while (x >= RAND_MAX - remainder);
	return LetterArray[0 + x % n];	
}

int32 FBullCowGame::GetMaxTries() const 
{
	// creates a difficulty - first difficulty in the TMap is 3 length word, 4 tries. ect...
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5, 10}, {6,15}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

// resets the game to beginning state
void FBullCowGame::Reset(int32 WordLength)
{
	const FString HIDDEN_WORD = GetWord(WordLength);
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}

// validates the guess
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();
	for (int32 i = 0; i < WordLength; i++) {
		for (int32 j = 0; j < WordLength; j++)	{
			if (MyHiddenWord[i] == Guess[j]) {
				if (i == j) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	// if they get the word right, set the bGameWon flag to true
	// indicating that they have won
	if (BullCowCount.Bulls == WordLength) {
		bGameWon = true;
	}
	else {
		bGameWon = false;
	}
	return BullCowCount;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))// if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())// if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1){ return true; }

	TMap<char, bool> LetterSeen;
	// check each letter if the letter has been seen.
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		// if the letter has been seen, then it's not an Isogram
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			// indicates the letter has been seen for the first time.
			LetterSeen[Letter] = true;
		}
	}	
	return true;
}

// this method checks the string if all the characters are lowercased.
bool FBullCowGame::IsLowerCase(FString Word) const
{
	if (Word.length() <= 1) { return true; }
	// checks each letter if the letter is lowercased.
	for (auto Letter : Word)
	{
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}