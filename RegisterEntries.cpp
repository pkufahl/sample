//
// Created by Peter Kufahl on 8/18/15.
//

#include "RegisterEntries.h"

int Request::_st_counter = 0;

void RegisterEntries::test_register_entries() { }

Request::Request() {
	_id = _st_counter++;
}

// each Request that gets made gets a unique id by incrementing a static data member
Request::Request(const std::string &name) {
	_id = _st_counter++;
	_name = name;
}

// operator= : handles self-assignment by incrementing the count in the rhs
//  before decrementing the count in the lhs
PointerLikeHasPtr& PointerLikeHasPtr::operator=(const PointerLikeHasPtr &rhs) {

	++*rhs._use;

	if (--*_use == 0)
	{
		delete _ps;
		delete _use;
	}

	_ps = rhs._ps;
	_i = rhs._i;
	_use = rhs._use;

	return *this;
}

// if the reference count goes to 0, delete the string and the counter
PointerLikeHasPtr::~PointerLikeHasPtr() {

	if (--*_use == 0) {
		delete _ps;
		delete _use;
	}
}

ValueLikeHasPtr &ValueLikeHasPtr::operator=(ValueLikeHasPtr hp) {
	// Old way - hp must be passed in by reference and swap() need not be defined
	/*
	std::string *new_string_ptr = new std::string(*hp._ps);
	delete _ps;
	_ps = new_string_ptr;
	_i = hp._i;
	return *this; */

	// new way, using the idiom known as "copy and swap", since swap is a defined friend function
	// swap the contents of the left-hand operand with the local variable hp
	// This variable hp is passed in by value
	swap (*this, hp);   // hp now points to the memory this object had used
	return *this;       // hp is destroyed, which deletes the pointer in hp
}