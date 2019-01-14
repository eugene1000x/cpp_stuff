
#include <eugenejonas/cpp_stuff/arithm/gcd.h>

#include <cxxtest/TestSuite.h>


namespace eugenejonas::cpp_stuff
{


class UnitTest_calculateGcdX: public CxxTest::TestSuite
{
	public: void test1()
	{
		int m = 15;
		int n = 25;
		int expected = 5;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test2()
	{
		int m = 0;
		int n = 1;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test3()
	{
		int m = 0;
		int n = -1;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test4()
	{
		int m = -15;
		int n = -25;
		int expected = 5;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test5()
	{
		int m = 15;
		int n = -25;
		int expected = 5;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test6()
	{
		int m = -15;
		int n = 25;
		int expected = 5;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test7()
	{
		int m = 1;
		int n = 0;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test8()
	{
		int m = -1;
		int n = 0;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test9()
	{
		int m = 2147483647;
		int n = 2147483646;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test10()
	{
		int m = 999999999;
		int n = 999999998;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test11()
	{
		int m = 99999999;
		int n = 99999998;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test12()
	{
		int m = 9999999;
		int n = 9999998;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test13()
	{
		int m = 999999;
		int n = 999998;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test14()
	{
		int m = 381672;
		int n = 296875;
		int expected = 19;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test15()
	{
		int m = 644674545;
		int n = 47543947;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test16()
	{
		int m = 34958634;
		int n = 9941591;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test17()
	{
		int m = 35082241;
		int n = 6473766;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test18()
	{
		int m = 58795547;
		int n = 1061821;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test19()
	{
		int m = 338593;
		int n = 9109;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test20()
	{
		int m = 880367;
		int n = 9941;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test21()
	{
		int m = 67867;
		int n = 32359;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test22()
	{
		int m = 94546145;
		int n = 91529;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test23()
	{
		int m = 675327;
		int n = 402089;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test24()
	{
		int m = 14553053;
		int n = 2608351;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test25()
	{
		int m = 2147483647;
		int n = 2147483543;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test26()
	{
		int m = 765656767;
		int n = 2273273;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test27()
	{
		int m = 1246565765;
		int n = 1288733;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test28()
	{
		int m = 12379046;
		int n = 70549;
		int expected = 1;
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdBruteForceAlg(m, n));
		TS_ASSERT_EQUALS(expected, calculateGcdCommonDivisorAlg(m, n));
	}
	
	public: void test29()
	{
		BigInt m("34324324325443254343");
		BigInt n("9132049432681032473249327");
		BigInt expected("1");
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
	}
	
	public: void test30()
	{
		BigInt m("121371230054832908340173490269324705249328493284584325093284923850743250784325902740298535807930843506593608350784350327540");
		BigInt n("91320494326810324732493212031203102132407329014923784932879420240247247027502431090278492874902785098240275490278927");
		BigInt expected("1");
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
	}
	
	public: void test31()
	{
		BigInt m("13280109012891043809819832454435455436645479437859864365865363552312543243213345453445334541512004350104352035430");
		BigInt n("293849024024323400234001310238012930192839081243901824309128432034912301810298238471201301348902830234");
		BigInt expected("6");
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
	}
	
	public: void test32()
	{
		BigInt m("4347587543845344512104330043350433030786090032143657979432799213217890780553");
		BigInt n("73494360435905034659044384373295543241043543634324354345543");
		BigInt expected("3");
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
	}
	
	public: void test33()
	{
		BigInt m("211001097070244022481");
		BigInt n("12259903770424861960510530172516");
		BigInt expected(m);
		TS_ASSERT_EQUALS(expected, calculateGcdEuclidAlg(m, n));
	}
}


}
