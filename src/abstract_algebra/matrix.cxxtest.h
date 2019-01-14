
#include <eugenejonas/cpp_stuff/abstract_algebra/matrix.h>

#include <valarray>

#include <cxxtest/TestSuite.h>


namespace eugenejonas::cpp_stuff
{


class UnitTest_Matrix: public CxxTest::TestSuite
{
	public: void test1()
	{
		int arrA[] = {3, 2, -1, 2, 0, 10};
		int arrB[] = {4, -5, 0};
		int arrExpected[] = {2, 8};
		
		Matrix <2, 3, int> a(arrA);
		Matrix <3, 1, int> b(arrB);
		Matrix <2, 1, int> c = a * b;
		Matrix <2, 1, int> expected(arrExpected);
		
		TS_ASSERT_EQUALS(expected, c);
	}
	
	public: void test2()
	{
		int arrA[] = {4, -9, 8, 2, 0, 0, 5, 14, -4, 2, 0, -1};
		int arrB[] = {-8, 2, 0, 1};
		int arrExpected[] = {-48, 14, 35};
		
		Matrix <3, 4, int> a = arrA;
		
		std::valarray <int> v(arrB, sizeof(arrB) / sizeof(int));
		std::valarray <int> mult = a * v;
		std::valarray <int> expected(arrExpected, sizeof(arrExpected) / sizeof(int));
		
		bool doVectorsEqual = Matrix <1, 1, int> ::doVectorsEqual(mult, expected);
		
		TS_ASSERT_EQUALS(true, doVectorsEqual);
	}
}


}
