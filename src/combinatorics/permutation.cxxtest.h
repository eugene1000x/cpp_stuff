
#include <eugenejonas/cpp_stuff/combinatorics/permutation.h>
#include <eugenejonas/cpp_stuff/orderings.h>

#include <string>

#include <cxxtest/TestSuite.h>


namespace eugenejonas::cpp_stuff
{


using std::string;
using std::vector;


class UnitTest_Permutation_with_StrictTotalIntegerOrdering: public CxxTest::TestSuite
{
	public: void test1()
	{
		Permutation <int, StrictTotalIntegerOrdering> p1(2), p2(2);
		TS_ASSERT_EQUALS(p1, p2);
	}
	
	public: void test2()
	{
		Permutation <int, StrictTotalIntegerOrdering> p(3);
		TS_ASSERT(p == p);
	}
	
	public: void test3()
	{
		int a[] = {2, 4, 6, 5, 1, 3};
		int b[] = {5, 1, 6, 2, 4, 3};
		
		Permutation <int, StrictTotalIntegerOrdering> p = vector <int> (a, a + sizeof(a) / sizeof(a[0]));
		Permutation <int, StrictTotalIntegerOrdering> p2 = vector <int> (b, b + sizeof(b) / sizeof(b[0]));
		Permutation <int, StrictTotalIntegerOrdering> inverse = p.getInverse();
		
		TS_ASSERT_EQUALS(p2, inverse);
	}
	
	public: void test4()
	{
		int a[] = {2, 4, 6, 5, 1, 3};
		int b[] = {5, 1, 2, 4, 6, 3};
		
		Permutation <int, StrictTotalIntegerOrdering> p = vector <int> (a, a + sizeof(a) / sizeof(a[0]));
		Permutation <int, StrictTotalIntegerOrdering> expected = vector <int> (b, b + sizeof(b) / sizeof(b[0]));
		
		TS_ASSERT_EQUALS(expected, p.getDecompositionInCycles());
	}
	
	public: void test5()
	{
		int a[] = {2, 4, 6, 5, 1, 3};
		
		Permutation <int, StrictTotalIntegerOrdering> p = vector <int> (a, a + sizeof(a) / sizeof(a[0]));
		Permutation <int, StrictTotalIntegerOrdering> copy(sizeof(a) / sizeof(a[0]));
		copy.reconstructFromDecompositionInCycles(p.getDecompositionInCycles());
		
		TS_ASSERT_EQUALS(p, copy);
	}
	
	public: void test6()
	{
		int a[] = {2, 4, 6, 5, 1, 3};
		Permutation <int, StrictTotalIntegerOrdering> p = vector <int> (a, a + sizeof(a) / sizeof(a[0]));
		int inversions = p.calculateInversionsDivideAndConquer();
		
		TS_ASSERT_EQUALS(8, inversions);
		
		inversions = p.calculateInversionsBruteForce();
		
		TS_ASSERT_EQUALS(8, inversions);
	}
	
	public: void test7()
	{
		int a[] = {2, 4, 6, 5, 1, 3};
		int b[] = {1, 5, 4, 3, 6, 2};
		int c[] = {5, 3, 2, 6, 1, 4};
		
		Permutation <int, StrictTotalIntegerOrdering> p = vector <int> (a, a + sizeof(a) / sizeof(a[0]));
		Permutation <int, StrictTotalIntegerOrdering> q = vector <int> (b, b + sizeof(b) / sizeof(b[0]));
		Permutation <int, StrictTotalIntegerOrdering> expected = vector <int> (c, c + sizeof(c) / sizeof(c[0]));
		
		TS_ASSERT_EQUALS(expected, q * p);
	}
	
	public: void test8()
	{
		int a[] = {2, 3, 4, 5, 6, 7, 1};
		int b[] = {7, 2, 3, 4, 5, 6, 1};
		
		vector <int> v(vector <int> (a, a + sizeof(a) / sizeof(a[0])));
		Permutation <int, StrictTotalIntegerOrdering> expected(vector <int> (b, b + sizeof(b) / sizeof(b[0])));
		Permutation <int, StrictTotalIntegerOrdering> p(sizeof(a) / sizeof(a[0]));
		p.reconstructFromDecompositionInCycles(v);
		
		TS_ASSERT_EQUALS(expected, p);
	}
	
	public: void test9()
	{
		int a[] = {2, 3, 1, 5, 4};
		Permutation <int, StrictTotalIntegerOrdering> p = vector <int> (a, a + sizeof(a) / sizeof(a[0]));
		int inversions = p.calculateInversionsDivideAndConquer();
		
		TS_ASSERT_EQUALS(3, inversions);
		
		inversions = p.calculateInversionsBruteForce();
		
		TS_ASSERT_EQUALS(3, inversions);
	}
	
	public: void test10()
	{
		int a[] = {11, 8, 5, 1, 7, 4, 10, 9, 6, 3, 2};
		Permutation <int, StrictTotalIntegerOrdering> p = vector <int> (a, a + sizeof(a) / sizeof(a[0]));
		
		int b[] = {11, 8, 5, 1, 7, 6, 2, 3, 4, 9, 10};
		Permutation <int, StrictTotalIntegerOrdering> expectedNext = vector <int> (b, b + sizeof(b) / sizeof(b[0]));
		
		p.next();
		
		TS_ASSERT_EQUALS(expectedNext, p);
	}
	
	public: void test11()
	{
		int a[] = {4, 3, 2, 1};
		Permutation <int, StrictTotalIntegerOrdering> p = vector <int> (a, a + sizeof(a) / sizeof(a[0]));
		bool doesNextPermutationExist = p.next();
		
		TS_ASSERT_EQUALS(false, doesNextPermutationExist);
	}
}

class UnitTest_Permutation_with_CustomStrictTotalOrdering: public CxxTest::TestSuite
{
	public: void test1()
	{
		string customOrderingArr[] = {"str1", "str2", "str3"};
		string permutationArr[] = {"str3", "str1", "str2"};
		string inversePermutationArr[] = {"str2", "str3", "str1"};

		CustomStrictTotalOrdering <string> compare(vector <string> (
				customOrderingArr,
				customOrderingArr + sizeof(customOrderingArr) / sizeof(customOrderingArr[0])
		));
		
		Permutation <string, CustomStrictTotalOrdering <string> > p(
				vector <string> (
						permutationArr,
						permutationArr + sizeof(permutationArr) / sizeof(permutationArr[0])
				),
				compare
		);
		
		Permutation <string, CustomStrictTotalOrdering <string> > expectedInverse(
				vector <string> (
						inversePermutationArr,
						inversePermutationArr + sizeof(inversePermutationArr) / sizeof(inversePermutationArr[0])
				),
				compare
		);
		
		Permutation <string, CustomStrictTotalOrdering <string> > actualInverse = p.getInverse();
		
		TS_ASSERT_EQUALS(expectedInverse, actualInverse);
	}
}


}
