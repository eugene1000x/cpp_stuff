
#include <eugenejonas/cpp_stuff/arithm/arithm_functions.h>

#include <cmath>

#include <cxxtest/TestSuite.h>


namespace eugenejonas::cpp_stuff
{


class UnitTest_modExp: public CxxTest::TestSuite
{
	public: void test1()
	{
		TS_ASSERT_EQUALS(0, modExp(0, 0, 1));
	}
	
	public: void test2()
	{
		TS_ASSERT_EQUALS(1, modExp(0, 0, 2));
	}
	
	public: void test3()
	{
		TS_ASSERT_EQUALS(0, modExp(0, 0, -1));
	}
	
	public: void test4()
	{
		TS_ASSERT_EQUALS(1, modExp(0, 0, -2));
	}
	
	public: void test5()
	{
		TS_ASSERT_EQUALS(1, modExp(1, 0, 2));
	}
	
	public: void test6()
	{
		TS_ASSERT_EQUALS(1, modExp(1, 1, 2));
	}
	
	public: void test7()
	{
		TS_ASSERT_EQUALS(1, modExp(1, 1, -2));
	}
	
	public: void test8()
	{
		TS_ASSERT_EQUALS(1, modExp(-2, 3, 3));
	}
}

class UnitTest_myRound: public CxxTest::TestSuite
{
	public: void test1()
	{
		int r = myRound(9.5);
		TS_ASSERT_EQUALS(10, r);
	}
	
	public: void test2()
	{
		int r = myRound(1.49);
		TS_ASSERT_EQUALS(1, r);
	}
	
	public: void test3()
	{
		int r = myRound(-2.3);
		TS_ASSERT_EQUALS(-2, r);
	}
	
	public: void test4()
	{
		int r = myRound(5.500001);
		TS_ASSERT_EQUALS(6, r);
	}
	
	public: void test5()
	{
		int r = myRound(-8.5);
		TS_ASSERT_EQUALS(-9, r);
	}
	
	public: void test6()
	{
		int r = myRound(-8.500001);
		TS_ASSERT_EQUALS(-9, r);
	}
	
	public: void test7()
	{
		int r = myRound(8.2);
		TS_ASSERT_EQUALS(8, r);
	}
	
	public: void test8()
	{
		int r = myRound(8.7);
		TS_ASSERT_EQUALS(9, r);
	}
	
	public: void test9()
	{
		int r = myRound(-8.6);
		TS_ASSERT_EQUALS(-9, r);
	}
	
	public: void test10()
	{
		int r = myRound(-8.2);
		TS_ASSERT_EQUALS(-8, r);
	}
}

class UnitTest_calculateCos: public CxxTest::TestSuite
{
	private: static const double EPS = 0.000000001;


	public: void test1()
	{
		double res = calculateCos(0, UnitTest_calculateCos::EPS);
		TS_ASSERT_DELTA(1, res, UnitTest_calculateCos::EPS);
	}
	
	public: void test2()
	{
		double res = calculateCos(M_PI, UnitTest_calculateCos::EPS);
		TS_ASSERT_DELTA(-1, res, UnitTest_calculateCos::EPS);
	}
	
	public: void test3()
	{
		double res = calculateCos(M_PI / 2, UnitTest_calculateCos::EPS);
		TS_ASSERT_DELTA(0, res, UnitTest_calculateCos::EPS);
	}
	
	public: void test4()
	{
		double res = calculateCos(-4, UnitTest_calculateCos::EPS);
		TS_ASSERT_DELTA(std::cos(-4), res, UnitTest_calculateCos::EPS);
	}
}

class UnitTest_calculateSin: public CxxTest::TestSuite
{
	private: static const double EPS = 0.000000001;


	public: void test1()
	{
		double res = calculateSin(0, UnitTest_calculateSin::EPS);
		TS_ASSERT_DELTA(0, res, UnitTest_calculateSin::EPS);
	}
	
	public: void test2()
	{
		double res = calculateSin(M_PI, UnitTest_calculateSin::EPS);
		TS_ASSERT_DELTA(0, res, UnitTest_calculateSin::EPS);
	}
	
	public: void test3()
	{
		double res = calculateSin(M_PI / 2, UnitTest_calculateSin::EPS);
		TS_ASSERT_DELTA(1, res, UnitTest_calculateSin::EPS);
	}
	
	public: void test4()
	{
		double res = calculateSin(-4, UnitTest_calculateSin::EPS);
		TS_ASSERT_DELTA(std::sin(-4), res, UnitTest_calculateSin::EPS);
	}
}

class UnitTest_countPrimes: public CxxTest::TestSuite
{
	/**
	 * The example test case from "Olimps":
	 * http://www.lio.lv/olimps/uzdevumi.php?show=2
	 */
	public: void test1()
	{
		TS_ASSERT_EQUALS(57, countPrimes(123, 456));
	}

	public: void test2()
	{
		TS_ASSERT_EQUALS(0, countPrimes(0, 0));
	}
	
	public: void test3()
	{
		TS_ASSERT_EQUALS(0, countPrimes(45, -2));
	}
}

class UnitTest_isPerfectSquare: public CxxTest::TestSuite
{
	public: void test1()
	{
		TS_ASSERT_EQUALS(false, isPerfectSquare(10));
	}
	
	public: void test2()
	{
		int sqrtn = 6;
		TS_ASSERT(isPerfectSquare(9));
		TS_ASSERT(isPerfectSquare(9, sqrtn));
		TS_ASSERT_EQUALS(3, sqrtn);
	}
	
	public: void test3()
	{
		TS_ASSERT_EQUALS(false, isPerfectSquare(160001));
	}
}

class UnitTest_getIntLength: public CxxTest::TestSuite
{
	public: void test1()
	{
		TS_ASSERT_EQUALS(1, getIntLength(0, 10));
	}
	
	public: void test2()
	{
		TS_ASSERT_EQUALS(1, getIntLength(1, 10));
	}
	
	public: void test3()
	{
		TS_ASSERT_EQUALS(5, getIntLength(18323, 10));
	}
	
	public: void test4()
	{
		TS_ASSERT_EQUALS(3, getIntLength(256, 16));
	}
	
	public: void test5()
	{
		TS_ASSERT_EQUALS(5, getIntLength(435435, 16));
	}
	
	public: void test6()
	{
		TS_ASSERT_EQUALS(7, getIntLength(435435, 8));
	}
}

class UnitTest_intToString: public CxxTest::TestSuite
{
	public: void test1()
	{
		TS_ASSERT_EQUALS("0", intToString(0));
	}
	
	public: void test2()
	{
		TS_ASSERT_EQUALS("1", intToString(1));
	}
	
	public: void test3()
	{
		TS_ASSERT_EQUALS("18323", intToString(18323));
	}
	
	public: void test4()
	{
		TS_ASSERT_EQUALS("256", intToString(256));
	}
	
	public: void test5()
	{
		TS_ASSERT_EQUALS("435435", intToString(435435));
	}
}


}
