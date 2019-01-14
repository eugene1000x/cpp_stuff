
#include <eugenejonas/cpp_stuff/orderings.h>
#include <eugenejonas/cpp_stuff/sort.h>

#include <algorithm>
#include <cassert>
#include <iterator>
#include <string>

#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
#include <concepts>
#else
#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#endif

#include <cxxtest/TestSuite.h>


namespace eugenejonas::cpp_stuff
{


using std::string;


/**
 * Class with static helper methods.
 */
template <typename TPL_SortTestUtils_Iterator, typename TPL_SortTestUtils_StrictWeakOrdering> class SortTestUtils
{
	typedef typename iterator_traits <TPL_SortTestUtils_Iterator> ::pointer pointer;
	typedef typename iterator_traits <TPL_SortTestUtils_Iterator> ::value_type value_type;


	BOOST_CONCEPT_ASSERT((boost::RandomAccessIterator <TPL_SortTestUtils_Iterator>));
	BOOST_CONCEPT_ASSERT((StrictWeakOrdering <TPL_SortTestUtils_StrictWeakOrdering, value_type>));


	/**
	 * This method checks that sorting algorithms are stable.
	 * Stable sorting algorithms must not change relative order of equivalent elements.
	 */
	public: static void checkAsStable(
			TPL_SortTestUtils_Iterator sourceFirst,
			TPL_SortTestUtils_Iterator sourceLast,
			TPL_SortTestUtils_StrictWeakOrdering swoCompare
	)
	{
		std::size_t distance = sourceLast - sourceFirst;
		
		pointer sortedFirst = new value_type[distance];
		pointer sortedLast = sortedFirst + distance;
		
		Sorter <pointer, TPL_SortTestUtils_StrictWeakOrdering> *sorter =
				new Sorter <pointer, TPL_SortTestUtils_StrictWeakOrdering> (sortedFirst, sortedLast, swoCompare);


		std::copy(sourceFirst, sourceLast, sortedFirst);
		sorter->bubbleSort();
		TS_ASSERT(isStableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, swoCompare));

		std::copy(sourceFirst, sourceLast, sortedFirst);
		sorter->heapSort();
		TS_ASSERT(isStableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, swoCompare));

		std::copy(sourceFirst, sourceLast, sortedFirst);
		sorter->mergeSort();
		TS_ASSERT(isStableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, swoCompare));

		std::copy(sourceFirst, sourceLast, sortedFirst);
		sorter->quickSort();
		TS_ASSERT(isStableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, swoCompare));

		std::copy(sourceFirst, sourceLast, sortedFirst);
		sorter->selectionSort();
		TS_ASSERT(isStableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, swoCompare));


		delete sorter;
		delete[] sortedFirst;
	}

	/**
	 * This method checks sorting algorithms as unstable.
	 * Unstable sorting algorithms do not guarantee preserving
	 * relative order of equivalent elements.
	 */
	public: template <typename TPL_StrictTotalOrdering> static void checkAsUnstable(
			TPL_SortTestUtils_Iterator sourceFirst,
			TPL_SortTestUtils_Iterator sourceLast,
			TPL_SortTestUtils_StrictWeakOrdering swoCompare,
			TPL_StrictTotalOrdering stoCompare
	)
	{
		std::size_t distance = sourceLast - sourceFirst;
		
		pointer sortedFirst = new value_type[distance];
		pointer sortedLast = sortedFirst + distance;
		
		Sorter <pointer, TPL_SortTestUtils_StrictWeakOrdering> *sorter =
				new Sorter <pointer, TPL_SortTestUtils_StrictWeakOrdering> (sortedFirst, sortedLast, swoCompare);


		std::copy(sourceFirst, sourceLast, sortedFirst);
		sorter->bubbleSort();
		TS_ASSERT(isUnstableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, swoCompare, stoCompare));

		std::copy(sourceFirst, sourceLast, sortedFirst);
		sorter->heapSort();
		TS_ASSERT(isUnstableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, swoCompare, stoCompare));

		std::copy(sourceFirst, sourceLast, sortedFirst);
		sorter->mergeSort();
		TS_ASSERT(isUnstableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, swoCompare, stoCompare));

		std::copy(sourceFirst, sourceLast, sortedFirst);
		sorter->quickSort();
		TS_ASSERT(isUnstableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, swoCompare, stoCompare));

		std::copy(sourceFirst, sourceLast, sortedFirst);
		sorter->selectionSort();
		TS_ASSERT(isUnstableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, swoCompare, stoCompare));


		delete sorter;
		delete[] sortedFirst;
	}
}

/**
 * Note: this is total ordering.
 */
class UnitTest_isXSorted_with_integers_and_standard_less_than: public CxxTest::TestSuite
{
	public: void test1()
	{
		int *sourceFirst, *sourceLast, *sortedFirst, *sortedLast;
		int source[] = {18, 0, -4, 0};
		int sorted[] = {-4, 0, 0, 18};
		
		std::less <int> compare;
		std::size_t length = sizeof(source) / sizeof(source[0]);
		
		sourceFirst = source;
		sourceLast = source + length;
		sortedFirst = sorted;
		sortedLast = sorted + length;
		
		TS_ASSERT_EQUALS(false, isSorted(sourceFirst, sourceLast, compare));
		TS_ASSERT(isUnstableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compare, compare));
		TS_ASSERT(isStableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compare));
	}
	
	public: void test2()
	{
		int *sourceFirst, *sourceLast, *sortedFirst, *sortedLast;
		int source[] = {};
		int sorted[] = {};
		
		std::less <int> compare;
		std::size_t length = sizeof(source) / sizeof(source[0]);
		
		sourceFirst = source;
		sourceLast = source + length;
		sortedFirst = sorted;
		sortedLast = sorted + length;
		
		TS_ASSERT(isSorted(sourceFirst, sourceLast, compare));
		TS_ASSERT(isUnstableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compare, compare));
		TS_ASSERT(isStableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compare));
	}
}

/**
 * Note: this is weak, but not total ordering.
 */
class UnitTest_isXSorted_with_pointers_to_string_and_compareStrings: public CxxTest::TestSuite
{
	/**
	 * Test with array which does not contain equivalent non-equal elements.
	 */
	public: void test1()
	{
		string **sourceFirst, **sourceLast, **sortedFirst, **sortedLast;
		string a("abc"), b("def"), c("ghi");
		string *source[] = {&a, &b, &c, &a, &a, &c, &b};
		string *sorted[] = {&a, &a, &a, &b, &b, &c, &c};
		
		std::size_t length = sizeof(source) / sizeof(source[0]);
		
		sourceFirst = source;
		sourceLast = source + length;
		sortedFirst = sorted;
		sortedLast = sorted + length;
		
		TS_ASSERT_EQUALS(false, isSorted(sourceFirst, sourceLast, compareStrings));
		TS_ASSERT(isUnstableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compareStrings, std::less <string*> ()));
		TS_ASSERT(isStableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compareStrings));
	}

	public: void test2()
	{
		string **sourceFirst, **sourceLast;
		string a("abc"), b("def"), c("def");
		string *source[] = {&a, &b, &c, &a, &a, &c, &b};
		
		std::size_t length = sizeof(source) / sizeof(source[0]);
		
		sourceFirst = source;
		sourceLast = source + length;
		
		TS_ASSERT_EQUALS(false, isSorted(sourceFirst, sourceLast, compareStrings));
	}

	/**
	 * Test case where relative order of equivalent elements has not changed.
	 */
	public: void test3()
	{
		string **sourceFirst, **sourceLast, **sortedFirst, **sortedLast;
		string a("abc"), b("def"), c("def");
		string *source[] = {&a, &b, &c, &a, &a, &c, &b};
		string *sorted[] = {&a, &a, &a, &b, &c, &c, &b};
		
		std::size_t length = sizeof(source) / sizeof(source[0]);
		
		sourceFirst = source;
		sourceLast = source + length;
		sortedFirst = sorted;
		sortedLast = sorted + length;
		
		TS_ASSERT(isUnstableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compareStrings, std::less <string*> ()));
		TS_ASSERT(isStableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compareStrings));
	}

	/**
	 * Test case where relative order of equivalent elements has changed.
	 */
	public: void test4()
	{
		string **sourceFirst, **sourceLast, **sortedFirst, **sortedLast;
		string a("abc"), b("def"), c("def");
		string *source[] = {&a, &b, &c, &a, &a, &c, &b};
		string *sorted[] = {&a, &a, &a, &b, &c, &b, &c};
		
		std::size_t length = sizeof(source) / sizeof(source[0]);
		
		sourceFirst = source;
		sourceLast = source + length;
		sortedFirst = sorted;
		sortedLast = sorted + length;
		
		TS_ASSERT(isSorted(sortedFirst, sortedLast, compareStrings));
		TS_ASSERT(isUnstableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compareStrings, std::less <string*> ()));
		TS_ASSERT_EQUALS(false, isStableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compareStrings));
	}
}

/**
 * Note: this is weak, but not total ordering.
 */
class UnitTest_isXSorted_with_unsigned_and_compareLastDigit: public CxxTest::TestSuite
{
	/**
	 * Test case where relative order of equivalent elements has not changed.
	 */
	public: void test1()
	{
		unsigned *sourceFirst, *sourceLast, *sortedFirst, *sortedLast;
		unsigned source[] = {2, 5, 12, 2, 3};
		unsigned sorted[] = {2, 12, 2, 3, 5};
		
		std::size_t length = sizeof(source) / sizeof(source[0]);
		
		sourceFirst = source;
		sourceLast = source + length;
		sortedFirst = sorted;
		sortedLast = sorted + length;
		
		TS_ASSERT_EQUALS(false, isSorted(sourceFirst, sourceLast, compareLastDigit));
		TS_ASSERT(isSorted(sortedFirst, sortedLast, compareLastDigit));
		TS_ASSERT(isUnstableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compareLastDigit, std::less <unsigned> ()));
		TS_ASSERT(isStableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compareLastDigit));
	}

	/**
	 * Test case where relative order of equivalent elements has changed.
	 */
	public: void test2()
	{
		unsigned *sourceFirst, *sourceLast, *sortedFirst, *sortedLast;
		unsigned source[] = {2, 5, 12, 2, 3};
		unsigned sorted[] = {2, 2, 12, 3, 5};
		
		std::size_t length = sizeof(source) / sizeof(source[0]);
		
		sourceFirst = source;
		sourceLast = source + length;
		sortedFirst = sorted;
		sortedLast = sorted + length;
		
		TS_ASSERT(isSorted(sortedFirst, sortedLast, compareLastDigit));
		TS_ASSERT(isUnstableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compareLastDigit, std::less <unsigned> ()));
		TS_ASSERT_EQUALS(false, isStableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compareLastDigit));
	}

	/**
	 * Test case where relative order of equivalent elements has changed.
	 */
	public: void test3()
	{
		unsigned *sourceFirst, *sourceLast, *sortedFirst, *sortedLast;
		unsigned source[] = {2, 5, 12, 2, 3};
		unsigned sorted[] = {12, 2, 2, 3, 5};
		
		std::size_t length = sizeof(source) / sizeof(source[0]);
		
		sourceFirst = source;
		sourceLast = source + length;
		sortedFirst = sorted;
		sortedLast = sorted + length;
		
		TS_ASSERT(isSorted(sortedFirst, sortedLast, compareLastDigit));
		TS_ASSERT(isUnstableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compareLastDigit, std::less <unsigned> ()));
		TS_ASSERT_EQUALS(false, isStableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compareLastDigit));
	}

	/**
	 * Test case where element in the array "sorted" was replaced with a different,
	 * but equivalent element.
	 */
	public: void test4()
	{
		unsigned *sourceFirst, *sourceLast, *sortedFirst, *sortedLast;
		unsigned source[] = {2, 5, 12, 2, 3};
		unsigned sorted[] = {2, 2, 2, 3, 5};
		
		std::size_t length = sizeof(source) / sizeof(source[0]);
		
		sourceFirst = source;
		sourceLast = source + length;
		sortedFirst = sorted;
		sortedLast = sorted + length;
		
		TS_ASSERT(isSorted(sortedFirst, sortedLast, compareLastDigit));
		TS_ASSERT_EQUALS(false, isUnstableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compareLastDigit, std::less <unsigned> ()));
		TS_ASSERT_EQUALS(false, isStableSorted(sortedFirst, sortedLast, sourceFirst, sourceLast, compareLastDigit));
	}
}

class UnitTest_Sorter_with_integers_and_standard_less_than: public CxxTest::TestSuite
{
	private: typedef SortTestUtils <int*, std::less <int> > Utils;


	private: int *sourceFirst, *sourceLast;
	private: std::less <int> compare;
	
	
	public: void test1()
	{
		int arr[] = {4, 7, -9, 1, 8, 12, 100, 15, 56, -29};
		this->sourceFirst = arr;
		this->sourceLast = arr + sizeof(arr) / sizeof(arr[0]);
		Utils::checkAsUnstable(this->sourceFirst, this->sourceLast, this->compare, this->compare);
	}
	
	public: void test2()
	{
		int arr[] = {};
		this->sourceFirst = arr;
		this->sourceLast = arr + sizeof(arr) / sizeof(arr[0]);
		Utils::checkAsUnstable(this->sourceFirst, this->sourceLast, this->compare, this->compare);
	}
	
	public: void test3()
	{
		int arr[] = {1};
		this->sourceFirst = arr;
		this->sourceLast = arr + sizeof(arr) / sizeof(arr[0]);
		Utils::checkAsUnstable(this->sourceFirst, this->sourceLast, this->compare, this->compare);
	}
	
	public: void test4()
	{
		int arr[] = {-323, 123};
		this->sourceFirst = arr;
		this->sourceLast = arr + sizeof(arr) / sizeof(arr[0]);
		Utils::checkAsUnstable(this->sourceFirst, this->sourceLast, this->compare, this->compare);
	}
	
	public: void test5()
	{
		int arr[] = {0, 0, -5};
		this->sourceFirst = arr;
		this->sourceLast = arr + sizeof(arr) / sizeof(arr[0]);
		Utils::checkAsUnstable(this->sourceFirst, this->sourceLast, this->compare, this->compare);
	}
	
	public: void test6()
	{
		int arr[] = {243, 243};
		this->sourceFirst = arr;
		this->sourceLast = arr + sizeof(arr) / sizeof(arr[0]);
		Utils::checkAsUnstable(this->sourceFirst, this->sourceLast, this->compare, this->compare);
	}
	
	public: void test7()
	{
		int arr[] = {-1232, -2343};
		this->sourceFirst = arr;
		this->sourceLast = arr + sizeof(arr) / sizeof(arr[0]);
		Utils::checkAsUnstable(this->sourceFirst, this->sourceLast, this->compare, this->compare);
	}
}

class UnitTest_Sorter_with_strings_and_pointers_to_strings: public CxxTest::TestSuite
{
	/**
	 * Test with empty array.
	 */
	public: void test1()
	{
		string **sourceFirst, **sourceLast;
		typedef SortTestUtils <string**, bool(*)(const string *str1, const string *str2)> Utils;
		string *arr[] = {};
		sourceFirst = arr;
		sourceLast = arr + sizeof(arr) / sizeof(arr[0]);
		Utils::checkAsUnstable(sourceFirst, sourceLast, compareStrings, std::less <string*> ());
	}

	/**
	 * Test with array of pointers that does not contain equivalent unequal elements.
	 */
	public: void test2()
	{
		string **sourceFirst, **sourceLast;
		typedef SortTestUtils <string**, bool(*)(const string *str1, const string *str2)> Utils;
		string a("abc"), b(""), c("g");
		string *arr[] = {&a, &b, &c, &a, &a, &c, &b};
		sourceFirst = arr;
		sourceLast = arr + sizeof(arr) / sizeof(arr[0]);
		Utils::checkAsUnstable(sourceFirst, sourceLast, compareStrings, std::less <string*> ());
	}

	/**
	 * Test with array of pointers that contains equivalent
	 * unequal elements (pointers to objects "b" and "c").
	 */
	public: void test3()
	{
		string **sourceFirst, **sourceLast;
		typedef SortTestUtils <string**, bool(*)(const string *str1, const string *str2)> Utils;
		string a("abc"), b(""), c("");
		string *arr[] = {&a, &b, &c, &a, &a, &c, &b};
		sourceFirst = arr;
		sourceLast = arr + sizeof(arr) / sizeof(arr[0]);
		Utils::checkAsUnstable(sourceFirst, sourceLast, compareStrings, std::less <string*> ());
	}

	/**
	 * Test with array of objects that does not contain equivalent unequal elements.
	 */
	public: void test4()
	{
		string *sourceFirst, *sourceLast;
		typedef SortTestUtils <string*, std::less <string> > Utils;
		string a("abc"), b(""), c("");
		string arr[] = {a, b, c, a, a, c, b};
		sourceFirst = arr;
		sourceLast = arr + sizeof(arr) / sizeof(arr[0]);
		Utils::checkAsUnstable(sourceFirst, sourceLast, std::less <string> (), std::less <string> ());
	}
}


}
