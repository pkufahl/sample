//
// Created by Peter Kufahl on 8/18/15.
//

#ifndef SAMPLE_REGISTERENTRIES_H
#define SAMPLE_REGISTERENTRIES_H

#include <string>
#include <memory>       // shared_ptr

class RegisterEntries {
public:
	RegisterEntries() = default;
	~RegisterEntries() = default;

	void test_register_entries();
};

class Request {
public:
	Request();
	Request(const std::string &name);

	// prevent copying of this class since there is no sensible meaning behind making a copy of a unique Request
	Request(const Request&) = delete;
	Request& operator=(const Request&) = delete;

	const int id() const { return _id; }
	const std::string name() const { return _name; }

private:
	std::string _name;
	int _id;
	static int _st_counter;

};

// this class "acts like a value", meaning that it has its own copy of the
//  resource that it manages. For valuelike behavior, it has:
//  1. a copy ctor that copies the string, not just the ptr
//  2. a destructor to free the string
//  3. a copy assignment optr that frees the object's existing string a copies the string from its
//    right-hand operand
//  swap function is defined to properly manage calls to swap() by stl algorithms - instead of std::swap(),
//   we use our own version to avoid dynamic memory allocation
class ValueLikeHasPtr {
public:
	friend void swap(ValueLikeHasPtr&, ValueLikeHasPtr&);

	ValueLikeHasPtr(const std::string &s = std::string())
			: _ps(new std::string(s)),
			  _i(0)
	{ }

	// this copy ctor copies all the members: it dynamically allocates a new string and copies the
	//  object to which _ps points, rather than copying _ps itself.
	ValueLikeHasPtr(const ValueLikeHasPtr& hp)
			: _ps(new std::string(*hp._ps)),
              _i(hp._i)
	{ }

	ValueLikeHasPtr & operator=(ValueLikeHasPtr hp);

	~ValueLikeHasPtr()
	{
		delete _ps;
	}

private:
	std::string *_ps;
	int _i;
};

inline void swap(ValueLikeHasPtr& lhs, ValueLikeHasPtr& rhs) {

	using std::swap;
	swap(lhs._ps, rhs._ps);
	swap(lhs._i, rhs._i);
}

// this class "acts like a pointer", meaning that the copy ctor and copy assignment optr both
//  copy the pointer member, not the string to which that pointer points. This class still needs its own destructor
//  to free the memory allocated by the ctor that takes a string. However, it cannot unilaterally free its
//  associated string: it does so only when the last HasPtr pointing to that string goes away.
// instead of shared_ptr, this class uses a reference counting class to manage its resource directly.
//
// note: defining a swap() function for this class would be pointless because (unlike in ValueLikeHasPtr), there's
//  no dynamic memory allocation involved in a std::swap - so a specific version of swap() wouldn't improve performance
class PointerLikeHasPtr {
public:
	PointerLikeHasPtr(const std::string &s = std::string())
			: _ps(new std::string(s)),
              _i(0), _use(new std::size_t(1))
	{ }

	PointerLikeHasPtr(const PointerLikeHasPtr& hp)
			: _ps(hp._ps),
              _i(hp._i),
              _use(hp._use)
	{
		++*_use;
	}

	PointerLikeHasPtr& operator=(const PointerLikeHasPtr&);

	~PointerLikeHasPtr();

private:
	std::string *_ps;
	int _i;
	std::size_t *_use;
};


#endif //SAMPLE_REGISTERENTRIES_H
