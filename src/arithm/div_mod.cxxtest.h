
#include <eugenejonas/cpp_stuff/arithm/div_mod.h>

#include <cxxtest/TestSuite.h>


namespace eugenejonas::cpp_stuff
{


/**
 * Test cases in this test suite are same as in UnitTest_BigInt_div_mod.
 */
class UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments: public CxxTest::TestSuite
{
	private: static const double EPS = 0.000000001;
	
	
	public: void test1()
	{
		int n = 37, m = 14, expectedRemainder = 9, expectedQuotient = 2;
		TS_ASSERT_EQUALS(expectedRemainder, myMod(n, m));
		TS_ASSERT_EQUALS(expectedQuotient, myDiv(n, m));
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test2()
	{
		int n = 37, m = -14, expectedRemainder = 9, expectedQuotient = -2;
		TS_ASSERT_EQUALS(expectedRemainder, myMod(n, m));
		TS_ASSERT_EQUALS(expectedQuotient, myDiv(n, m));
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test3()
	{
		int n = -37, m = 14, expectedRemainder = 5, expectedQuotient = -3;
		TS_ASSERT_EQUALS(expectedRemainder, myMod(n, m));
		TS_ASSERT_EQUALS(expectedQuotient, myDiv(n, m));
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test4()
	{
		int n = -37, m = -14, expectedRemainder = 5, expectedQuotient = 3;
		TS_ASSERT_EQUALS(expectedRemainder, myMod(n, m));
		TS_ASSERT_EQUALS(expectedQuotient, myDiv(n, m));
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test5()
	{
		int n = 5890, m = 6467, expectedRemainder = 5890, expectedQuotient = 0;
		TS_ASSERT_EQUALS(expectedRemainder, myMod(n, m));
		TS_ASSERT_EQUALS(expectedQuotient, myDiv(n, m));
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test6()
	{
		int n = 5890, m = -6467, expectedRemainder = 5890, expectedQuotient = 0;
		TS_ASSERT_EQUALS(expectedRemainder, myMod(n, m));
		TS_ASSERT_EQUALS(expectedQuotient, myDiv(n, m));
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test7()
	{
		int n = -5890, m = 6467, expectedRemainder = 577, expectedQuotient = -1;
		TS_ASSERT_EQUALS(expectedRemainder, myMod(n, m));
		TS_ASSERT_EQUALS(expectedQuotient, myDiv(n, m));
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test8()
	{
		int n = -5890, m = -6467, expectedRemainder = 577, expectedQuotient = 1;
		TS_ASSERT_EQUALS(expectedRemainder, myMod(n, m));
		TS_ASSERT_EQUALS(expectedQuotient, myDiv(n, m));
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test9()
	{
		int n = 120, m = 8, expectedRemainder = 0, expectedQuotient = 15;
		TS_ASSERT_EQUALS(expectedRemainder, myMod(n, m));
		TS_ASSERT_EQUALS(expectedQuotient, myDiv(n, m));
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test10()
	{
		int n = 120, m = -8, expectedRemainder = 0, expectedQuotient = -15;
		TS_ASSERT_EQUALS(expectedRemainder, myMod(n, m));
		TS_ASSERT_EQUALS(expectedQuotient, myDiv(n, m));
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test11()
	{
		int n = -120, m = 8, expectedRemainder = 0, expectedQuotient = -15;
		TS_ASSERT_EQUALS(expectedRemainder, myMod(n, m));
		TS_ASSERT_EQUALS(expectedQuotient, myDiv(n, m));
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test12()
	{
		int n = -120, m = -8, expectedRemainder = 0, expectedQuotient = 15;
		TS_ASSERT_EQUALS(expectedRemainder, myMod(n, m));
		TS_ASSERT_EQUALS(expectedQuotient, myDiv(n, m));
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
}

/**
 * Test functions "myFloatMod" and "myFloatDiv".
 *
 * Test cases in this test suite are made in a similar way
 * as in UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments above. They include tests
 * for every possible combination of operand signs.
 *
 * Test cases 1-8 are divided into two groups:
 *
 * 1) |n| = 7.2, |m| = 3
 * 2) |n| = 34.23435, |m| = 59.77896
 *
 * In test cases 9-12 n divides m.
 */
class UnitTest_myFloatDiv_myFloatMod: public CxxTest::TestSuite
{
	private: static const double EPS = 0.000000001;


	public: void test1()
	{
		double n = 7.2, m = 3, expectedRemainder = 1.2;
		int expectedQuotient = 2;
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myFloatDiv_myFloatMod::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test2()
	{
		double n = 7.2, m = -3, expectedRemainder = 1.2;
		int expectedQuotient = -2;
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myFloatDiv_myFloatMod::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test3()
	{
		double n = -7.2, m = 3, expectedRemainder = 1.8;
		int expectedQuotient = -3;
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myFloatDiv_myFloatMod::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test4()
	{
		double n = -7.2, m = -3, expectedRemainder = 1.8;
		int expectedQuotient = 3;
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myFloatDiv_myFloatMod::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test5()
	{
		double n = 34.23435, m = 59.77896, expectedRemainder = 34.23435;
		int expectedQuotient = 0;
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myFloatDiv_myFloatMod::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test6()
	{
		double n = 34.23435, m = -59.77896, expectedRemainder = 34.23435;
		int expectedQuotient = 0;
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myFloatDiv_myFloatMod::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test7()
	{
		double n = -34.23435, m = 59.77896, expectedRemainder = 25.54461;
		int expectedQuotient = -1;
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myFloatDiv_myFloatMod::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test8()
	{
		double n = -34.23435, m = -59.77896, expectedRemainder = 25.54461;
		int expectedQuotient = 1;
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myFloatDiv_myFloatMod::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test9()
	{
		double n = 106.736, m = 26.684, expectedRemainder = 0;
		int expectedQuotient = 4;
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myFloatDiv_myFloatMod::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test10()
	{
		double n = 106.736, m = -26.684, expectedRemainder = 0;
		int expectedQuotient = -4;
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myFloatDiv_myFloatMod::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test11()
	{
		double n = -106.736, m = 26.684, expectedRemainder = 0;
		int expectedQuotient = -4;
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myFloatDiv_myFloatMod::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
	
	public: void test12()
	{
		double n = -106.736, m = -26.684, expectedRemainder = 0;
		int expectedQuotient = 4;
		TS_ASSERT_DELTA(expectedRemainder, myFloatMod(n, m), UnitTest_myFloatDiv_myFloatMod::EPS);
		TS_ASSERT_EQUALS(expectedQuotient, myFloatDiv(n, m));
	}
}


}
