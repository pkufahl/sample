//
// Created by Peter Kufahl on 8/20/15.
//
// StringVector is a simplified "vector" of strings that manages its own memory allocation
//
// the vector<> class stores its elements in contiguous storage, and to obtain performance it preallocates
//  enough storage to hold more elements than are needed. Each vector member that adds elements checks whether there
//  is enough space available for another element. If there isn't enough space left, then the vector gets
//  reallocated: the vector obtains new space, moves the existing elements into that space, frees the old
//  space, and adds the new element.
//
// StringVector will use a similar strategy, and use an allocator to obtain raw memory. Because the memory
//  an allocator allocates is unconstructed, use allocator's construct() member to create objects in that
//  space when we need a new element. Similarly, when we remove an element, we use the destroy() member to
//  destroy the element.
//
// StringVector has three ptrs into the space it uses for its elements:
//  _elements       pts to the 1st element in the allocated memory
//  _first_free     pts to just beyond the last element
//  _cap            pts to just past the end of the allocated memory
//
// There's also a data member named _alloc that is an allocator<string>. It allocates the memory
//  used by a StringVector. I tried making it a static data member but it wasn't linking.
//
#ifndef SAMPLE_STRINGVECTOR_H
#define SAMPLE_STRINGVECTOR_H

#include <memory>   // allocator
#include <string>
#include <initializer_list>


class StringVector {
	friend bool operator==(const StringVector& lhs, const StringVector& rhs);
	friend bool operator!=(const StringVector& lhs, const StringVector& rhs);
	friend bool operator< (const StringVector& lhs, const StringVector& rhs);
	friend bool operator> (const StringVector& lhs, const StringVector& rhs);
	friend bool operator<=(const StringVector& lhs, const StringVector& rhs);
	friend bool operator>=(const StringVector& lhs, const StringVector& rhs);

public:
	StringVector() :                                    // _alloc is default initialized
	 _elements(nullptr),
     _first_free(nullptr),
     _cap(nullptr)
	{ }

	StringVector(const StringVector&);
	StringVector(std::initializer_list<std::string>);
	StringVector& operator=(const StringVector&);

	StringVector(StringVector&&) noexcept;              // move ctor
	StringVector& operator=(StringVector&&) noexcept;   // move assignment operator

	~StringVector()
	{
		free();
	}

	StringVector& operator=(std::initializer_list<std::string> rhs);

    std::string& operator[](std::size_t n) { return _elements[n]; }
    const std::string& operator[](std::size_t n) const { return _elements[n]; }


	void push_back(const std::string&);                 // copy an element

	size_t size() const
	{
		return _first_free - _elements;
	}

	size_t capacity() const
	{
		return _cap - _elements;
	}

	std::string* begin() const
	{
		return _elements;
	}

	std::string* end() const
	{
		return _first_free;
	}

	void reserve(size_t newCapacity);
	void resize(size_t count);
	void resize(size_t count, const std::string& s);

	std::string& at(size_t pos) { return *(_elements + pos); }
	const std::string& at(size_t pos) const { return *(_elements + pos); }

private:
	/*static*/
    static std::allocator <std::string> _alloc;      // allocates the elements

	void check_and_allocate()                           // used by functions that add elements
	{
		if (size() == capacity()) reallocate();
	}

	std::pair<std::string*, std::string*> allocate_and_copy (const std::string*, const std::string*);

	void allocate_and_move(size_t newCapacity);

	void range_initialize(const std::string*, const std::string*);

	void free();                // destroy the elements and free the space
	void reallocate();          // get more space and copy over the existing elements
	std::string *_elements;      // ptr to the first element in the array
	std::string *_first_free;    // ptr to the first free element in the array
	std::string *_cap;           // ptr to one location past the end of the array
};

bool operator==(const StringVector& lhs, const StringVector& rhs);
bool operator!=(const StringVector& lhs, const StringVector& rhs);
bool operator< (const StringVector& lhs, const StringVector& rhs);
bool operator> (const StringVector& lhs, const StringVector& rhs);
bool operator<=(const StringVector& lhs, const StringVector& rhs);
bool operator>=(const StringVector& lhs, const StringVector& rhs);

#endif //SAMPLE_STRINGVECTOR_H
