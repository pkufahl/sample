//
// Created by Peter Kufahl on 8/26/15.
//

#include "InputFunctor.h"
#include <algorithm>
#include <map>
#include <fstream>
#include <cctype>

void test_InputFunctor1()
{
	InputFunctor1 getInput;

	std::cout << "Constructor called ..." << std::endl;

	std::cout << getInput() << std::endl;

	std::cout << "... done" << std::endl;
}

void test_InputFunctor1_vec()
{
	InputFunctor1 getInput;
	std::vector<std::string> vec;

	for (std::string tmp; !(tmp = getInput()).empty(); )
		vec.push_back(tmp);

	for (const auto &str : vec)
		std::cout << str << " ";

	std::cout << std::endl;
}

void test_IsEqualTo()
{
	std::vector<int> vec = {3, 2, 3, 5, 6, 3, 4, 0, 0, 3, 4, 2};

	std::cout << "Before: ";
	for (auto i : vec)
		std::cout << i << " ";

	std::cout << std::endl;

	std::replace_if(vec.begin(), vec.end(), IsEqualTo(3), 9);

	std::cout << "After: ";
	for (auto i : vec)
		std::cout << i << " ";

	std::cout << std::endl;

}

void test_IsInRange(const std::string& str)
{
	// create a vector of predicates with various upper limits
	std::size_t lo = 1;
	auto uppers = { 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u, 12u, 13u, 14u };
	std::vector<IsInRange> predicates;

	for (auto u : uppers)
		predicates.push_back(IsInRange{ lo, u });           // direct brace init. to avoid most-vexing-parse

	// create a table to store counts
	std::map<std::size_t, std::size_t> countTable;

	for (auto u : uppers)
		countTable[u] = 0;

	// read the file and count
	std::ifstream input(str);
	for (std::string word; input >> word; )
		for (auto isitinrange : predicates)
			if (isitinrange(word))
				++countTable[isitinrange.upper_limit()];

	// print results
	for (auto pair : countTable)
		std::cout << "count in range [1, " << pair.first << "] : " << pair.second << std::endl;

}

void test_Biggies(const std::string& str)
{
	// read file of text into vector of words
	std::ifstream input(str);
	std::string word;
	std::vector<std::string> bigVectorOfWords1, bigVectorOfWords2;

	while(input >> word)
	{
		// put into lower case
		for (auto& tidbit : word)
			tidbit = std::tolower(tidbit);

		bigVectorOfWords1.push_back(word);
		bigVectorOfWords2.push_back(word);
	}


	std::cout << "USING FUNCTORS" << std::endl;
	biggies_functors(bigVectorOfWords1, 10);

	std::cout << "USING LAMBDAS" << std::endl;
	biggies_lambdas(bigVectorOfWords2, 10);

	std::cout << "done" << std::endl;


}

std::string make_plural(std::size_t sz, const std::string& word, const std::string& ending)
{
	return (sz > 1) ? word + ending : word;
}

void elim_dups(std::vector<std::string>& words)
{
	// sort words alphabetically so we can find the duplicates
	std::sort(words.begin(), words.end());

	// unique() reorders the input range so that each word appears once in the front
	//  portion of the range and returns an iterator one past the unique range
	auto end_of_unique = std::unique(words.begin(), words.end());

	// erase() is a vector operation that removes the nonunique elements
	words.erase(end_of_unique, words.end());
}

void biggies_functors(std::vector<std::string>& words, std::vector<std::string>::size_type sz)
{
	elim_dups(words);

	// sort words by size, but maintain the alphabetical order of words of the same size
	// the functor ShortString overloads the ()-operator to return boolean result of comparing
	//  string lengths
	std::stable_sort(words.begin(), words.end(), ShorterString());

	// find_if returns an iterator to the first element whose size is >= sz
	// the functor BiggerEqual overloads the ()-operator to return the boolean result of this
	//  comparison
	auto iter = std::find_if(words.begin(), words.end(), BiggerEqual(sz));
	auto count = words.end() - iter;

	// print words of a given size or larger
	// the functor Print prints out each word followed by a space
	std::cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer" << std::endl;
	std::for_each(iter, words.end(), Print());
	std::cout << std::endl;
}

void biggies_lambdas(std::vector<std::string>& words, std::vector<std::string>::size_type sz)
{
	elim_dups(words);

	// sort words by size, but maintain the alphabetical order of words of the same size
	std::stable_sort(words.begin(), words.end(),
		[](const std::string& a, const std::string &b)
		{ return a.size() < b.size(); });

	// find_if returns an iterator to the first element whose size is >= sz
	auto iter = std::find_if(words.begin(), words.end(),
		[sz](const std::string& a)
		{ return a.size() >= sz; });
	auto count = words.end() - iter;

	// print words of a given size or larger
	std::cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer" << std::endl;
	std::for_each(iter, words.end(), [](const std::string& s){ std::cout << s << " "; });
	std::cout << std::endl;
}
