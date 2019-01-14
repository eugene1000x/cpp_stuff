
#include <eugenejonas/cpp_stuff/arithm/big_int.h>
#include <eugenejonas/cpp_stuff/combinatorics/calculator.h>

#include <cxxtest/TestSuite.h>


namespace eugenejonas::cpp_stuff
{


/**
 * Expected results were calculated using http://markknowsnothing.com/cgi-bin/calculator.cgi.
 */
class UnitTest_Calculator_calculateFactorial: public CxxTest::TestSuite
{
	public: void test1()
	{
		TS_ASSERT_EQUALS(BigInt(1), Calculator::calculateFactorial(0));
	}
	
	public: void test2()
	{
		TS_ASSERT_EQUALS(BigInt(1), Calculator::calculateFactorial(1));
	}
	
	public: void test3()
	{
		TS_ASSERT_EQUALS(BigInt(2), Calculator::calculateFactorial(2));
	}
	
	public: void test4()
	{
		TS_ASSERT_EQUALS(BigInt(6), Calculator::calculateFactorial(3));
	}
	
	public: void test5()
	{
		TS_ASSERT_EQUALS(BigInt("1124000727777607680000"), Calculator::calculateFactorial(22));
	}
}

/**
 * Expected results were calculated using http://markknowsnothing.com/cgi-bin/calculator.cgi.
 */
class UnitTest_Calculator_calculateBinomialCoefficientX: public CxxTest::TestSuite
{
	public: void test1()
	{
		TS_ASSERT_EQUALS(BigInt(1), Calculator::calculateBinomialCoefficientPascalTriangle(0, 0));
		TS_ASSERT_EQUALS(BigInt(1), Calculator::calculateBinomialCoefficientIterative(0, 0));
	}
	
	public: void test2()
	{
		TS_ASSERT_EQUALS(BigInt(10), Calculator::calculateBinomialCoefficientPascalTriangle(5, 3));
		TS_ASSERT_EQUALS(BigInt(10), Calculator::calculateBinomialCoefficientIterative(5, 3));
	}
	
	public: void test3()
	{
		TS_ASSERT_EQUALS(BigInt(10), Calculator::calculateBinomialCoefficientPascalTriangle(5, 2));
		TS_ASSERT_EQUALS(BigInt(10), Calculator::calculateBinomialCoefficientIterative(5, 2));
	}
	
	public: void test4()
	{
		TS_ASSERT_EQUALS(BigInt(2598960), Calculator::calculateBinomialCoefficientPascalTriangle(52, 5));
		TS_ASSERT_EQUALS(BigInt(2598960), Calculator::calculateBinomialCoefficientIterative(52, 5));
	}
	
	public: void test5()
	{
		TS_ASSERT_EQUALS(BigInt(2), Calculator::calculateBinomialCoefficientPascalTriangle(2, 1));
		TS_ASSERT_EQUALS(BigInt(2), Calculator::calculateBinomialCoefficientIterative(2, 1));
	}
	
	public: void test6()
	{
		TS_ASSERT_EQUALS(BigInt(120), Calculator::calculateBinomialCoefficientPascalTriangle(10, 3));
		TS_ASSERT_EQUALS(BigInt(120), Calculator::calculateBinomialCoefficientIterative(10, 3));
	}
	
	public: void test7()
	{
		TS_ASSERT_EQUALS(BigInt(184756), Calculator::calculateBinomialCoefficientPascalTriangle(20, 10));
		TS_ASSERT_EQUALS(BigInt(184756), Calculator::calculateBinomialCoefficientIterative(20, 10));
	}
	
	public: void test8()
	{
		TS_ASSERT_EQUALS(BigInt(646646), Calculator::calculateBinomialCoefficientPascalTriangle(22, 12));
		TS_ASSERT_EQUALS(BigInt(646646), Calculator::calculateBinomialCoefficientIterative(22, 12));
	}
	
	public: void test9()
	{
		TS_ASSERT_EQUALS(BigInt(847660528), Calculator::calculateBinomialCoefficientPascalTriangle(40, 10));
		TS_ASSERT_EQUALS(BigInt(847660528), Calculator::calculateBinomialCoefficientIterative(40, 10));
	}
	
	public: void test10()
	{
		TS_ASSERT_EQUALS(BigInt(30421755), Calculator::calculateBinomialCoefficientPascalTriangle(28, 12));
		TS_ASSERT_EQUALS(BigInt(30421755), Calculator::calculateBinomialCoefficientIterative(28, 12));
	}
	
	public: void test11()
	{
		TS_ASSERT_EQUALS(BigInt(0), Calculator::calculateBinomialCoefficientPascalTriangle(0, 1));
		TS_ASSERT_EQUALS(BigInt(0), Calculator::calculateBinomialCoefficientIterative(0, 1));
	}
	
	public: void test12()
	{
		TS_ASSERT_EQUALS(BigInt(1), Calculator::calculateBinomialCoefficientPascalTriangle(1, 0));
		TS_ASSERT_EQUALS(BigInt(1), Calculator::calculateBinomialCoefficientIterative(1, 0));
	}
}

/**
 * Expected results were taken from http://en.wikipedia.org/wiki/Stirling_numbers_of_the_first_kind#Table_of_values.
 */
class UnitTest_Calculator_calculateUnsignedStirlingFirstKindNumber: public CxxTest::TestSuite
{
	public: void test1()
	{
		TS_ASSERT_EQUALS(BigInt(1), Calculator::calculateUnsignedStirlingFirstKindNumber(0, 0));
	}
	
	public: void test2()
	{
		TS_ASSERT_EQUALS(BigInt(35), Calculator::calculateUnsignedStirlingFirstKindNumber(5, 3));
	}
	
	public: void test3()
	{
		TS_ASSERT_EQUALS(BigInt(50), Calculator::calculateUnsignedStirlingFirstKindNumber(5, 2));
	}
	
	public: void test4()
	{
		TS_ASSERT_EQUALS(BigInt(175), Calculator::calculateUnsignedStirlingFirstKindNumber(7, 5));
	}
	
	public: void test5()
	{
		TS_ASSERT_EQUALS(BigInt(109584), Calculator::calculateUnsignedStirlingFirstKindNumber(9, 2));
	}
	
	public: void test6()
	{
		TS_ASSERT_EQUALS(BigInt(1960), Calculator::calculateUnsignedStirlingFirstKindNumber(8, 5));
	}
	
	public: void test7()
	{
		TS_ASSERT_EQUALS(BigInt(0), Calculator::calculateUnsignedStirlingFirstKindNumber(8, 0));
	}
	
	public: void test8()
	{
		TS_ASSERT_EQUALS(BigInt(0), Calculator::calculateUnsignedStirlingFirstKindNumber(0, 1));
	}
	
	public: void test9()
	{
		TS_ASSERT_EQUALS(BigInt(0), Calculator::calculateUnsignedStirlingFirstKindNumber(1, 0));
	}
}

/**
 * Expected results were taken from http://en.wikipedia.org/wiki/Fibonacci_number#List_of_Fibonacci_numbers.
 */
class UnitTest_Calculator_calculateFibonacciNumber: public CxxTest::TestSuite
{
	public: void test1()
	{
		TS_ASSERT_EQUALS(BigInt(0), Calculator::calculateFibonacciNumber(0));
	}
	
	public: void test2()
	{
		TS_ASSERT_EQUALS(BigInt(1), Calculator::calculateFibonacciNumber(1));
	}
	
	public: void test3()
	{
		TS_ASSERT_EQUALS(BigInt(1), Calculator::calculateFibonacciNumber(2));
	}
	
	public: void test4()
	{
		TS_ASSERT_EQUALS(BigInt(55), Calculator::calculateFibonacciNumber(10));
	}
	
	public: void test5()
	{
		TS_ASSERT_EQUALS(BigInt(987), Calculator::calculateFibonacciNumber(16));
	}
	
	public: void test6()
	{
		TS_ASSERT_EQUALS(BigInt(6765), Calculator::calculateFibonacciNumber(20));
	}
	
	public: void test7()
	{
		TS_ASSERT_EQUALS(BigInt(1), Calculator::calculateFibonacciNumber(-1));
	}
	
	public: void test8()
	{
		TS_ASSERT_EQUALS(BigInt(-1), Calculator::calculateFibonacciNumber(-2));
	}
	
	public: void test9()
	{
		TS_ASSERT_EQUALS(-Calculator::calculateFibonacciNumber(10), Calculator::calculateFibonacciNumber(-10));
	}
	
	public: void test10()
	{
		TS_ASSERT_EQUALS(Calculator::calculateFibonacciNumber(45), Calculator::calculateFibonacciNumber(-45));
	}
	
	public: void test11()
	{
		TS_ASSERT_EQUALS(-Calculator::calculateFibonacciNumber(46), Calculator::calculateFibonacciNumber(-46));
	}
}


}
