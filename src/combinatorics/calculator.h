
#ifndef EUGENEJONAS__CPP_STUFF__COMBINATORICS__CALCULATOR_H
#define EUGENEJONAS__CPP_STUFF__COMBINATORICS__CALCULATOR_H


#include <eugenejonas/cpp_stuff/arithm/big_int.h>

#include <algorithm>
#include <cassert>


namespace eugenejonas::cpp_stuff
{


class Calculator
{
	public: static BigInt calculateFactorial(int n)
	{
		assert(n >= 0);
		
		BigInt res(1);
		
		for (int i = 2; i <= n; i++)
		{
			res *= i;
		}
		
		return res;
	}

	/**
	 * Calculates binomial coefficient (number of unordered k-combinations from
	 * n elements, or C(n, k)) using Pascal's triangle.
	 */
	public: static BigInt calculateBinomialCoefficientPascalTriangle(int n, int k)
	{
		assert(n >= 0);
		assert(k >= 0);
		
		// the checks necessary for the algorithm to work
		if (k > n)
		{
			return 0;
		}
		if (k > n / 2)
		{
			k = n - k;
		}

		BigInt *arr = new BigInt[k + 1];
		arr[0] = 1;
		
		for (int i = 1; i < k; i++)
		{
			for (int j = i; j >= 1; j--)
			{
				arr[j] += arr[j - 1];
			}
		}
		
		for (int i = k; i <= n - k + 1; i++)
		{
			for (int j = k; j >= 1; j--)
			{
				arr[j] += arr[j - 1];
			}
		}
		
		for (int i = n - k + 2; i <= n; i++)
		{
			for (int j = k; j >= k - n + i; j--)
			{
				arr[j] += arr[j - 1];
			}
		}
		
		BigInt res = arr[k];
		delete[] arr;
		return res;
	}

	/**
	 * Calculates binomial coefficient (number of unordered k-combinations from
	 * n elements, or C(n, k)) using iterational method.
	 *
	 * @time O(k) divisions and multiplications.
	 */
	public: static BigInt calculateBinomialCoefficientIterative(int n, int k)
	{
		assert(n >= 0);
		assert(k >= 0);
		
		/*
		 * If n, k > 0, the following theorem holds:
		 * C(n, k) = C(n - 1, k - 1) * n / k,
		 * which means that k divides C(n - 1, k - 1) * n.
		 * So we can iteratively calculate binomial coefficient,
		 * dividing res by i with zero remainder:
		 *
		 * [[[1 * (n - k + 1) / 1] * (n - k + 2) / 2] * ... * (n - k + k) / k]
		 */

		if (k > n)
		{
			return 0;			// loop invariant wouldn't hold if (n - k) was negative
		}
		
		if (k > n / 2)
		{
			k = n - k;			// just an optimization - the algorithm would work if k <= n / 2 as well
		}
		
		BigInt res = 1;			// C(n - k, 0)

		for (int i = 1; i <= k; i++)
		{
			// loop invariant: res == C(n - k + i - 1, i - 1)
			
			// sequence of operations is important to make sure division is with zero remainder
			res *= n - k + i;
			res /= i;
		}

		return res;
	}

	private: static BigInt calculateBinomialCoefficientRecursive(int n, int k)
	{
		assert(n >= 0);
		assert(k >= 0);
		
		if (n < k)
		{
			return 0;
		}
		
		BigInt res = 0;
		Calculator::calculateBinomialCoefficientRecursiveImpl(n, k, res);
		
		return res;
	}

	private: static void calculateBinomialCoefficientRecursiveImpl(int n, int k, BigInt &res)
	{
		if (k > n / 2)
		{
			k = n - k;
		}
		
		if (k == 0)
		{
			res += 1;
			return;
		}

		Calculator::calculateBinomialCoefficientRecursiveImpl(n - 1, k, res);
		Calculator::calculateBinomialCoefficientRecursiveImpl(n - 1, k - 1, res);
	}

	/**
	 * Calculates unsigned Stirling number of the first kind (number of
	 * n-permutations with k cycles, or с(n, k)).
	 */
	public: static BigInt calculateUnsignedStirlingFirstKindNumber(int n, int k)
	{
		assert(n >= 0);
		assert(k >= 0);
		
		// These checks are necessary for the algorithm to work.
		// Need to ensure both numbers are strictly positive,
		// because the main calculation starts from с(1, 1).
		if (k == 0 && n == 0)
		{
			return 1;
		}
		else if (n == 0 || k == 0)
		{
			return 0;
		}

		// just an optimization - the algorithm would work if k > n or k == n as well
		if (k > n)
		{
			return 0;
		}
		else if (k == n)
		{
			return 1;
		}

		BigInt *arr = new BigInt[k + 1];
		arr[1] = 1;
		
		if ((n + 2) >> 1 >= k)
		{
			for (int i = 2; i < k; i++)
			{
				for (int j = i; j >= 1; j--)
				{
					arr[j] *= (i - 1);
					arr[j] += arr[j - 1];
				}
			}
			
			for (int i = k; i <= n - k + 1; i++)
			{
				for (int j = k; j >= 1; j--)
				{
					arr[j] *= (i - 1);
					arr[j] += arr[j - 1];
				}
			}
			
			for (int i = n - k + 2; i <= n; i++)
			{
				for (int j = k; j >= k - n + i; j--)
				{
					arr[j] *= (i - 1);
					arr[j] += arr[j - 1];
				}
			}
		}
		else
		{
			for (int i = 2; i <= n - k + 1; i++)
			{
				for (int j = i; j >= 1; j--)
				{
					arr[j] *= (i - 1);
					arr[j] += arr[j - 1];
				}
			}
			
			for (int i = n - k + 2; i < k; i++)
			{
				for (int j = i; j >= k - n + i; j--)
				{
					arr[j] *= (i - 1);
					arr[j] += arr[j - 1];
				}
			}
			
			for (int i = k; i <= n; i++)
			{
				for (int j = k; j >= k - n + i; j--)
				{
					arr[j] *= (i - 1);
					arr[j] += arr[j - 1];
				}
			}
		}
		
		BigInt res = arr[k];
		delete[] arr;
		return res;
	}

	/**
	 * @param n Index, can be negative.
	 */
	public: static BigInt calculateFibonacciNumber(int n)
	{
		if (n == 0)
		{
			return BigInt();
		}
		
		BigInt a, b(1);
		int absn = std::abs(n);
		
		for (int i = 1; i < absn; ++i)
		{
			BigInt tmp = b;
			b += a;
			a = tmp;
		}
		
		if (n > 0)
		{
			return b;
		}
		else if (n % 2 == 0)
		{
			return -b;
		}
		else
		{
			return b;
		}
	}
}


}


#endif
