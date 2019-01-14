
#ifndef EUGENEJONAS__CPP_STUFF__ARITHM__GCD_H
#define EUGENEJONAS__CPP_STUFF__ARITHM__GCD_H


#include <eugenejonas/cpp_stuff/arithm/big_int.h>
#include <eugenejonas/cpp_stuff/arithm/div_mod.h>

#include <algorithm>
#include <cassert>
#include <cstdlib>


namespace eugenejonas::cpp_stuff
{


/**
 * These functions calculate the Greatest Common Divisor of two integers
 * using different algorithms. Function calculateGcdEuclidAlg takes two BigInt
 * objects, because its algorithm is suitable for long numbers. The other two
 * algoritms work only with small numbers.
 *
 * @pre m != 0 || n != 0 (GCD(0, 0) is undefined since any integer except 0 divides 0)
 * @return Greatest common divisor of m and n.
 */
BigInt calculateGcdEuclidAlg(BigInt const &m, BigInt const &n)
{
	assert(m != 0 || n != 0);
	
	BigInt m2 = m, n2 = n;
	
	while (n2 != 0)
	{
		BigInt r = m2 % n2;
		m2 = n2;
		n2 = r;
	}
	return m2.abs();
}
int calculateGcdBruteForceAlg(int m, int n)
{
	assert(m != 0 || n != 0);
	
	m = std::abs(m);
	n = std::abs(n);
	
	if (m < n)
	{
		std::swap(m, n);
	}
	
	if (n == 0)
	{
		return m;
	}
	
	for (int i = n; true; i--)
	{
		if (myMod(m, i) == 0 && myMod(n, i) == 0)
		{
			return i;
		}
	}
	assert(false);
}
int calculateGcdCommonDivisorAlg(int m, int n)
{
	assert(m != 0 || n != 0);
	
	m = std::abs(m);
	n = std::abs(n);
	
	if (m == 0)
	{
		return n;
	}
	
	if (n == 0)
	{
		return m;
	}
	
	int d = 2, res = 1;
	
	if (m < n)
	{
		std::swap(m, n);
	}
	
	while (n > 1)
	{
		if (n % d == 0)
		{
			n /= d;
			if (m % d == 0)
			{
				m /= d;
				res *= d;
			}
			// if d divides n, check d again
		}
		else
		{
			d++;
		}
	}
	return res;
}


}


#endif
