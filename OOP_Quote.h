//
// Created by Peter Kufahl on 8/27/15.
// Demonstration of OOP principles: data abstraction, inheritance and dynamic binding
//
// OOP_Quote is a base class representing generic quote information (price, product id)
//  it has a virtual member function
//  by necessity, it must have a virtual dtor
//
// Discount_Quote is derived from OOP_Quote and makes net_price() a pure virtual function
// Bulk_Quote is derived from Discount_Quote: discounts price if quantity above a minimum
// Trial_Quote is also derived from Discount_Quote: discounts price if quantity below a maximum
//
#ifndef SAMPLE_OOP_QUOTE_H
#define SAMPLE_OOP_QUOTE_H

#include <string>
#include <iostream>

class OOP_Quote {
public:
	OOP_Quote() = default;

	OOP_Quote(const std::string& prodID, double salesPrice)
			: _productID(prodID),
			  _price(salesPrice)
	{ }

	virtual ~OOP_Quote() = default;

	std::string product_ID() const { return _productID; }
    virtual double net_price(std::size_t numSold) const { return numSold * _price; }
private:
	std::string _productID;
protected:
	double _price = 0.0;
};

class Discount_Quote : public OOP_Quote {

public:
	Discount_Quote() = default;

	Discount_Quote(const std::string& prodID, double price, std::size_t qty, double discount)
		: OOP_Quote(prodID, price),
	      _quantityLimit(qty),
	      _discount(discount)
	{ }

	double net_price(std::size_t) const = 0;
protected:
	std::size_t _quantityLimit = 0;         // min/max of quantity, as far as discounting is concerned
	double _discount = 0;
};

class Bulk_Quote : public Discount_Quote {
public:
	Bulk_Quote() = default;

	Bulk_Quote(const std::string& prodID, double price, std::size_t minimumQuantity, double discount)
			: Discount_Quote(prodID, price, minimumQuantity, discount)
	{ }

	double net_price(std::size_t) const override;               // explicitly stated to override OOP_Quote::net_price()

private:

};

class Trial_Quote : public Discount_Quote {
public:
    Trial_Quote() = default;

    Trial_Quote(const std::string& prodID, double price, std::size_t maxQuantity, double discount)
		    : Discount_Quote(prodID, price, maxQuantity, discount)
    { }

    double net_price(std::size_t) const override;               // explicitly stated to override OOP_Quote::net_price()

private:

};


double print_total(std::ostream& os, const OOP_Quote& item, std::size_t n);

#endif //SAMPLE_OOP_QUOTE_H
