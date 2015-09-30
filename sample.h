//
// Created by Peter Kufahl on 8/17/15.
//

#ifndef SAMPLE_SAMPLE_H
#define SAMPLE_SAMPLE_H

#include <iostream>
#include <sys/time.h>
#include <fstream>

#include "WordCounter.h"
#include "RegisterEntries.h"
#include "Message.h"
#include "TextQuerySTL.h"
#include "TextQueryAlloc.h"
#include "SimpleString.h"
#include "RevenueData.h"
#include "StringBlob.h"
#include "InputFunctor.h"
#include "FunctorCalc.h"
#include "OOP_Quote.h"

void test_word_counter();
void test_messages();
void run_queriesSTL(std::ifstream& infile);
void run_queriesAlloc(std::ifstream& infile);
void run_both_queries(std::ifstream& infile1, std::ifstream& infile2);

void test_queries();
void test_simplestring();

void foo(SimpleString x) { std::cout << x.c_string() << std::endl; }
void bar(const SimpleString& x) { std::cout << x.c_string() << std::endl; }
SimpleString baz() { SimpleString ret("world"); return ret; }

void test_stringvec_initlist();
void test_subscripts();
void test_incs_decs();

void test_FunctorCalc();
void test_ConvertRevenue();

void test_oop_quote();

#endif //SAMPLE_SAMPLE_H
