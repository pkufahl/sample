//
// Created by Peter Kufahl on 8/26/15.
//

#include "FunctorCalc.h"

int FCadd (int i, int j) { return i+j; }

auto FunctorCalc = std::map<std::string, std::function<int(int,int)>> {

		{ "+", FCadd },                                 // function pointer
		{ "-", std::minus<int>() },                     // library functor
		{ "/", FCdiv() },                               // user-defined functor
		{ "*", [](int i, int j){ return i * j; } },     // anon. lambda
		{ "%", FCmod }                                  // named lambda object (closure)
};


void test_FunctorCalc()
{
	while (std::cout << "enter as: num operator num :\n", true)
	{
		int lhs, rhs;
		std::string op;
		std::cin >> lhs >> op >> rhs;
		std::cout << FunctorCalc[op](lhs, rhs) << std::endl;
	}
}