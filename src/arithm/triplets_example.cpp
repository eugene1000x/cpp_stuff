
#include <eugenejonas/cpp_stuff/arithm/generators.h>
#include <eugenejonas/cpp_stuff/consumers.h>

#include <iostream>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>


using std::cin;
using std::cout;


/**
 * This program reads a non-negative integer n and prints all triplets
 * (a, b, c) such that 0 <= a <= b <= c <= n and a ^ 2 + b ^ 2 = c ^ 2.
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

		eugenejonas::cpp_stuff::Printer <boost::tuple <int, int, int> > printer(cout);
		eugenejonas::cpp_stuff::generateTriplets(n, printer);
	}
	while (true);
	
	return 0;
}
