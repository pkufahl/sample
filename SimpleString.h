//
// Created by Peter Kufahl on 8/21/15.
//

#ifndef SAMPLE_SIMPLESTRING_H
#define SAMPLE_SIMPLESTRING_H

#include <memory>
#include <iostream>

class SimpleString {
public:
	friend std::ostream& operator<<(std::ostream& output, const SimpleString& str);
	friend std::istream& operator>>(std::istream& input, SimpleString& str);
	friend bool operator==(const SimpleString& lhs, const SimpleString& rhs);
	friend bool operator!=(const SimpleString& lhs, const SimpleString& rhs);
	friend bool operator< (const SimpleString& lhs, const SimpleString& rhs);
	friend bool operator> (const SimpleString& lhs, const SimpleString& rhs);
	friend bool operator<=(const SimpleString& lhs, const SimpleString& rhs);
	friend bool operator>=(const SimpleString& lhs, const SimpleString& rhs);

public:
	SimpleString() : SimpleString("") { }

    SimpleString(const char *);

    SimpleString(const SimpleString&);
	SimpleString& operator=(const SimpleString&);

	SimpleString(SimpleString&&) noexcept;
	SimpleString& operator=(SimpleString&&) noexcept;

	~SimpleString() { free(); }

	char& operator[] (size_t n) { return _first_element[n]; }
	const char& operator[] (size_t n) const { return _first_element[n]; }

	void push_back(const char);                         // added for the >> operator

	void reserve(size_t size);
	void resize(size_t count);
	void resize(size_t count, char tidbit);

	char* begin() const { return _first_element; }
	char* end() const { return _last_element; }

	const char *c_string() const { return _first_element; }

	size_t size() const { return _last_element - _first_element; }
	size_t length() const { return size(); }
	size_t capacity() const { return _capacity - _first_element; }

private:
	std::pair< char*, char* > allocate_and_copy(const char*, const char*);

	void range_initializer(const char*, const char*);

	void free();
	void reallocate();
	void allocate_and_move(size_t newCap);
	void check_and_allocate() { if (_first_free == _capacity) reallocate(); }

private:
	char *_first_element;
	char *_first_free;
	char *_capacity;
    char *_last_element;
	std::allocator<char> _alloc;
};

std::ostream& operator<<(std::ostream& output, const SimpleString& str);
std::istream& operator>>(std::istream& input, SimpleString& str);
bool operator==(const SimpleString& lhs, const SimpleString& rhs);
bool operator!=(const SimpleString& lhs, const SimpleString& rhs);
bool operator!=(const SimpleString& lhs, const SimpleString& rhs);
bool operator< (const SimpleString& lhs, const SimpleString& rhs);
bool operator> (const SimpleString& lhs, const SimpleString& rhs);
bool operator<=(const SimpleString& lhs, const SimpleString& rhs);
bool operator>=(const SimpleString& lhs, const SimpleString& rhs);

#endif //SAMPLE_SIMPLESTRING_H
