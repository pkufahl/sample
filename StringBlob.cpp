//
// Created by Peter Kufahl on 8/25/15.
//

#include "StringBlob.h"
#include <algorithm>       // lexicographical_compare

// **************************************************************************************************************
// StringBlob friend functions - operators
// **************************************************************************************************************

bool operator==(const StringBlob& lhs, const StringBlob& rhs)
{
	return *lhs._data == *rhs._data;

}

bool operator!=(const StringBlob& lhs, const StringBlob& rhs)
{
	return !(lhs == rhs);
}

bool operator< (const StringBlob& lhs, const StringBlob& rhs)
{
	return std::lexicographical_compare(lhs._data->begin(), lhs._data->end(), rhs._data->begin(), rhs._data->end());
}

bool operator> (const StringBlob& lhs, const StringBlob& rhs)
{
	return rhs < lhs;
}

bool operator<=(const StringBlob& lhs, const StringBlob& rhs)
{
	return !(rhs < lhs);
}

bool operator>=(const StringBlob& lhs, const StringBlob& rhs)
{
	return !(lhs < rhs);
}

// **************************************************************************************************************
// StringBlobPtr friend functions - operators
// **************************************************************************************************************

bool operator==(const StringBlobPtr& lhs, const StringBlobPtr& rhs)
{
	return lhs._current == rhs._current;
}

bool operator!=(const StringBlobPtr& lhs, const StringBlobPtr& rhs)
{
	return !(lhs == rhs);
}

bool operator< (const StringBlobPtr& lhs, const StringBlobPtr& rhs)
{
	return lhs._current < rhs._current;
}

bool operator> (const StringBlobPtr& lhs, const StringBlobPtr& rhs)
{
	return lhs._current > rhs._current;
}

bool operator<=(const StringBlobPtr& lhs, const StringBlobPtr& rhs)
{
	return lhs._current <= rhs._current;
}

bool operator>=(const StringBlobPtr& lhs, const StringBlobPtr& rhs)
{
	return lhs._current >= rhs._current;
}


// **************************************************************************************************************
// ConstStringBlobPtr friend functions - operators
// **************************************************************************************************************

bool operator==(const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs)
{
	return lhs._current == rhs._current;
}

bool operator!=(const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs)
{
	return !(lhs == rhs);
}

bool operator< (const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs)
{
	return lhs._current < rhs._current;
}

bool operator> (const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs)
{
	return lhs._current > rhs._current;
}

bool operator<=(const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs)
{
	return lhs._current <= rhs._current;
}

bool operator>=(const ConstStringBlobPtr& lhs, const ConstStringBlobPtr& rhs)
{
	return lhs._current >= rhs._current;
}

// **************************************************************************************************************
// StringBlob copy/move assigmnent operators
// **************************************************************************************************************

StringBlob& StringBlob::operator=(const StringBlob &sb)
{

	_data = make_shared<vector<string>>(*sb._data);
	return *this;
}

StringBlob& StringBlob::operator=(StringBlob &&sb) noexcept
{
	if (this != &sb)
	{
		_data = std::move(sb._data);
		sb._data = nullptr;
	}

	return *this;
}

// **************************************************************************************************************
// StringBlob member functions
// **************************************************************************************************************

StringBlobPtr StringBlob::begin()
{
	return StringBlobPtr(*this);
}

StringBlobPtr StringBlob::end()
{
	return StringBlobPtr(*this, _data->size());
}

ConstStringBlobPtr StringBlob::cbegin() const
{
	return ConstStringBlobPtr(*this);
}

ConstStringBlobPtr StringBlob::cend() const
{
	return ConstStringBlobPtr(*this, _data->size());
}
