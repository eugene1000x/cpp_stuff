
#include <eugenejonas/cpp_stuff/arithm/generators.h>
#include <eugenejonas/cpp_stuff/consumers.h>

#include <cmath>

#include <cxxtest/TestSuite.h>


namespace eugenejonas::cpp_stuff
{


/**
 * Test cases come from the paper
 * "Представление чисел в виде суммы двух квадратов"
 * (http://www.referat.ru/pub/item/17281),
 * section "КОЛИЧЕСТВО ПРЕДСТАВЛЕНИЙ ЧИСЛА В ВИДЕ СУММЫ ДВУХ КВАДРАТОВ".
 */
class UnitTest_generateSquareSumRepresentations: public CxxTest::TestSuite
{
	public: void test1()
	{
		Counter <boost::tuple <int, int> > counter;
		generateSquareSumRepresentations(65, counter);
		TS_ASSERT_EQUALS(2, counter.getCount());
	}
	
	public: void test2()
	{
		Counter <boost::tuple <int, int> > counter;
		generateSquareSumRepresentations(25, counter);
		TS_ASSERT_EQUALS(2, counter.getCount());
	}
	
	public: void test3()
	{
		Counter <boost::tuple <int, int> > counter;
		generateSquareSumRepresentations(5746, counter);
		TS_ASSERT_EQUALS(3, counter.getCount());
	}
}

class UnitTest_generateTriplets: public CxxTest::TestSuite
{
	/**
	 * 0 ^ 2 + 0 ^ 2 = 0 ^ 2
	 */
	public: void test1()
	{
		Counter <boost::tuple <int, int, int> > counter;
		generateTriplets(0, counter);
		TS_ASSERT_EQUALS(1, counter.getCount());
	}

	/**
	 * 0 ^ 2 + 0 ^ 2 = 0 ^ 2; 0 ^ 2 + 1 ^ 2 = 1 ^ 2
	 */
	public: void test2()
	{
		Counter <boost::tuple <int, int, int> > counter;
		generateTriplets(1, counter);
		TS_ASSERT_EQUALS(2, counter.getCount());
	}

	/**
	 * 0 ^ 2 + 0 ^ 2 = 0 ^ 2; 0 ^ 2 + 1 ^ 2 = 1 ^ 2; 0 ^ 2 + 2 ^ 2 = 2 ^ 2
	 */
	public: void test3()
	{
		Counter <boost::tuple <int, int, int> > counter;
		generateTriplets(2, counter);
		TS_ASSERT_EQUALS(3, counter.getCount());
	}
}


}
