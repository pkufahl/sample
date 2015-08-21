//
// Created by Peter Kufahl on 8/20/15.
//

#include <sstream>

#include "TextQuerySTL.h"

TextQuerySTL::TextQuerySTL(std::ifstream &ifs) : _file(new vector<string>)
{
	string text;
	while(getline(ifs, text))                   // for each line in the file
	{
		_file->push_back(text);                         // store this line of text

		unsigned long n = _file->size() - 1;            // current line number

		std::istringstream line(text);                  // separate the line into words
		string word;

		while(line >> word)
		{
			// if word is not already in _wordMap, subscripting adds a new entry
			// spLines is a shared_ptr
			auto& spLines = _wordMap[word];

			if (!spLines)       // spLines is null the first time we see that word
				spLines.reset(new std::set<LineNum>);    // allocate a new set

			spLines->insert(n);                 // insert the line number
		}
	}
}

QueryResultSTL TextQuerySTL::query(const string &wordSought) const {

	// return a ptr to this "no data" set if we do not find wordSought
	static shared_ptr<std::set<LineNum>> st_noData(new std::set<LineNum>);

	// use find(), not a subscript, to avoid adding words to _wordMap
	auto loc = _wordMap.find(wordSought);

	// return the query result containing the "no data" set or the set of
	//  line numbers corresponding to wordSought
	if (loc == _wordMap.end())
		return QueryResultSTL(wordSought, st_noData, _file);
	else
		return QueryResultSTL(wordSought, loc->second, _file);
}

std::ostream &print(std::ostream &os, const QueryResultSTL &qr) {

	string timez = (qr._linesItsOn->size() > 1) ? "times" : "time";

	os << qr._wordSought << " occurs " << qr._linesItsOn->size() << " " << timez << std::endl;

	for (auto num : *qr._linesItsOn)
		os << "\t(line " << num + 1 << ") " << *(qr._inputFile->begin() + num) << std::endl;

	return os;
}
