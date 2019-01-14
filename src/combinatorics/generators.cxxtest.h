
#include <eugenejonas/cpp_stuff/combinatorics/generators.h>

#include <set>
#include <vector>

#include <cxxtest/TestSuite.h>


namespace eugenejonas::cpp_stuff
{


using std::set;
using std::vector;


class UnitTest_PermutationGenerator: public CxxTest::TestSuite
{
	public: void test1()
	{
		int arr[] = {};
		vector <Permutation> expectedVector;
		expectedVector.push_back(vector <int> (arr, arr + 0));
		set <Permutation> expectedSet(expectedVector.begin(), expectedVector.end());
		
		vector <Permutation> actualVector = Generator::permutations(0);
		set <Permutation> actualSet(actualVector.begin(), actualVector.end());
		
		TS_ASSERT_EQUALS(expectedSet, actualSet);
	}
	
	public: void test2()
	{
		int arr1[] = {1, 2, 3};
		int arr2[] = {1, 3, 2};
		int arr3[] = {3, 2, 1};
		int arr4[] = {3, 1, 2};
		int arr5[] = {2, 1, 3};
		int arr6[] = {2, 3, 1};
		
		vector <Permutation> expectedVector;
		
		expectedVector.push_back(vector <int> (arr1, arr1 + 3));
		expectedVector.push_back(vector <int> (arr2, arr2 + 3));
		expectedVector.push_back(vector <int> (arr3, arr3 + 3));
		expectedVector.push_back(vector <int> (arr4, arr4 + 3));
		expectedVector.push_back(vector <int> (arr5, arr5 + 3));
		expectedVector.push_back(vector <int> (arr6, arr6 + 3));
		
		set <Permutation> expectedSet(expectedVector.begin(), expectedVector.end());
		
		vector <Permutation> actualVector = Generator::permutations(3);
		set <Permutation> actualSet(actualVector.begin(), actualVector.end());
		
		TS_ASSERT_EQUALS(expectedSet, actualSet);
	}
}


}
