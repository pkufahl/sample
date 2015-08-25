//
// Created by Peter Kufahl on 8/25/15.
// Sample application that compiles revenue data based on some id number, quantity and revenue per item
//

#ifndef SAMPLE_REVENUEDATA_H
#define SAMPLE_REVENUEDATA_H

#include <string>
#include <iostream>

class RevenueData {
public:
	friend std::istream& operator>>(std::istream& input, RevenueData& rev);         // input
	friend std::ostream& operator<<(std::ostream& output, const RevenueData& rev);  // output
	friend RevenueData operator+(const RevenueData& lhs, const RevenueData& rhs);   // addition
	friend bool operator==(const RevenueData& lhs, const RevenueData& rhs);         // equality
	friend bool operator!=(const RevenueData& lhs, const RevenueData &rhs);         // inequality
public:
	RevenueData(const std::string& str, unsigned n, double p)
		: _itemID(str),
		  _unitsSold(n),
		  _revenue(n * p)
	{ }

	RevenueData() : RevenueData("", 0, 0.0f) { }
	RevenueData(const std::string& str) : RevenueData(str, 0, 0.0f) { }
	RevenueData(std::istream& input);

	RevenueData& operator=(const std::string& rhs);     // assignment using string for _itemID
	RevenueData& operator+=(const RevenueData& rhs);    // compound assignment

	std::string itemID() const { return _itemID; }

private:
	inline double average_price() const;

	std::string _itemID;
	unsigned _unitsSold = 0;
	double _revenue = 0.0;
};

std::istream& operator>>(std::istream& input, RevenueData& rev);
std::ostream& operator<<(std::ostream& output, const RevenueData& rev);
RevenueData operator+(const RevenueData& lhs, const RevenueData& rhs);
bool operator==(const RevenueData& lhs, const RevenueData& rhs);
bool operator!=(const RevenueData& lhs, const RevenueData &rhs);

inline double RevenueData::average_price() const
{
	return _unitsSold ? _revenue/_unitsSold : 0;
}

#endif //SAMPLE_REVENUEDATA_H
