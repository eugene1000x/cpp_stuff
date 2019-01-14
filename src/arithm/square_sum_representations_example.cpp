
#include <eugenejonas/cpp_stuff/arithm/generators.h>
#include <eugenejonas/cpp_stuff/consumers.h>

#include <iostream>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>


using std::cin;
using std::cout;


/**
 * This program prints all representations of an integer n as a
 * sum of squares of two natural numbers.
 */
int main()
{
	int n;
	do
	{
		cout << "Enter n: ";
		cin >> n;
		if (n < 0)
		{
			cout << "Error: n must be non-negative!\n";
			continue;
		}

		eugenejonas::cpp_stuff::Printer <boost::tuple <int, int> > printer(cout);
		eugenejonas::cpp_stuff::generateSquareSumRepresentations(n, printer);
	}
	while (true);
	
	return 0;
}
