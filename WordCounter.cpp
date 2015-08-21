//
// Created by Peter Kufahl on 8/18/15.
//

#include "WordCounter.h"
//using namespace std;

// executes word counting program
void WordCounter::do_wordCount() {

	std::map <std::string, size_t> tmpWordCount;
	std::string word;

	std::ifstream inFile(_dataSource);

	if (inFile)
	{
		while (inFile >> word)
			++tmpWordCount[word];

		for (const auto &wc : tmpWordCount)
			std::cout << wc.first << " occurs " << wc.second << ((wc.second > 1) ? " times" : " time") << std::endl;
	}
	else
	{
		// no source of data
		std::cout << "WordCounter: no source of text data" << std::endl;
	}
}

void WordCounter::do_unorderedWordCount() {

	std::unordered_map <std::string, size_t> tmpWordCount;
	std::string word;

	std::ifstream inFile(_dataSource);

	if (inFile)
	{
		while (inFile >> word)
			++tmpWordCount[word];

		for (const auto &wc : tmpWordCount)
			std::cout << wc.first << " occurs " << wc.second << ((wc.second > 1) ? " times" : " time") << std::endl;
	}
	else
	{
		// no source of data
		std::cout << "WordCounter: no source of text data" << std::endl;
	}

}

// ignores case and punctuation
void WordCounter::do_betterWordCount() {

	std::map <std::string, size_t> tmpWordCount;
	std::string word;

	std::ifstream inFile(_dataSource);

	_numWords = 0;

	if (inFile)
	{
		// build the data structure here
		while (inFile >> word) {

			// ignore case in word-counting: use tolower
			for (auto& tidbit : word)
				tidbit = tolower(tidbit);

			// ignore punctuation in word-counting: use ispunct() and the erase-remove idiom
			// note: I had to use "::" in front of ispunct since this function has an overload
			//  and without the :: the compiler cannot decide which one to use
			word.erase(remove_if(word.begin(), word.end(), ispunct), word.end());

			// add it to the map, creating an entry if there is none (incrementing the value from 0 to 1)
			++tmpWordCount[word];
			++_numWords;
		}

		// output here
		for (const auto &wc : tmpWordCount)
			std::cout << wc.first << " occurs " << wc.second << ((wc.second > 1) ? " times" : " time") << std::endl;
	}
	else
	{
		// no source of data
		std::cout << "WordCounter: no source of text data" << std::endl;
	}

}

void WordCounter::do_unorderedBetterWordCount() {

	std::unordered_map <std::string, size_t> tmpWordCount;
	std::string word;

	std::ifstream inFile(_dataSource);

	_numWords = 0;

	if (inFile)
	{
		// build the data structure here
		while (inFile >> word) {

			// ignore case in word-counting: use tolower
			for (auto& tidbit : word)
				tidbit = tolower(tidbit);

			word.erase(remove_if(word.begin(), word.end(), ispunct), word.end());

			// add it to the map, creating an entry if there is none (incrementing the value from 0 to 1)
			++tmpWordCount[word];
			++_numWords;
		}

		// output here
		for (const auto &wc : tmpWordCount)
			std::cout << wc.first << " occurs " << wc.second << ((wc.second > 1) ? " times" : " time") << std::endl;
	}
	else
	{
		// no source of data
		std::cout << "WordCounter: no source of text data" << std::endl;
	}
}