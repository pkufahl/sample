//
// Created by Peter Kufahl on 8/21/15.
//

#include "SimpleString.h"
#include <algorithm>

std::pair<char *, char *> SimpleString::allocate_and_copy(const char *first, const char *last) {

	auto str = _alloc.allocate(last - first);

	return { str, std::uninitialized_copy(first, last, str) };
}


void SimpleString::range_initializer(const char *first, const char *last) {

	auto newStr = allocate_and_copy(first, last);
	_first_element = newStr.first;
	_first_free = _capacity = newStr.second;
	_last_element = _first_free - 1;
}

SimpleString::SimpleString(const char *str) {

	// main ctor

	char *c = const_cast<char*>(str);

	while (*c)
		++c;

	range_initializer(str, ++c);
}


SimpleString::SimpleString(const SimpleString &rhs) {

	// copy ctor

	// range_initializer(rhs._elements, rhs._end);
	range_initializer(rhs._first_element, rhs._first_free);

	std::cout << "copy constructor" << std::endl;

}


void SimpleString::free() {

	// std::cout << "free() called ... ";
	if (_first_element)
	{
		// std::cout << *_first_element << " ... ";
		std::for_each(_first_element, _first_free, [this](char &c){ _alloc.destroy(&c); });

		_alloc.deallocate(_first_element, _capacity - _first_element);
	}

	// std::cout << "successful" << std::endl;
}

SimpleString &SimpleString::operator=(const SimpleString &rhs) {

	// copy assignment

	auto newstr = allocate_and_copy(rhs._first_element, rhs._first_free);
	free();
	_first_element = newstr.first;
	_first_free = _capacity = newstr.second;
	_last_element = _first_free - 1;

	std::cout << "copy assignment" << std::endl;

	return *this;
}

SimpleString::SimpleString(SimpleString &&str) noexcept
	: _first_element(str._first_element),
	  _last_element(str._last_element),
      _first_free(str._first_free),
      _capacity(str._capacity)
{
	// move ctor

	str._first_element = str._last_element = str._first_free = str._capacity = nullptr;

	std::cout << "move constructor" << std::endl;
}

SimpleString &SimpleString::operator=(SimpleString &&rhs) noexcept
{
	// move assignment

	if (this != &rhs)
	{
		free();
		_first_element = rhs._first_element;
		_last_element = rhs._last_element;
		_first_free = rhs._first_free;
		_capacity = rhs._capacity;
		rhs._first_element = rhs._last_element = rhs._first_free = rhs._capacity = nullptr;
	}

	std::cout << "move assignment" << std::endl;

	return *this;
}

std::ostream& operator<<(std::ostream& output, const SimpleString& str)
{
	output << str.c_string();

	return output;
}

void SimpleString::push_back(const char tidbit) {

	check_and_allocate();
	*_last_element = tidbit;
	_last_element = _first_free;

	_alloc.construct(_first_free++, '\0');
}

void SimpleString::allocate_and_move(size_t newCap) {

	auto newData = _alloc.allocate(newCap);
	auto dest = newData;
	auto elem = _first_element;

	for (size_t i=0; i != size()+1; ++i)
		_alloc.construct(dest++, std::move(*elem++));

	free();

	_first_element = newData;
	_last_element = dest - 1;
	_first_free = dest;
	_capacity = _first_element + newCap;
}

void SimpleString::reallocate() {

	auto newCapacity = size() ? 2 * (size()+1) : 2;

	allocate_and_move(newCapacity);
}

std::istream &operator>>(std::istream &input, SimpleString &str) {

	for (char tidbit; (tidbit = input.get()) != '\n'; )
		str.push_back(tidbit);

	return input;
}

bool operator==(const SimpleString& lhs, const SimpleString& rhs)
{
	return ((lhs.size() == rhs.size()) &&
		std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

bool operator!=(const SimpleString& lhs, const SimpleString& rhs)
{
	return !(lhs == rhs);
}

void SimpleString::resize(size_t count) {

	// little resize()

	resize(count, ' ');
}

void SimpleString::resize(size_t count, char tidbit) {

	// big resize()

	if (count > size())         // grow to fit
	{
		if (count > capacity()) reserve(count * 2);

		for (size_t i = size(); i != count; ++i)
		{
			*_last_element++ = tidbit;
			_alloc.construct(_first_free++, '\0');
		}
	}
	else if (count < size())    // shrink to fit, procrustean style
	{
		while (_last_element != _first_element + count)
		{
			--_last_element;
			_alloc.destroy(--_first_free);
		}
		*_last_element = '\0';
	}
}

void SimpleString::reserve(size_t sz) {

	// used by the resize() method
	// wrapper function for allocate_and_move

	if (sz <= capacity()) return;

	allocate_and_move(sz);

}

bool operator<(const SimpleString &lhs, const SimpleString &rhs) {

	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

bool operator>(const SimpleString &lhs, const SimpleString &rhs) {

	return rhs < lhs;
}

bool operator<=(const SimpleString &lhs, const SimpleString &rhs) {

	return !(rhs < lhs);
}

bool operator>=(const SimpleString &lhs, const SimpleString &rhs) {

	return !(lhs < rhs);
}
