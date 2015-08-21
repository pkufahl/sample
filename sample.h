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

void test_word_counter();
void test_messages();
void run_queriesSTL(std::ifstream& infile);
void run_queriesAlloc(std::ifstream& infile);
void run_both_queries(std::ifstream& infile1, std::ifstream& infile2);

void test_queries();

#endif //SAMPLE_SAMPLE_H
