
#include <eugenejonas/cpp_stuff/combinatorics/calculator.h>

#include <iostream>


using eugenejonas::cpp_stuff::Calculator;

using std::cin;
using std::cout;


/**
 * This program calculates binomial coefficient C(n, k).
 * It supports long number arithmetics.
 */
int main()
{
	int n, k;

	do
	{
		do
		{
			cout << "Enter n: ";
			cin >> n;
			
			if (n < 0)
			{
				cout << "Error: n must be non-negative!\n";
			}
		}
		while (n < 0);

		do
		{
			cout << "Enter k: ";
			cin >> k;
			
			if (k < 0)
			{
				cout << "Error: k must be non-negative!\n";
			}
		}
		while (k < 0);

		cout << "C(" << n << ", " << k << "): ";
		Calculator::calculateBinomialCoefficientPascalTriangle(n, k).writeln();
	}
	while (true);

	return 0;
}
