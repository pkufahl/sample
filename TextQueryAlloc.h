//
// Created by Peter Kufahl on 8/20/15.
//

#ifndef SAMPLE_TEXTQUERYALLOC_H
#define SAMPLE_TEXTQUERYALLOC_H

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

#include "StringVector.h"

class QueryResultAlloc;

class TextQueryAlloc {
public:
	// no longer using vector<string>, but StringVector
    // using LineNum = vector<string>::size_type;

    TextQueryAlloc(std::ifstream&);

    QueryResultAlloc query(const string&) const;

private:
    // shared_ptr<vector<string>> _file;               // input file
	shared_ptr<StringVector> _file;

    // std::map<string, shared_ptr<std::set<LineNum>>> _wordMap;
	std::map<string, shared_ptr<std::set<size_t>>> _wordMap;
};

class QueryResultAlloc {
public:
    friend std::ostream& print(std::ostream&, const QueryResultAlloc&);
public:
    QueryResultAlloc(const string& s, shared_ptr<std::set<size_t>> spSet, shared_ptr<StringVector> v) :
		    _wordSought(s),
		    _linesItsOn(spSet),
		    _inputFile(v)
    { }
private:
    string _wordSought;                                         // word this query represents
    shared_ptr<std::set<size_t>> _linesItsOn;                   // the lines in the text that it's on
    shared_ptr<StringVector> _inputFile;                      // the input file
};

std::ostream& print(std::ostream&, const QueryResultAlloc&);


#endif //SAMPLE_TEXTQUERYALLOC_H
