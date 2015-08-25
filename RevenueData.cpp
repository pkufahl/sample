//
// Created by Peter Kufahl on 8/25/15.
//

#include "RevenueData.h"


RevenueData::RevenueData(std::istream &input) : RevenueData()
{
	input >> *this;
}


RevenueData& RevenueData::operator+=(const RevenueData &rhs) {

	_unitsSold += rhs._unitsSold;
	_revenue += rhs._revenue;
	return *this;
}


std::istream &operator>>(std::istream &input, RevenueData &rev) {

	double price = 0.0;
	input >> rev._itemID >> rev._unitsSold >> price;

	if(input)
		rev._revenue = price * rev._unitsSold;
	else
		rev = RevenueData();

	return input;
}

std::ostream &operator<<(std::ostream &output, const RevenueData &rev) {

	output << rev._itemID << " " << rev._unitsSold << " " << rev._revenue << " " << rev.average_price();

	return output;
}

RevenueData operator+(const RevenueData &lhs, const RevenueData &rhs) {

	RevenueData rev = lhs;
	rev += rhs;
	return rev;
}

bool operator==(const RevenueData& lhs, const RevenueData& rhs)
{
	return lhs._itemID == rhs._itemID &&
           lhs._unitsSold == rhs._unitsSold &&
           lhs._revenue == rhs._revenue;
}

bool operator!=(const RevenueData& lhs, const RevenueData &rhs)
{
	return !(lhs == rhs);
}


RevenueData &RevenueData::operator=(const std::string &rhs) {

	*this = RevenueData(rhs);
	return *this;
}
