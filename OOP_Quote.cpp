//
// Created by Peter Kufahl on 8/27/15.
//

#include "OOP_Quote.h"

double print_total(std::ostream& os, const OOP_Quote& item, std::size_t n)
{
	// dynamic binding: because 1. OOP_Quote::net_price() is a virtual function, and
	//                          2. item is passed in by reference,
	// item.net_price(n) calls OOP_Quote::net_price() or Bulk_Quote::net_price(),
	//  depending on the type of the parameter item
	double ret = item.net_price(n);

	// calls OOP_Quote::product_ID()
	os << "Product ID: " << item.product_ID() << "\t\t# sold: " << n << "\ttotal due: " << ret << std::endl;

	return ret;
}

double Bulk_Quote::net_price(size_t count) const {

	if (count >= _quantityLimit)
		return count * (1 - _discount) * _price;
	else
		return count * _price;
}

double Trial_Quote::net_price(size_t count) const {

	if (count <= _quantityLimit)
		return count * (1 - _discount) * _price;
	else
		return count * _price;
}
