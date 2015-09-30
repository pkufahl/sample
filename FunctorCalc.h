//
// Created by Peter Kufahl on 8/26/15.
//

#ifndef SAMPLE_FUNCTORCALC_H
#define SAMPLE_FUNCTORCALC_H

#include <iostream>
#include <string>
#include <map>
#include <functional>

void test_FunctorCalc();

int FCadd(int i, int j);

auto FCmod = [](int i, int j){ return i % j; };

struct FCdiv {
	int operator()(int i, int j) const
	{
		return i/j;
	}
};



#endif //SAMPLE_FUNCTORCALC_H
