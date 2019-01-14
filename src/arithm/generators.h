
#ifndef EUGENEJONAS__CPP_STUFF__ARITHM__GENERATORS_H
#define EUGENEJONAS__CPP_STUFF__ARITHM__GENERATORS_H


#include <eugenejonas/cpp_stuff/arithm/arithm_functions.h>
#include <eugenejonas/cpp_stuff/consumers.h>

#include <cassert>
#include <cmath>

#include <boost/tuple/tuple.hpp>


namespace eugenejonas::cpp_stuff
{


/**
 * Generates all possible representations of an integer as a sum of squares
 * of two natural numbers. The order of the addends does not matter, so
 * representations 100 = 0 ^ 2 + 10 ^ 2 and 100 = 10 ^ 2 + 0 ^ 2 are the same.
 *
 * The representations are generated as tuples of two elements, where
 * the first element is not greater than the second. The tuples
 * are generated in the ascending order by their first element.
 *
 * @param n The number, n >= 0.
 */
void generateSquareSumRepresentations(int n, Consumer <boost::tuple <int, int> > &consumer)
{
	boost::tuple <int, int> tuple;
	int &a = boost::tuples::get <0> (tuple);
	int &b = boost::tuples::get <1> (tuple);
	double sqrtndiv2 = std::sqrt(n / 2.0);
	
	consumer.start();
	
	for (a = 0; a <= sqrtndiv2; ++a)
	{
		if (isPerfectSquare(n - a * a, b))
		{
			consumer.feed(tuple);
		}
	}
	
	consumer.finish();
}

/**
 * Generates all integer triplets (a, b, c) such that
 * n >= c >= b >= a >= 0 and a ^ 2 + b ^ 2 == c ^ 2.
 * Triplets are generated in the ascending order by their first
 * element, then by the second element.
 *
 * @param n Non-negative integer.
 */
void generateTriplets(int n, Consumer <boost::tuple <int, int, int> > &consumer)
{
	const double sqrt2 = 1.41421356237309504880;
	const double n2 = n / sqrt2;
	boost::tuple <int, int, int> tuple;
	int &a = boost::tuples::get <0> (tuple);
	int &b = boost::tuples::get <1> (tuple);
	int &sqrtn = boost::tuples::get <2> (tuple);
	
	consumer.start();
	
	for (a = 0; a <= n2; ++a)
	{
		for (b = a; b <= std::sqrt(n * n - a * a); ++b)
		{
			if (isPerfectSquare(a * a + b * b, sqrtn))
			{
				consumer.feed(tuple);
			}
		}
	}
	
	consumer.finish();
}


}


#endif
