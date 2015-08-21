//
// Created by Peter Kufahl on 8/20/15.
//

#ifndef SAMPLE_TEXTQUERYSTL_H
#define SAMPLE_TEXTQUERYSTL_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <memory>       // shared_ptr
using std::shared_ptr;

#include <iostream>
#include <fstream>
#include <map>
#include <set>

class QueryResultSTL;

class TextQuerySTL {
public:
	using LineNum = vector<string>::size_type;

	TextQuerySTL(std::ifstream&);

	QueryResultSTL query(const string&) const;

private:
	shared_ptr<vector<string>> _file;               // input file

	std::map<string, shared_ptr<std::set<LineNum>>> _wordMap;
};

class QueryResultSTL {
public:
	friend std::ostream& print(std::ostream&, const QueryResultSTL&);
public:
	QueryResultSTL(const string& s, shared_ptr<std::set<TextQuerySTL::LineNum>> spSet, shared_ptr<vector<string>> v) :
			_wordSought(s),
            _linesItsOn(spSet),
            _inputFile(v)
	{ }
private:
	string _wordSought;                                         // word this query represents
	shared_ptr<std::set<TextQuerySTL::LineNum>> _linesItsOn;    // the lines in the text that it's on
	shared_ptr<vector<string>> _inputFile;                      // the input file
};

std::ostream& print(std::ostream&, const QueryResultSTL&);

#endif //SAMPLE_TEXTQUERYSTL_H
