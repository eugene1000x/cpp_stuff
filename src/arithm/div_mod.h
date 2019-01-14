
#ifndef EUGENEJONAS__CPP_STUFF__ARITHM__DIV_MOD_H
#define EUGENEJONAS__CPP_STUFF__ARITHM__DIV_MOD_H


#include <eugenejonas/cpp_stuff/arithm/arithm_functions.h>

#include <cassert>
#include <cmath>
#include <cstdlib>


namespace eugenejonas::cpp_stuff
{


/**
 * Functions that implement div and mod operations on integers and real numbers.
 * 
 * Problems with standard C++ operators "%" and "/" is that their behaviour
 * is implementation-defined if any of the operands is negative.
 * Function "std::fmod" may produce negative remainder.
 * Behaviour of cpp_stuff "my[Float]Mod" and "my[Float]Div" functions is well-defined and "my[Float]Mod"
 * always produces non-negative remainder (and "my[Float]Div" is consistent with that).
 * 
 * Functions "myMod" and "myFloatMod" return non-negative remainder r of n / m, such
 * that |m| > r >= 0. Functions "myDiv" and "myFloatDiv" return quotient q of n / m,
 * which is obtained by rounding the value of n down (towards -infinity) to the
 * nearest multiple of m and then dividing it by m.
 * 
 * The functions are consistent, meaning that:
 * my[Float]Div(n, m) * m + my[Float]Mod(n, m) == n
 * 
 * "myMod" and "myDiv" functions behave in the same way as "myFloatMod" and "myFloatDiv"
 * functions on whole numbers: for any two integers n and m, results of
 * myFloatMod(n, m) and myMod(n, m) are the same and results of myFloatDiv(n, m) and
 * myDiv(n, m) are the same.
 * 
 * 
 * Examples:
 * 
 * myMod(12, 5) == 2
 * myMod(12, -5) == 2
 * myMod(-12, 5) == 3
 * myMod(-12, -5) == 3
 * 
 * myDiv(12, 5) == 2
 * myDiv(12, -5) == -2
 * myDiv(-12, 5) == -3
 * myDiv(-12, -5) == 3
 * 
 * myFloatMod(7.2, 3.0) == 1.2
 * myFloatMod(7.2, -3.0) == 1.2
 * myFloatMod(-7.2, 3.0) == 1.8
 * myFloatMod(-7.2, -3.0) == 1.8
 * 
 * myFloatDiv(7.2, 3.0) == 2
 * myFloatDiv(7.2, -3.0) == -2
 * myFloatDiv(-7.2, 3.0) == -3
 * myFloatDiv(-7.2, -3.0) == 3
 * 
 * 
 * @param n Dividend.
 * @param m Divisor, m != 0.
 */
int myMod(int n, int m)
{
	assert(m != 0);
	m = std::abs(m);
	
	if (n >= 0)
	{
		return n % m;
	}
	else if ((-n) % m == 0)
	{
		return 0;
	}
	else
	{
		return m - ((-n) % m);
	}
}
int myDiv(int n, int m)
{
	assert(m != 0);
	
	if (n < 0 && m < 0)
	{
		if ((-n) % (-m) == 0)
		{
			return (-n) / (-m);
		}
		else
		{
			return (-n) / (-m) + 1;
		}
	}
	else if (n < 0)
	{
		if ((-n) % (m) == 0)
		{
			return -((-n) / m);
		}
		else
		{
			return -((-n) / m) - 1;
		}
	}
	else if (m < 0)
	{
		return -((n) / (-m));
	}
	else
	{
		return n / m;
	}
}
double myFloatMod(double n, double m)
{
	assert(m != 0);
	m = std::fabs(m);
	
	if (n >= 0)
	{
		return std::fmod(n, m);
	}
	else if (std::fmod(-n, m) == 0)
	{
		return 0;
	}
	else
	{
		return m - std::fmod(-n, m);
	}
}
int myFloatDiv(double n, double m)
{
	assert(m != 0);
	return myRound((n - myFloatMod(n, m)) / m);
	
	//double k = std::floor(n / m);
	//return myRound(k);
}


}


#endif
