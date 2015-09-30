//
// Created by Peter Kufahl on 8/25/15.
// rudimentary example data structure wrapper classes
// made to illustrate resource sharing via C++11 mechanisms
//
// StringBlob houses a shared pointer to vector<string>
// StringBlobPtr is a custom iterator for StringBlob
// ConstStringBlobPtr is a custom const iterator for StringBlob
//

#ifndef SAMPLE_STRINGBLOB_H
#define SAMPLE_STRINGBLOB_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <initializer_list>
using std::initializer_list;

#include <memory>
using std::make_shared;
using std::shared_ptr;

#include <exception>
#include <utility>

class StringBlobPtr;
class ConstStringBlobPtr;

class StringBlob {
	using size_type = vector<string>::size_type;
	friend class StringBlobPtr;
	friend class ConstStringBlobPtr;

	friend bool operator==(const StringBlob& lhs, const StringBlob& rhs);
    friend bool operator!=(const StringBlob& lhs, const StringBlob& rhs);
    friend bool operator< (const StringBlob& lhs, const StringBlob& rhs);
    friend bool operator> (const StringBlob& lhs, const StringBlob& rhs);
    friend bool operator<=(const StringBlob& lhs, const StringBlob& rhs);
    friend bool operator>=(const StringBlob& lhs, const StringBlob& rhs);

public:
	StringBlob()
			: _data(make_shared<vector<string>>())
	{ }

	StringBlob(initializer_list<string> il)
			: _data(make_shared<vector<string>>(il))
	{ }

	StringBlob(const StringBlob& sb)
			: _data(make_shared<vector<string>>(*sb._data))
	{ }

	StringBlob& operator=(const StringBlob& sb);

	StringBlob(StringBlob&& rhs) noexcept
		: _data(std::move(rhs._data))
	{ }

	StringBlob& operator=(StringBlob&& sb) noexcept;

	StringBlobPtr begin();
	StringBlobPtr end();

	ConstStringBlobPtr cbegin() const;
	ConstStringBlobPtr cend() const;

	string& operator[](size_t n);
	const string& operator[](size_t n) const;

	size_type size() const { return _data->size(); }
	bool empty() const { return _data->empty(); }

	void push_back(const string &str) { _data->push_back(str); }
	void push_back(string &&str) { _data->push_back(std::move(str)); }

	void pop_back();
	string& front();
	string& back();
	const string& front() const;
	const string& back() const;

private:
	void check(size_type t, const string& str) const;

	shared_ptr<vector<string>> _data;
};

bool operator==(const StringBlob& lhs, const StringBlob& rhs);
bool operator!=(const StringBlob& lhs, const StringBlob& rhs);
bool operator< (const StringBlob& lhs, const StringBlob& rhs);
bool operator> (const StringBlob& lhs, const StringBlob& rhs);
bool operator<=(const StringBlob& lhs, const StringBlob& rhs);
bool operator>=(const StringBlob& lhs, const StringBlob& rhs);

inline void StringBlob::pop_back() {

	check(0, "pop back on empty StringBlob");
	return _data->pop_back();
}

inline string& StringBlob::front() {

	check(0, "front on empty StringBlob");
	return _data->front();
}

inline string& StringBlob::back() {

	check(0, "back on empty StringBlob");
	return _data->back();
}

inline const string& StringBlob::front() const {

	check(0, "front on empty StringBlob");
	return _data->front();
}

inline const string& StringBlob::back() const {

	check(0, "back on empty StringBlob");
	return _data->back();
}

inline void StringBlob::check(size_type t, const string &str) const
{
	if (t >= _data->size()) throw std::out_of_range(str);
}

inline string& StringBlob::operator[](size_t n)
{
	check(n, "out of range");
	return _data->at(n);
}

inline const string& StringBlob::operator[](size_t n) const
{
	check(n, "out of range");
	return _data->at(n);
}


class StringBlobPtr {
	friend bool operator==(const StringBlobPtr& lhs, const StringBlobPtr& rhs);
	friend bool operator!=(const StringBlobPtr& lhs, const StringBlobPtr& rhs);
    friend bool operator< (const StringBlobPtr& lhs, const StringBlobPtr& rhs);
    friend bool operator> (const StringBlobPtr& lhs, const StringBlobPtr& rhs);
    friend bool operator<=(const StringBlobPtr& lhs, const StringBlobPtr& rhs);
    friend bool operator>=(const StringBlobPtr& lhs, const StringBlobPtr& rhs);

public:
	StringBlobPtr() : _current(0) { }

	StringBlobPtr(StringBlob &sb, size_t sz = 0)
			: _weak(sb._data),
              _current(sz)
	{ }

	string& dereference() const;

	StringBlobPtr& operator++();    // prefix inc.
	StringBlobPtr& operator--();    // prefix dec.

	StringBlobPtr operator++(int);  // postfix inc.
	StringBlobPtr operator--(int);  // postfix dec.

	StringBlobPtr& operator+=(size_t n);
	StringBlobPtr& operator-=(size_t n);

	StringBlobPtr operator+(size_t n) const;
	StringBlobPtr operator-(size_t n) const;

	string& operator[](size_t n);
	const string& operator[](size_t n) const;

	string& operator*();
	string* operator->();

private:
	shared_ptr<vector<string>> check(size_t sz, const string& str) const;

	// _weak is a weak_ptr, meaning that it has no control over the lifetime of its target
	// rather, it points to an object managed by a shared_ptr and does not alter its reference count
	// _weak and its member function lock() prevent a user of StringBlob from trying to access
	//  a vector<string> that no longer exists
    std::weak_ptr<vector<string>> _weak;

	size_t _current;
};

bool operator==(const StringBlobPtr& lhs, const StringBlobPtr& rhs);
bool operator!=(const StringBlobPtr& lhs, const StringBlobPtr& rhs);
bool operator< (const StringBlobPtr& lhs, const StringBlobPtr& rhs);
bool operator> (const StringBlobPtr& lhs, const StringBlobPtr& rhs);
bool operator<=(const StringBlobPtr& lhs, const StringBlobPtr& rhs);
bool operator>=(const StringBlobPtr& lhs, const StringBlobPtr& rhs);

inline string& StringBlobPtr::dereference() const
{
	auto ptr = check(_current, "dereference past end");

	return (*ptr)[_current];
}

inline StringBlobPtr& StringBlobPtr::operator++() {

	check(_current, "increment past end of StringBlobPtr");
	++_current;
	return *this;
}

inline StringBlobPtr& StringBlobPtr::operator--() {

	--_current;
	check(-1, "decrement past start of StringBlobPtr");
	return *this;
}

inline StringBlobPtr StringBlobPtr::operator++(int) {

	// postfix: increment the object but return the unchanged value

	StringBlobPtr ret = *this;

	// prefix operator does the check()
	++*this;
	return ret;
}

inline StringBlobPtr StringBlobPtr::operator--(int) {

	// postfix: decrement the object but return the unchanged value

	StringBlobPtr ret = *this;

	// prefix operator does the check()
	--*this;
	return ret;
}

inline StringBlobPtr& StringBlobPtr::operator+=(size_t n)
{
	_current += n;
	check(_current, "increment past end of StringBlobPtr");
	return *this;
}

inline StringBlobPtr& StringBlobPtr::operator-=(size_t n)
{
	_current -= n;
	check(_current, "increment past end of StringBlobPtr");
	// check(-1, "decrement past start of StringBlobPtr");
	return *this;
}

inline StringBlobPtr StringBlobPtr::operator+(size_t n) const
{
	StringBlobPtr ret = *this;
	ret += n;
	return ret;
}

inline StringBlobPtr StringBlobPtr::operator-(size_t n) const
{
	StringBlobPtr ret = *this;
	ret -= n;
	return ret;
}


inline shared_ptr<vector<string>> StringBlobPtr::check(size_t sz, const string& str) const
{
	auto ret = _weak.lock();

	if (!ret) throw std::runtime_error("unbound StringBlobPtr");

	if (sz >= ret->size()) throw std::out_of_range(str);

	return ret;
}

inline string& StringBlobPtr::operator[](size_t n)
{
	auto ptr = check(n, "dereference out of range");
	return (*ptr)[n];
}

inline const string& StringBlobPtr::operator[](size_t n) const
{
	auto ptr = check(n, "dereference out of range");
	return (*ptr)[n];
}

inline string& StringBlobPtr::operator*()
{
	auto p = check(_current, "dereference past end");
	return (*p)[_current];
}

inline string* StringBlobPtr::operator->()
{
	return &this->operator*();
}

class ConstStringBlobPtr {

    friend bool operator==(const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs);
    friend bool operator!=(const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs);
    friend bool operator< (const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs);
    friend bool operator> (const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs);
    friend bool operator<=(const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs);
    friend bool operator>=(const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs);

public:
    ConstStringBlobPtr() : _current(0) { }

    ConstStringBlobPtr(const StringBlob &sb, size_t sz = 0)
		    : _weak(sb._data),
		      _current(sz)
    { }

    const string& dereference() const;

    ConstStringBlobPtr& operator++();    // prefix inc.
    ConstStringBlobPtr& operator--();    // prefix dec.

    ConstStringBlobPtr operator++(int);  // postfix inc.
    ConstStringBlobPtr operator--(int);  // postfix dec.

    ConstStringBlobPtr& operator+=(size_t n);
    ConstStringBlobPtr& operator-=(size_t n);

    ConstStringBlobPtr operator+(size_t n) const;
    ConstStringBlobPtr operator-(size_t n) const;

    const string& operator[](size_t n) const;

	const string& operator*() const;
	const string* operator->() const;

private:
    shared_ptr<vector<string>> check(size_t sz, const string& str) const;

    // _weak is a weak_ptr, meaning that it has no control over the lifetime of its target
    // rather, it points to an object managed by a shared_ptr and does not alter its reference count
    // _weak and its member function lock() prevent a user of StringBlob from trying to access
    //  a vector<string> that no longer exists
    std::weak_ptr<vector<string>> _weak;

    size_t _current;
};

bool operator==(const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs);
bool operator!=(const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs);
bool operator< (const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs);
bool operator> (const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs);
bool operator<=(const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs);
bool operator>=(const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs);

inline const string& ConstStringBlobPtr::dereference() const
{
	auto ptr = check(_current, "dereference past end");

	return (*ptr)[_current];
}

inline ConstStringBlobPtr& ConstStringBlobPtr::operator++() {

	check(_current, "increment past end of ConstStringBlobPtr");
	++_current;
	return *this;
}

inline ConstStringBlobPtr& ConstStringBlobPtr::operator--() {

	--_current;
	check(-1, "decrement past start of ConstStringBlobPtr");
	return *this;
}

inline ConstStringBlobPtr ConstStringBlobPtr::operator++(int) {

	// postfix: increment the object but return the unchanged value

	ConstStringBlobPtr ret = *this;

	// prefix operator does the check()
	++*this;
	return ret;
}

inline ConstStringBlobPtr ConstStringBlobPtr::operator--(int) {

	// postfix: decrement the object but return the unchanged value

	ConstStringBlobPtr ret = *this;

	// prefix operator does the check()
	--*this;
	return ret;
}

inline ConstStringBlobPtr& ConstStringBlobPtr::operator+=(size_t n)
{
	_current += n;
	check(_current, "increment past end of ConstStringBlobPtr");
	return *this;
}

inline ConstStringBlobPtr& ConstStringBlobPtr::operator-=(size_t n)
{
	_current -= n;
	check(_current, "increment past end of ConstStringBlobPtr");
	// check(-1, "decrement past start of ConstStringBlobPtr");
	return *this;
}

inline ConstStringBlobPtr ConstStringBlobPtr::operator+(size_t n) const
{
	ConstStringBlobPtr ret = *this;
	ret += n;
	return ret;
}

inline ConstStringBlobPtr ConstStringBlobPtr::operator-(size_t n) const
{
	ConstStringBlobPtr ret = *this;
	ret -= n;
	return ret;
}


inline shared_ptr<vector<string>> ConstStringBlobPtr::check(size_t sz, const string& str) const
{
	auto ret = _weak.lock();

	if (!ret) throw std::runtime_error("unbound ConstStringBlobPtr");

	if (sz >= ret->size()) throw std::out_of_range(str);

	return ret;
}

inline const string& ConstStringBlobPtr::operator[](size_t n) const
{
	auto ptr = check(n, "dereference out of range");
	return (*ptr)[n];
}

inline const string& ConstStringBlobPtr::operator*() const
{
	auto p = check(_current, "dereference past end");
	return (*p)[_current];
}

inline const string* ConstStringBlobPtr::operator->() const
{
	return &this->operator*();
}

#endif //SAMPLE_STRINGBLOB_H
