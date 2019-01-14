
#ifndef EUGENEJONAS__CPP_STUFF__ARITHM__ARITHM_FUNCTIONS_H
#define EUGENEJONAS__CPP_STUFF__ARITHM__ARITHM_FUNCTIONS_H


#include <eugenejonas/cpp_stuff/arithm/big_int.h>
#include <eugenejonas/cpp_stuff/arithm/div_mod.h>

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>


namespace eugenejonas::cpp_stuff
{


/**
 * Returns a ^ b mod m. mod operation works the same way
 * as function "myMod".
 *
 * @param a The base (can be negative).
 * @param b The exponent, b >= 0.
 * @param m The modulus, m != 0.
 */
BigInt modExp(BigInt const &a, BigInt const &b, BigInt const &m)
{
	assert(m != 0 && b >= 0);

	BigInt exp = b;
	BigInt res = BigInt(1) % m;		// "% m" is needed to handle case when b == 0 and m == +-1
	BigInt c = a % m;

	while (exp != 0)
	{
		if (exp % 2 != 0)
		{
			res = (c * res) % m;
		}
		c = (c * c) % m;
		exp /= 2;
	}
	
	return res;
}

/**
 * This function rounds real number to the nearest integer.
 * If fractional part is exactly 0.5, rounding half away
 * from zero is applied.
 * 
 * @return The rounded value: myRound(8.5) == 9, myRound(-8.5) == -9,
 *		myRound(8.2) == 8, myRound(8.7) == 9, myRound(-8.6) == -9,
 *		myRound(-8.2) == -8.
 */
int myRound(double dbl)
{
	if (dbl >= 0)
	{
		return (int) (dbl + 0.5);
	}
	else
	{
		return (int) (dbl - 0.5);
	}
}

/**
 * @param rad__angle Angle in radians.
 * @param eps Precision.
 */
double calculateCos(double rad__angle, double eps)
{
	assert(eps > 0);

	// cos(x) == 1 - (x ^ 2) / 2! + ... + (-1) ^ n * x ^ (2 * n) / (2 * n)! + ...

	double mod = myFloatMod(rad__angle, 2 * M_PI);
	double sum = 1;
	double d = 1;
	int n = 0;
	
	do
	{
		d = -d * mod / (2 * n + 1) * mod / (2 * n + 2);
		n++;
		sum += d;
	}
	while (std::fabs(d) >= eps);
	
	return sum;
}
double calculateSin(double rad__angle, double eps)
{
	assert(eps > 0);

	// sin(x) == x - (x ^ 3) / 3! + ... + (-1) ^ n * x ^ (2 * n + 1) / (2 * n + 1)! + ...

	double mod = myFloatMod(rad__angle, 2 * M_PI);
	double sum = mod;
	double d = mod;
	int n = 1;
	
	do
	{
		d = -d * mod / (2 * n) * mod / (2 * n + 1);
		n++;
		sum += d;
	}
	while (std::fabs(d) >= eps);
	
	return sum;
}

/**
 * Returns number of primes in interval [a; b].
 */
int countPrimes(int a, int b)
{
	if (a < 2)
	{
		a = 2;
	}
	
	if (a > b)
	{
		return 0;
	}
	
	int res = b - a + 1;
	std::vector <bool> v(b - a + 1, true);
	const int t = (int) std::sqrt(b);
	
	for (int i = 2; i <= t; ++i)
	{
		int j = a / i;
		if (j < 2)
		{
			j = 2;
		}

		// exclude all multiples of i in the interval [a; b]: 2 * i, 3 * i, ...
		for ( ; j <= b / i; ++j)
		{
			assert(i * j <= b);
			if (i * j >= a && v[i * j - a])
			{
				--res;
				v[i * j - a] = false;
			}
		}
	}
	
	return res;
}

/**
 * These functions check if the number is square of a natural number.
 * The one-argument version simply returns true or false, the two-argument
 * version also returns the value of the square root.
 *
 * @param n The number to check, n >= 0.
 * @param sqrtn Will hold the value of the square root of n
 *		(only if the function returns true).
 */
bool isPerfectSquare(int n, int &sqrtn)
{
	assert(n >= 0);
	sqrtn = myRound(std::sqrt(n));
	int f = sqrtn * sqrtn;
	return f == n;
}
bool isPerfectSquare(int n)
{
	int sqrtn;
	return isPerfectSquare(n, sqrtn);
}

/**
 * Calculates length of the representation of a non-negative integer in the given numeral system.
 * 
 * @param base Base of the numeral system, base > 1.
 * @return Number of digits in the representation (number 0 has length 1).
 */
int getIntLength(int n, int base)
{
	assert(base > 1);
	assert(n >= 0);
	
	if (n == 0)
	{
		return 1;
	}
	
	int res = 0;
	
	while (n > 0)
	{
		res++;
		n /= base;
	}
	
	return res;
}

/**
 * Returns decimal representation of a non-negative integer.
 */
std::string intToString(int n)
{
	assert(n >= 0);
	
	if (n == 0)
	{
		return "0";
	}
	
	const int base = 10;
	std::string res;
	
	while (n > 0)
	{
		res.insert(res.begin(), (n % base) + '0');
		n /= base;
	}
	
	return res;
}


}


#endif
