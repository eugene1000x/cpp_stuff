
#include <eugenejonas/cpp_stuff/arithm/big_int.h>

#include <cxxtest/TestSuite.h>


namespace eugenejonas::cpp_stuff
{


class UnitTest_BigInt: public CxxTest::TestSuite
{
	public: void test1()
	{
		BigInt b = 342;
		b = b * 2;
		TS_ASSERT_EQUALS(684, b);
	}
	
	public: void test2()
	{
		BigInt a(10), b("23");
		TS_ASSERT_EQUALS(33, a + b);
		TS_ASSERT_EQUALS(-13, a - b);
		TS_ASSERT_EQUALS(230, a * b);
		TS_ASSERT_EQUALS(33, a + 23);
		TS_ASSERT_EQUALS(-13, a - 23);
		TS_ASSERT_EQUALS(230, a * 23);
	}
	
	public: void test3()
	{
		BigInt a(10), b("-21"), c = 9;
		a += b;
		TS_ASSERT_EQUALS(-11, a);
		a *= c;
		TS_ASSERT_EQUALS(-99, a);
		a -= b;
		TS_ASSERT_EQUALS(-78, a);
	}
	
	public: void test4()
	{
		BigInt a(13), b("13");
		TS_ASSERT_EQUALS(a, b);
		a += 23;
		TS_ASSERT_EQUALS(36, a);
		a *= 2;
		TS_ASSERT_EQUALS(72, a);
		a -= 3;
		TS_ASSERT_EQUALS(69, a);
	}
}

class UnitTest_BigInt_cascaded_operators: public CxxTest::TestSuite
{
	public: void test1()
	{
		BigInt b;
		b *= b *= b *= b = 2;			// b *= (b *= (b *= (b = 2)));
		TS_ASSERT_EQUALS(256, b);
	}
	
	public: void test2()
	{
		BigInt a(-145);
		TS_ASSERT_EQUALS(-150, a -= 5);
	}
	
	public: void test3()
	{
		BigInt a = -15, b = 4;
		(a /= -6) /= -b;				// 3 / (-4)
		TS_ASSERT_EQUALS(0, a);
	}
	
	public: void test4()
	{
		BigInt a = -15, b = 2;
		(a /= -6) /= -b;				// 3 / (-2)
		TS_ASSERT_EQUALS(-1, a);
	}
}

/**
 * Test div and mod operators.
 * Test cases in this test suite are same as in
 * UnitTest_myDiv_myMod_myFloatDiv_myFloatMod_with_integer_arguments (a test for div_mod.h).
 *
 * 
 * Test cases 1-8 test mod and div operators with negative and
 * positive arguments a and b, where a does not divide b. Two test
 * case groups are:
 *
 * 1) |a| = 37, |b| = 14
 * 2) |a| = 5890, |b| = 6467
 *
 * All possible sign combinations are tested:
 *
 * a > 0, b > 0
 * a > 0, b < 0
 * a < 0, b > 0
 * a < 0, b < 0
 *
 * In test cases 1-4 |a| > |b|, in test cases 5-8 |a| < |b|.
 * 
 *
 * Test cases 9-12 test div and mod operators with negative and
 * positive arguments a and b, where a divides b.
 */
class UnitTest_BigInt_div_mod: public CxxTest::TestSuite
{
	public: void test1()
	{
		BigInt v = 37, expectedRemainder = 9, expectedQuotient = 2;
		BigInt a = v;
		long b = 14;

		TS_ASSERT_EQUALS(expectedQuotient, a / BigInt(b));
		TS_ASSERT_EQUALS(expectedRemainder, a % BigInt(b));
		TS_ASSERT_EQUALS(expectedQuotient, a / b);
		TS_ASSERT_EQUALS(expectedRemainder, a % b);

		a = v;
		a /= BigInt(b);
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= BigInt(b);
		TS_ASSERT_EQUALS(expectedRemainder, a);

		a = v;
		a /= b;
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= b;
		TS_ASSERT_EQUALS(expectedRemainder, a);
	}
	
	public: void test2()
	{
		BigInt v = 37, expectedRemainder = 9, expectedQuotient = -2;
		BigInt a = v;
		long b = -14;

		TS_ASSERT_EQUALS(expectedQuotient, a / BigInt(b));
		TS_ASSERT_EQUALS(expectedRemainder, a % BigInt(b));
		TS_ASSERT_EQUALS(expectedQuotient, a / b);
		TS_ASSERT_EQUALS(expectedRemainder, a % b);

		a = v;
		a /= BigInt(b);
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= BigInt(b);
		TS_ASSERT_EQUALS(expectedRemainder, a);

		a = v;
		a /= b;
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= b;
		TS_ASSERT_EQUALS(expectedRemainder, a);
	}
	
	public: void test3()
	{
		BigInt v = -37, expectedRemainder = 5, expectedQuotient = -3;
		BigInt a = v;
		long b = 14;

		TS_ASSERT_EQUALS(expectedQuotient, a / BigInt(b));
		TS_ASSERT_EQUALS(expectedRemainder, a % BigInt(b));
		TS_ASSERT_EQUALS(expectedQuotient, a / b);
		TS_ASSERT_EQUALS(expectedRemainder, a % b);

		a = v;
		a /= BigInt(b);
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= BigInt(b);
		TS_ASSERT_EQUALS(expectedRemainder, a);

		a = v;
		a /= b;
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= b;
		TS_ASSERT_EQUALS(expectedRemainder, a);
	}
	
	public: void test4()
	{
		BigInt v = -37, expectedRemainder = 5, expectedQuotient = 3;
		BigInt a = v;
		long b = -14;

		TS_ASSERT_EQUALS(expectedQuotient, a / BigInt(b));
		TS_ASSERT_EQUALS(expectedRemainder, a % BigInt(b));
		TS_ASSERT_EQUALS(expectedQuotient, a / b);
		TS_ASSERT_EQUALS(expectedRemainder, a % b);

		a = v;
		a /= BigInt(b);
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= BigInt(b);
		TS_ASSERT_EQUALS(expectedRemainder, a);

		a = v;
		a /= b;
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= b;
		TS_ASSERT_EQUALS(expectedRemainder, a);
	}
	
	public: void test5()
	{
		BigInt v = 5890, expectedRemainder = 5890, expectedQuotient = 0;
		BigInt a = v;
		long b = 6467;

		TS_ASSERT_EQUALS(expectedQuotient, a / BigInt(b));
		TS_ASSERT_EQUALS(expectedRemainder, a % BigInt(b));
		TS_ASSERT_EQUALS(expectedQuotient, a / b);
		TS_ASSERT_EQUALS(expectedRemainder, a % b);

		a = v;
		a /= BigInt(b);
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= BigInt(b);
		TS_ASSERT_EQUALS(expectedRemainder, a);

		a = v;
		a /= b;
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= b;
		TS_ASSERT_EQUALS(expectedRemainder, a);
	}
	
	public: void test6()
	{
		BigInt v = 5890, expectedRemainder = 5890, expectedQuotient = 0;
		BigInt a = v;
		long b = -6467;

		TS_ASSERT_EQUALS(expectedQuotient, a / BigInt(b));
		TS_ASSERT_EQUALS(expectedRemainder, a % BigInt(b));
		TS_ASSERT_EQUALS(expectedQuotient, a / b);
		TS_ASSERT_EQUALS(expectedRemainder, a % b);

		a = v;
		a /= BigInt(b);
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= BigInt(b);
		TS_ASSERT_EQUALS(expectedRemainder, a);

		a = v;
		a /= b;
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= b;
		TS_ASSERT_EQUALS(expectedRemainder, a);
	}
	
	public: void test7()
	{
		BigInt v = -5890, expectedRemainder = 577, expectedQuotient = -1;
		BigInt a = v;
		long b = 6467;

		TS_ASSERT_EQUALS(expectedQuotient, a / BigInt(b));
		TS_ASSERT_EQUALS(expectedRemainder, a % BigInt(b));
		TS_ASSERT_EQUALS(expectedQuotient, a / b);
		TS_ASSERT_EQUALS(expectedRemainder, a % b);

		a = v;
		a /= BigInt(b);
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= BigInt(b);
		TS_ASSERT_EQUALS(expectedRemainder, a);

		a = v;
		a /= b;
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= b;
		TS_ASSERT_EQUALS(expectedRemainder, a);
	}
	
	public: void test8()
	{
		BigInt v = -5890, expectedRemainder = 577, expectedQuotient = 1;
		BigInt a = v;
		long b = -6467;

		TS_ASSERT_EQUALS(expectedQuotient, a / BigInt(b));
		TS_ASSERT_EQUALS(expectedRemainder, a % BigInt(b));
		TS_ASSERT_EQUALS(expectedQuotient, a / b);
		TS_ASSERT_EQUALS(expectedRemainder, a % b);

		a = v;
		a /= BigInt(b);
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= BigInt(b);
		TS_ASSERT_EQUALS(expectedRemainder, a);

		a = v;
		a /= b;
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= b;
		TS_ASSERT_EQUALS(expectedRemainder, a);
	}
	
	public: void test9()
	{
		BigInt v = 120, expectedRemainder = 0, expectedQuotient = 15;
		BigInt a = v;
		long b = 8;

		TS_ASSERT_EQUALS(expectedQuotient, a / BigInt(b));
		TS_ASSERT_EQUALS(expectedRemainder, a % BigInt(b));
		TS_ASSERT_EQUALS(expectedQuotient, a / b);
		TS_ASSERT_EQUALS(expectedRemainder, a % b);

		a = v;
		a /= BigInt(b);
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= BigInt(b);
		TS_ASSERT_EQUALS(expectedRemainder, a);

		a = v;
		a /= b;
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= b;
		TS_ASSERT_EQUALS(expectedRemainder, a);
	}
	
	public: void test10()
	{
		BigInt v = 120, expectedRemainder = 0, expectedQuotient = -15;
		BigInt a = v;
		long b = -8;

		TS_ASSERT_EQUALS(expectedQuotient, a / BigInt(b));
		TS_ASSERT_EQUALS(expectedRemainder, a % BigInt(b));
		TS_ASSERT_EQUALS(expectedQuotient, a / b);
		TS_ASSERT_EQUALS(expectedRemainder, a % b);

		a = v;
		a /= BigInt(b);
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= BigInt(b);
		TS_ASSERT_EQUALS(expectedRemainder, a);

		a = v;
		a /= b;
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= b;
		TS_ASSERT_EQUALS(expectedRemainder, a);
	}
	
	public: void test11()
	{
		BigInt v = -120, expectedRemainder = 0, expectedQuotient = -15;
		BigInt a = v;
		long b = 8;

		TS_ASSERT_EQUALS(expectedQuotient, a / BigInt(b));
		TS_ASSERT_EQUALS(expectedRemainder, a % BigInt(b));
		TS_ASSERT_EQUALS(expectedQuotient, a / b);
		TS_ASSERT_EQUALS(expectedRemainder, a % b);

		a = v;
		a /= BigInt(b);
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= BigInt(b);
		TS_ASSERT_EQUALS(expectedRemainder, a);

		a = v;
		a /= b;
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= b;
		TS_ASSERT_EQUALS(expectedRemainder, a);
	}
	
	public: void test12()
	{
		BigInt v = -120, expectedRemainder = 0, expectedQuotient = 15;
		BigInt a = v;
		long b = -8;

		TS_ASSERT_EQUALS(expectedQuotient, a / BigInt(b));
		TS_ASSERT_EQUALS(expectedRemainder, a % BigInt(b));
		TS_ASSERT_EQUALS(expectedQuotient, a / b);
		TS_ASSERT_EQUALS(expectedRemainder, a % b);

		a = v;
		a /= BigInt(b);
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= BigInt(b);
		TS_ASSERT_EQUALS(expectedRemainder, a);

		a = v;
		a /= b;
		TS_ASSERT_EQUALS(expectedQuotient, a);

		a = v;
		a %= b;
		TS_ASSERT_EQUALS(expectedRemainder, a);
	}
}


}
