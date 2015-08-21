//
// Created by Peter Kufahl on 8/18/15.
//

#ifndef SAMPLE_WORDCOUNTER_H
#define SAMPLE_WORDCOUNTER_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>

#include <cctype>       // tolower, ispunct
#include <algorithm>    // remove_if

class WordCounter {
public:
	WordCounter() : _dataSource("data.txt"), _numWords(0) {}

	WordCounter(const std::string& s) : _dataSource(s), _numWords(0) {}

	~WordCounter() {}

	void do_wordCount();

	void do_unorderedWordCount();

	void do_betterWordCount();

	void do_unorderedBetterWordCount();

	long get_words() { return _numWords; }

private:
	std::string _dataSource;
	long _numWords;
};


#endif //SAMPLE_WORDCOUNTER_H
