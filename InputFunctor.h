//
// Created by Peter Kufahl on 8/26/15.
//

#ifndef SAMPLE_INPUTFUNCTOR_H
#define SAMPLE_INPUTFUNCTOR_H

#include <iostream>
#include <string>
#include <vector>


void test_InputFunctor1();
void test_InputFunctor1_vec();
void test_IsEqualTo();
void test_IsInRange(const std::string& str);
void test_Biggies(const std::string& str);

std::string make_plural(std::size_t sz, const std::string& word, const std::string& ending);

void elim_dups(std::vector<std::string>& words);

void biggies_functors(std::vector<std::string>& words, std::vector<std::string>::size_type sz);
void biggies_lambdas(std::vector<std::string>& words, std::vector<std::string>::size_type sz);


class InputFunctor1 {

public:
	InputFunctor1(std::istream &is = std::cin) : _is(is) { }

	std::string operator()() const
	{
		std::string str;
		std::getline(_is, str);
		return _is ? str : std::string();
	}

private:
	std::istream& _is;
};

class IsEqualTo {
public:
	IsEqualTo(int v) : _value(v) { }

	bool operator()(int elem)
	{
		return elem == _value;
	}

private:
	int _value;
};

class IsInRange
{
public:
	IsInRange(std::size_t lower, std::size_t upper) : _lower(lower), _upper(upper) { }

	bool operator()(const std::string& str) const
	{
		return str.size() >= _lower && str.size() <= _upper;
	}

	std::size_t lower_limit() const { return _lower; }
	std::size_t upper_limit() const { return _upper; }
private:
	std::size_t _lower;
	std::size_t _upper;
};

class BiggerEqual
{
public:
	BiggerEqual(std::size_t sz) : _sz(sz) { }

	bool operator()(const std::string& str) { return str.size() >= _sz; }
private:
	std::size_t _sz;
};

class ShorterString
{
public:
	bool operator()(const std::string& s1, const std::string& s2) const
	{
		return s1.size() < s2.size();
	}
};

class Print
{
public:
	void operator()(const std::string& str) { std::cout << str << " "; }
};


#endif //SAMPLE_INPUTFUNCTOR_H
