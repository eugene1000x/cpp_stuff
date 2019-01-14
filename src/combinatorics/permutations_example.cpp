
#include <eugenejonas/cpp_stuff/combinatorics/generators.h>
#include <eugenejonas/cpp_stuff/combinatorics/permutation.h>
#include <eugenejonas/cpp_stuff/consumers.h>

#include <iostream>
#include <vector>


using eugenejonas::cpp_stuff::Collector;
using eugenejonas::cpp_stuff::Counter;
using eugenejonas::cpp_stuff::Permutation;
using eugenejonas::cpp_stuff::PermutationGenerator;
using eugenejonas::cpp_stuff::Printer;

using std::cin;
using std::cout;
using std::vector;


int main()
{
	const int length = 4;


	
	// test printer
	
	Printer <Permutation> printer(cout);
	PermutationGenerator(&printer, length);

	
	
	// test collector
	
	cout << "\n";
	
	Collector <Permutation, vector <Permutation> > collector;
	PermutationGenerator(&collector, length);
	
	cout << "Printing vector elements...\n";
	
	for (vector <Permutation> ::const_iterator it = collector.getElements().begin(); it != collector.getElements().end(); ++it)
	{
		cout << *it << "\n";
	}
	
	cout << "Vector length: " << collector.getElements().size() << "\n";

	
	
	// test counter
	
	Counter <Permutation> c;
	PermutationGenerator(&c, length);
	
	cout << "Total number of permutations: " << c.getCount() << "\n";



	return 0;
}
