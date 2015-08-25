//
// Created by Peter Kufahl on 8/20/15.
//

#include <utility>
#include <algorithm>
#include "StringVector.h"


// std::allocator <std::string> _st_alloc;      // allocates the elements
std::allocator <std::string> StringVector::_alloc;

void StringVector::push_back(const std::string &s) {

	check_and_allocate();   // make sure there is room for another element

	// construct a copy of s in the element to which _first_free pts
	_alloc.construct(_first_free++, s);
}

std::pair<std::string *, std::string *> StringVector::allocate_and_copy(const std::string *b,
                                                                        const std::string *e) {

	// like a vector<string>, StringVector has value-like behavior
	//
	// allocate_and_copy is called when a StringVector is copied or assigned.
	// first, we allocate enough storage to hold its given range of elements
	//  (b pts to the beginning, e pts to the end), and then we copy those elements
	//  into the newly allocated space

	// allocate the space to hold as many elements as are within range
	auto data = _alloc.allocate(e - b);

	// initialize and return a pair value constructed from data and the
	//  value returned by uninitialized copy
	return { data, std::uninitialized_copy(b, e, data) };
}

void StringVector::free() {

	// this member destroys the elements and then deallocates the space that this StringVector
	//  allocated.

	// may not deallocate a 0-ptr: if _elements = 0, there's no work to do
	if (_elements)
	{
		// destroy the old elements in reverse order
		for (auto p = _first_free; p != _elements; )
			_alloc.destroy(--p);

		_alloc.deallocate(_elements, _cap - _elements);
	}
}

StringVector::StringVector(const StringVector &v) {

	// copy ctor is straightforward, given the allocate_and_copy function

	range_initialize(v.begin(), v.end());
}


StringVector &StringVector::operator=(const StringVector &rhs) {

	auto newData = allocate_and_copy(rhs.begin(), rhs.end());
	free();

	_elements = newData.first;
	_first_free = newData.second;

	return *this;
}

void StringVector::reallocate() {

	// plan to allocate space for twice as many elements as the current size
	auto newCapacity = size() ? 2 * size() : 1;

	// call allocate_and_move
	allocate_and_move(newCapacity);
}

void StringVector::reserve(size_t newCapacity) {

	if (newCapacity <= capacity()) return;

	allocate_and_move(newCapacity);
}

void StringVector::resize(size_t count) {

	resize(count, std::string());
}


void StringVector::resize(size_t count, const std::string &s) {

	if (count > size())
	{
		if (count > capacity())
			reserve(count * 2);

		for (size_t i = size(); i != count ; ++i)
			_alloc.construct(_first_free++, s);
	}
	else
	{
		while (_first_free != _elements + count)
			_alloc.destroy(--_first_free);
	}
}

StringVector::StringVector(std::initializer_list<std::string> list_o_strings) {

	range_initialize(list_o_strings.begin(), list_o_strings.end());
}

void StringVector::range_initialize(const std::string *ps1, const std::string *ps2) {

	// call allocate_and_copy to allocate exactly as many elements as in v
	auto newData = allocate_and_copy(ps1, ps2);

	_elements = newData.first;
	_first_free = newData.second;

}

void StringVector::allocate_and_move(size_t newCapacity) {

	// this function :  1. allocates memory for a new, larger array of strings
	//                  2. constructs the first part of that space to hold the existing elements
	//                  3. destroys the elements in the existing memory and deallocates that memory
	// It accomplishes these tasks while avoiding the overhead of copying the data within the
	//  strings, by using the string's move constructor, and the utility move function to signal its
	//  intention to use the move ctor - thereby avoiding use of the string's copy ctor

	// allocate new memory
	auto newData = _alloc.allocate(newCapacity);

	// move the data from the old memory to the new
	auto dest = newData;                                // ptr to the next free pos in new array
	auto elem = _elements;                              // ptr to the next element in old array
	for (size_t i = 0; i != size(); ++i)
		_alloc.construct(dest++, std::move(*elem++));

	free();     // free the old space after moving the elements

	// update the data structure to point to the new elements
	_elements = newData;
	_first_free = dest;
	_cap = _elements + newCapacity;
}

StringVector::StringVector(StringVector &&sv) noexcept
	: _elements(sv._elements),
	  _first_free(sv._first_free),
	  _cap(sv._cap)
{
	// move ctor for StringVector
	// initializer list: new members take over the resources in sv

	// leave sv in a state where it is safe to call the dtor
	sv._elements = sv._first_free = sv._cap = nullptr;
}

StringVector &StringVector::operator=(StringVector &&rhs) noexcept {

	// move assignment operator for StringVector
	// first, directly test for self-assignment
	if (this != &rhs)
	{
		free();         // free the existing elements

		// take over resources
		_elements = rhs._elements;
		_first_free = rhs._first_free;
		_cap = rhs._cap;

		// leave rhs in a sata where it is safe to call the dtor
		rhs._elements = rhs._first_free = rhs._cap = nullptr;
	}

	return *this;
}

bool operator==(const StringVector& lhs, const StringVector& rhs)
{
	return (lhs.size() == rhs.size()) && std::equal(lhs._elements, lhs._first_free, rhs._elements);
}

bool operator!=(const StringVector& lhs, const StringVector& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const StringVector &lhs, const StringVector &rhs) {

	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

bool operator>(const StringVector &lhs, const StringVector &rhs) {

	return rhs > lhs;
}

bool operator<=(const StringVector &lhs, const StringVector &rhs) {

	return !(rhs > lhs);
}

bool operator>=(const StringVector &lhs, const StringVector &rhs) {

	return !(lhs < rhs);
}

StringVector &StringVector::operator=(std::initializer_list<std::string> rhs) {

	// assignment operator using an initializer list
	// uses allocate_and_copy() to allocate space and copy elements from the given range
	auto data = allocate_and_copy(rhs.begin(), rhs.end());

	// destroy the elements in this object, free the space
	free();

	// update data members to point to the new space
	_elements = data.first;
	_first_free = _cap = data.second;

	return *this;
}
