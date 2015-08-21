//
// Created by Peter Kufahl on 8/17/15.
//

#include "sample.h"

int main()
{
	// test_word_counter();
	// test_messages();

	test_queries();
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
