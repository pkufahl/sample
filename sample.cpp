//
// Created by Peter Kufahl on 8/17/15.
//

#include "sample.h"

int main()
{
	// test_word_counter();
	// test_messages();
	// test_queries();
	// test_simplestring();
	/*
	std::string request("Sample Request");
	RevenueData samp = request;

	std::cout << samp << std::endl;
	*/
	/*
	SimpleString str("i'm done");
	std::cout << str << std::endl;
	*/

	// test_stringvec_initlist();
	// test_subscripts();
	// test_incs_decs();
	// test_InputFunctor1();
	// test_InputFunctor1_vec();
	// test_IsEqualTo();
	// test_IsInRange("data.txt");
	// test_Biggies("data.txt");
	// test_FunctorCalc();
	// test_ConvertRevenue();

	test_oop_quote();

	return 0;
}

void test_word_counter() {
	std::cout << "trying word counting, using map" << std::endl;
	WordCounter tmpWC("longdata.txt");

	timeval start1, start2, finish1, finish2;
	long int micro1, micro2, sec1, sec2, words1, words2;

	gettimeofday(&start1, 0);
	tmpWC.do_betterWordCount();
	gettimeofday(&finish1, 0);
	words1 = tmpWC.get_words();

	std::cout << "trying word counting, using unordered map" << std::endl;

	gettimeofday(&start2, 0);
	tmpWC.do_unorderedBetterWordCount();
	gettimeofday(&finish2, 0);
	words2 = tmpWC.get_words();

	sec1 = finish1.tv_sec - start1.tv_sec;
	sec2 = finish2.tv_sec - start2.tv_sec;
	micro1 = finish1.tv_usec - start1.tv_usec;
	micro2 = finish2.tv_usec - start2.tv_usec;

	std::cout << "using the ordered map, word counting took " << sec1 << " seconds and " << micro1 << " usec (" << words1 << " words)" << std::endl;
	std::cout << "using the unordered map, word counting took " << sec2 << " seconds and " << micro2 << " usec (" << words2 << " words)" << std::endl;

	std::cout << "performance difference of " << 100 * (micro1 - micro2) / micro1 << " percent" << std::endl;
	std::cout << "done" << std::endl;
}

void test_messages() {

	std::cout << "testing message / folder bookkeeping system" << std::endl;

	Message m1("I'm message 1!"), m2("I'm message 2!"), m3("I'm message 3!"), m4("I'm message 4!");
	Folder f1, f2, f3;
	m1.save(f1);
	m2.save(f1);
	m3.save(f2);
	m4.save(f3);

	std::cout << "Experiment 1: f1-> m1, m2 ... f2-> m3 ... f3-> m4" << std::endl;
	std::cout << "Contents of folder 1: ";
	f1.print_contents();
	std::cout << "Contents of folder 2: ";
	f2.print_contents();
	std::cout << "Contents of folder 3: ";
	f3.print_contents();

	std::cout << "\nExperiment 2: put m1 into f2 and f3" << std::endl;
	m1.save(f2);
	m1.save(f3);
	m1.remove(f1);
	std::cout << "Contents of folder 1: ";
	f1.print_contents();
	std::cout << "Contents of folder 2: ";
	f2.print_contents();
	std::cout << "Contents of folder 3: ";
	f3.print_contents();

	std::cout << "\nExperiment 3: capitalizing m1 ..." << std::endl;
	m1.set("I'M MESSAGE 1!");
	std::cout << "Contents of folder 1: ";
	f1.print_contents();
	std::cout << "Contents of folder 2: ";
	f2.print_contents();
	std::cout << "Contents of folder 3: ";
	f3.print_contents();

	std::cout << "\nExperiment 4: swap m2 and m4" << std::endl;
	swap(m2, m4);
	std::cout << "Contents of m2: ";
	m2.print_contents();
	std::cout << "Contents of m4: ";
	m4.print_contents();

	std::cout << "Contents of folder 1: ";
	f1.print_contents();
	std::cout << "Contents of folder 2: ";
	f2.print_contents();
	std::cout << "Contents of folder 3: ";
	f3.print_contents();
	std::cout << "Swapping back ..." << std::endl;
	swap(m2, m4);
	std::cout << "Contents of m2: ";
	m2.print_contents();
	std::cout << "Contents of m4: ";
	m4.print_contents();
	std::cout << "Contents of folder 1: ";
	f1.print_contents();
	std::cout << "Contents of folder 2: ";
	f2.print_contents();
	std::cout << "Contents of folder 3: ";
	f3.print_contents();

	std::cout << "\nExperiment 5: swap f1 and f3" << std::endl;
	swap(f1, f3);
	std::cout << "Contents of folder 1: ";
	f1.print_contents();
	std::cout << "Contents of folder 2: ";
	f2.print_contents();
	std::cout << "Contents of folder 3: ";
	f3.print_contents();
	std::cout << "Swapping back ..." << std::endl;
	swap(f1, f3);
	std::cout << "Contents of folder 1: ";
	f1.print_contents();
	std::cout << "Contents of folder 2: ";
	f2.print_contents();
	std::cout << "Contents of folder 3: ";
	f3.print_contents();

}

void run_queriesSTL(std::ifstream& infile) {

	TextQuerySTL tq(infile);        // store the file and build the query map

	// iterate with the user: prompt for a word to find and print the results
	while (true)
	{
		std::cout << "Enter the word to look for, or 'q' to quit: ";
		string s;

		if (!(std::cin >> s) || (s == "q")) break;

		// run the query and print the results
		print(std::cout, tq.query(s)) << std::endl;
	}

}

void test_queries() {

	std::ifstream ifs ("longdata.txt");
	std::ifstream ifs2 ("longdata.txt");

	// run_queriesSTL(ifs);
	// run_queriesAlloc(ifs);
	run_both_queries(ifs, ifs2);

}

void run_queriesAlloc(std::ifstream &infile) {

	TextQueryAlloc tq(infile);        // store the file and build the query map

	// iterate with the user: prompt for a word to find and print the results
	while (true)
	{
		std::cout << "Enter the word to look for, or 'q' to quit: ";
		string s;

		if (!(std::cin >> s) || (s == "q")) break;

		// run the query and print the results
		print(std::cout, tq.query(s)) << std::endl;
	}
}

void run_both_queries(std::ifstream &infile1, std::ifstream &infile2) {


	timeval start1, start2, finish1, finish2;
	long int micro1, micro2, sec1, sec2;
	long int microCtor1, microCtor2, secCtor1, secCtor2;

	gettimeofday(&start1, 0);
	TextQuerySTL tqSTL(infile1);
	gettimeofday(&finish1, 0);
	secCtor1 = finish1.tv_sec - start1.tv_sec;
	microCtor1 = (finish1.tv_usec + finish1.tv_sec * 1000000) - (start1.tv_usec + start1.tv_sec * 1000000);

	gettimeofday(&start2, 0);
	TextQueryAlloc tqMOVE(infile2);
	gettimeofday(&finish2, 0);
	secCtor2 = finish2.tv_sec - start2.tv_sec;
	microCtor2 = (finish2.tv_usec + finish2.tv_sec * 1000000) - (start2.tv_usec + start2.tv_sec * 1000000);

	std::cout << "using vector<string>, this took " << secCtor1 << " seconds and " << microCtor1 << " usec" << std::endl;
	std::cout << "using std::move, this took " << secCtor2 << " seconds and " << microCtor2 << " usec" << std::endl;

	std::cout << "performance difference of " << 100 * (microCtor1 - microCtor2) / microCtor1 << " percent" << std::endl;

	// iterate with the user: prompt for a word to find and print the results
	while (true)
	{
		std::cout << "Enter the word to look for, or 'q' to quit: ";
		string s;

		if (!(std::cin >> s) || (s == "q")) break;

		// run the query and print the results
		gettimeofday(&start1, 0);
		print(std::cout, tqSTL.query(s)) << std::endl;
		gettimeofday(&finish1, 0);

		// run the query and print the results
		gettimeofday(&start2, 0);
		print(std::cout, tqMOVE.query(s)) << std::endl;
		gettimeofday(&finish2, 0);

		sec1 = finish1.tv_sec - start1.tv_sec;
		sec2 = finish2.tv_sec - start2.tv_sec;
		micro1 = (finish1.tv_usec + finish1.tv_sec * 1000000) - (start1.tv_usec + start1.tv_sec * 1000000);
		micro2 = (finish2.tv_usec + finish2.tv_sec * 1000000) - (start2.tv_usec + start2.tv_sec * 1000000);

		std::cout << "using vector<string>, the search took " << sec1 << " seconds and " << micro1 << " usec" << std::endl;
		std::cout << "using std::move, the search took " << sec2 << " seconds and " << micro2 << " usec" << std::endl;

		std::cout << "performance difference of " << 100 * (micro1 - micro2) / micro1 << " percent" << std::endl;

	}

	std::cout << "done" << std::endl;

}

void test_simplestring() {

	char text[] = "world";

	// SimpleString s0;
	SimpleString s1("hello");
	SimpleString s2;
	{
		SimpleString s0;
		s2 = std::move(s0);
		std::cout << "s2 assigned to move:s0" << std::endl;
	}

	SimpleString s3 = s1;
	SimpleString s4(text);
	s2 = s1;

	if (s2 == s1)
		std::cout << "s2 == s1" << std::endl;

	foo(s1);
	bar(s1);
	foo("temporary");
	bar("temporary");
	SimpleString s5 = baz();

	std::vector<SimpleString> vec;

	vec.reserve(8);
	// vec.push_back(std::move(s0));
	vec.push_back(s1);
	vec.push_back(s2);
	vec.push_back(s3);
	vec.push_back(s4);
	vec.push_back(s5);
	vec.push_back(baz());
	vec.push_back("good job");

	for (const auto &str : vec)
	{
		std::cout << str.c_string() << std::endl;
	}

	std::cout << "input a string: ";
	SimpleString s6;
	std::cin >> s6;
	std::cout << s6 << std::endl;

	if (s6 > s1)
		std::cout << "s6 > s1" << std::endl;
	else if (s6 < s1)
		std::cout << "s6 < s1" << std::endl;

	return;

}

void test_stringvec_initlist() {

	StringVector vec;
	vec.reserve(6);
	std::cout << "capacity(reserve to 6): " << vec.capacity() << std::endl;

	vec.reserve(4);
	std::cout << "capacity(reserve to 4): " << vec.capacity() << std::endl;

	vec.push_back("hello");
	vec.push_back("world");

	vec.resize(4);

	for (auto i = vec.begin(); i != vec.end(); ++i)
		std::cout << *i << std::endl;
	std::cout << "-EOF-" << std::endl;

	vec.resize(1);

	for (auto i = vec.begin(); i != vec.end(); ++i)
		std::cout << *i << std::endl;
	std::cout << "-EOF-" << std::endl;

	StringVector vec_list{ "hello", "world", "pezy" };

	for (auto i = vec_list.begin(); i != vec_list.end(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl;

	// Test operator==

	const StringVector const_vec_list = { "hello", "world", "pezy" };
	if (vec_list == const_vec_list)
		for (const auto &str : const_vec_list)
			std::cout << str << " ";
	std::cout << std::endl;

	// Test operator<
	const StringVector const_vec_list_small = { "hello", "pezy", "ok" };
	std::cout << (const_vec_list_small < const_vec_list) << std::endl;

}

void test_subscripts()
{
	char text[] = "world";

	// SimpleString s0;
	SimpleString s1("hello");
	SimpleString s2;
	{
		SimpleString s0;
		s2 = std::move(s0);
		std::cout << "s2 assigned to move:s0" << std::endl;
	}

	SimpleString s3 = s1;
	SimpleString s4(text);
	s2 = s1;

	if (s2 == s1)
		std::cout << "s2 == s1" << std::endl;

	foo(s1);
	bar(s1);
	foo("temporary");
	bar("temporary");
	SimpleString s5 = baz();

	std::vector<SimpleString> vec;

	vec.reserve(8);
	// vec.push_back(std::move(s0));
	vec.push_back(s1);
	vec.push_back(s2);
	vec.push_back(s3);
	vec.push_back(s4);
	vec.push_back(s5);
	vec.push_back(baz());
	vec.push_back("good job");

	for (const auto &str : vec)
	{
		std::cout << str.c_string() << std::endl;
	}

	std::cout << "input a string: ";
	SimpleString s6;
	std::cin >> s6;
	std::cout << s6 << std::endl;

	if (s6 > s1)
		std::cout << "s6 > s1" << std::endl;
	else if (s6 < s1)
		std::cout << "s6 < s1" << std::endl;

	std::cout << "s5[2] is " << s5[2] << std::endl;


	return;

}

void test_incs_decs()
{
	StringBlob sb1{"aaaargh", "b", "c"};
	StringBlob sb2 = sb1;

	sb2[2] = "b";

	if (sb1 > sb2)
	{
		for (StringBlobPtr iter = sb1.begin(); iter < sb1.end(); ++iter)
			std::cout << iter.dereference() << " ";

		std::cout << std::endl;

	}

	ConstStringBlobPtr iter(sb2);
	std::cout << (iter + 2).dereference() << std::endl;
	std::cout << "size is: " << iter->size() << std::endl;
}

void test_ConvertRevenue()
{
	RevenueData rd("item-0000", 10000, 1.99);
	std::cout << "As type RevenueData: " << rd << std::endl;
	std::cout << "As type string: " << static_cast<std::string>(rd) << std::endl;
	std::cout << "As type double: " << static_cast<double>(rd) << std::endl;

}

void test_oop_quote()
{
	OOP_Quote quote1("apples", 0.50);
	print_total(std::cout, quote1, 1000);
}
