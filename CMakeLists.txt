cmake_minimum_required(VERSION 3.2)
project(sample)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES sample.cpp WordCounter.cpp RegisterEntries.cpp StringVector.cpp StringVector.h TextQuerySTL.cpp TextQuerySTL.h TextQueryAlloc.cpp TextQueryAlloc.h SimpleString.cpp SimpleString.h RevenueData.cpp RevenueData.h StringBlob.cpp StringBlob.h InputFunctor.cpp InputFunctor.h FunctorCalc.cpp FunctorCalc.h OOP_Quote.cpp OOP_Quote.h)
add_executable(sample ${SOURCE_FILES} Message.cpp Message.h)