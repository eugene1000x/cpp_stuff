
#ifndef EUGENEJONAS__CPP_STUFF__SORT_H
#define EUGENEJONAS__CPP_STUFF__SORT_H


#include <eugenejonas/cpp_stuff/orderings.h>

#include <algorithm>
#include <cassert>
#include <iterator>
#include <set>
#include <string>
#include <vector>

#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
#include <concepts>
#else
#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#endif


/*
 * Note: All orderings must be consistent with equality (==) and inequality (!=),
 * otherwise some things may not work correctly (for example, std::multiset::operator==).
 */


namespace eugenejonas::cpp_stuff
{


/**
 * Checks if the given range [first; last) is sorted
 * with respect to the given ordering.
 */
template <typename TPL_InputIterator, typename TPL_StrictWeakOrdering>
bool isSorted(TPL_InputIterator first, TPL_InputIterator last, TPL_StrictWeakOrdering swoCompare)
{
	typedef typename iterator_traits <TPL_InputIterator> ::value_type value_type;


	BOOST_CONCEPT_ASSERT((boost::InputIterator <TPL_InputIterator>));
	BOOST_CONCEPT_ASSERT((StrictWeakOrdering <TPL_StrictWeakOrdering, value_type>));


	// no element can be greater than the one just after it
	for (TPL_InputIterator it = first; it != last; ++it)
	{
		TPL_InputIterator itNext = it;
		++itNext;
		
		if (itNext == last)
		{
			break;
		}
		
		if (swoCompare(*itNext, *it))
		{
			return false;
		}
	}

	return true;
}

/**
 * Checks if the given range [first; last) is unstable-sorted
 * with respect to the given strict weak ordering and the given source range
 * [sourceFirst; sourceLast). This function returns true even if
 * relative order of equivalent elements is not preserved.
 * 
 * @param stoCompare Actually, strict weak ordering would be enough,
 *		but due to inconsistencies in C++ standard (see below), total ordering is needed.
 *		It does not need to be consistent with the given weak ordering.
 */
template <typename TPL_InputIterator1, typename TPL_InputIterator2, typename TPL_StrictWeakOrdering, typename TPL_StrictTotalOrdering> bool isUnstableSorted(
		TPL_InputIterator1 first,
		TPL_InputIterator1 last,
		TPL_InputIterator2 sourceFirst,
		TPL_InputIterator2 sourceLast,
		TPL_StrictWeakOrdering swoCompare,
		TPL_StrictTotalOrdering stoCompare
)
{
	/*
	 * Problem with weak/total ordering
	 * 
	 * ISO/IEC 14882:2003, table 65, §23.1#5 (Containers library > Container requirements)
	 * two multisets a and b are equal (a == b) if:
	 * a.size() == b.size() && equal(a.begin(), a.end(), b.begin())
	 * 
	 * This doesn't make sense, because if both multisets contain the same two equivalent, but
	 * not equal elements c and d, then [a.begin(); a.end()) could be (c, d)
	 * and [b.begin(); b.end()) could be (d, c), and this formula would tell that
	 * multisets aren't equal.
	 * 
	 * So, weak ordering is insufficient for multiset.
	 * Comparison operator for multiset works as expected only
	 * if multiset has total ordering. Experiments also show that it
	 * doesn't work correctly if non-total ordering is given.
	 */


	typedef typename iterator_traits <TPL_InputIterator1> ::value_type value_type;


	BOOST_CONCEPT_ASSERT((boost::InputIterator <TPL_InputIterator1>));
	BOOST_CONCEPT_ASSERT((boost::InputIterator <TPL_InputIterator2>));
	BOOST_CONCEPT_ASSERT((StrictWeakOrdering <TPL_StrictWeakOrdering, value_type>));
	BOOST_CONCEPT_ASSERT((StrictTotalOrdering <TPL_StrictTotalOrdering, value_type>));


	assert((sourceLast - sourceFirst) == (last - first));

	// check if arrays contain the same elements
	std::multiset <value_type, TPL_StrictTotalOrdering> sortedMultiset(first, last, stoCompare);
	std::multiset <value_type, TPL_StrictTotalOrdering> sourceMultiset(sourceFirst, sourceLast, stoCompare);
	if (sortedMultiset != sourceMultiset)
	{
		return false;
	}

	return isSorted(first, last, swoCompare);
}

/**
 * Checks if the given range [first; last) is stable-sorted
 * with respect to the given ordering and the given source range
 * [sourceFirst; sourceLast). This function returns false if
 * relative order of equivalent elements is not preserved.
 */
template <typename TPL_InputIterator1, typename TPL_InputIterator2, typename TPL_StrictWeakOrdering> bool isStableSorted(
		TPL_InputIterator1 first,
		TPL_InputIterator1 last,
		TPL_InputIterator2 sourceFirst,
		TPL_InputIterator2 sourceLast,
		TPL_StrictWeakOrdering swoCompare
)
{
	typedef typename iterator_traits <TPL_InputIterator1> ::value_type value_type;
	typedef typename iterator_traits <TPL_InputIterator1> ::pointer pointer;


	BOOST_CONCEPT_ASSERT((boost::InputIterator <TPL_InputIterator1>));
	BOOST_CONCEPT_ASSERT((boost::InputIterator <TPL_InputIterator2>));
	BOOST_CONCEPT_ASSERT((StrictWeakOrdering <TPL_StrictWeakOrdering, value_type>));


	assert((sourceLast - sourceFirst) == (last - first));

	pointer expected = new value_type[sourceLast - sourceFirst];
	std::copy(sourceFirst, sourceLast, expected);
	std::stable_sort(expected, expected + (sourceLast - sourceFirst), swoCompare);

	bool res = std::equal(first, last, expected);
	delete[] expected;
	return res;
}

/**
 * Merge function for the merge sort algorithm. This function merges
 * two sorted ranges of elements into a single sorted range.
 * Before function call, ranges [first1; last1) and [first2; last2)
 * must be sorted in ascending order. Input ranges may overlap with
 * each other or with output range.
 *
 * @pre The following identities must hold for every two elements:
 *		swoCompare(*(first1 + i + 1), *(first1 + i)) == false
 *		swoCompare(*(first2 + i + 1), *(first2 + i)) == false
 * @post The following identity will hold for every two elements:
 *		swoCompare(*(output + i + 1), *(output + i)) == false
 * @return Number of iterator pairs (x, y) such that x is an
 *		iterator within the first range, y is an iterator within the
 *		second range, and swoCompare(*y, *x) == true.
 */
template <typename TPL_InputIterator1, typename TPL_InputIterator2, typename TPL_OutputIterator, typename TPL_StrictWeakOrdering>
#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
requires std::InputIterator <TPL_InputIterator1>,
		std::InputIterator <TPL_InputIterator2>,
		std::OutputIterator <TPL_OutputIterator, typename iterator_traits <TPL_InputIterator1> ::value_type>,
		std::StrictWeakOrder <TPL_StrictWeakOrdering, typename iterator_traits <TPL_InputIterator1> ::value_type>,
		std::Convertible <typename iterator_traits <TPL_InputIterator1> ::value_type, typename iterator_traits <TPL_InputIterator2> ::value_type>,
		std::Convertible <typename iterator_traits <TPL_InputIterator1> ::value_type, typename iterator_traits <TPL_OutputIterator> ::value_type>
#endif
int merge(TPL_InputIterator1 first1, TPL_InputIterator1 last1, TPL_InputIterator2 first2, TPL_InputIterator2 last2, TPL_OutputIterator output, TPL_StrictWeakOrdering swoCompare)
{
	#ifndef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
	BOOST_CONCEPT_ASSERT((boost::InputIterator <TPL_InputIterator1>));
	BOOST_CONCEPT_ASSERT((boost::InputIterator <TPL_InputIterator2>));
	BOOST_CONCEPT_ASSERT((boost::OutputIterator <TPL_OutputIterator, typename iterator_traits <TPL_InputIterator1> ::value_type>));
	BOOST_CONCEPT_ASSERT((StrictWeakOrdering <TPL_StrictWeakOrdering, typename iterator_traits <TPL_InputIterator1> ::value_type>));
	BOOST_CONCEPT_ASSERT((boost::Convertible <typename iterator_traits <TPL_InputIterator1> ::value_type, typename iterator_traits <TPL_InputIterator2> ::value_type>));
	BOOST_CONCEPT_ASSERT((boost::Convertible <typename iterator_traits <TPL_InputIterator1> ::value_type, typename iterator_traits <TPL_OutputIterator> ::value_type>));
	#endif


	typedef typename iterator_traits <TPL_InputIterator2> ::value_type value_type;
	typedef std::vector <value_type> stdvector;


	int count = 0;
	stdvector input1(first1, last1);
	stdvector input2(first2, last2);
	typename stdvector::iterator it1 = input1.begin();
	typename stdvector::iterator it2 = input2.begin();

	while (it1 != input1.end() && it2 != input2.end())
	{
		if (swoCompare(*it2, *it1))
		{
			count += (input1.end() - it1);
			*output = *it2;
			++output;
			++it2;
		}
		else
		{
			*output = *it1;
			++output;
			++it1;
		}
	}
	
	assert((it1 == input1.end()) != (it2 == input2.end()));
	
	if (it1 != input1.end())
	{
		std::copy(it1, input1.end(), output);
	}
	else
	{
		std::copy(it2, input2.end(), output);
	}
	
	return count;
}

/**
 * Pushes down element of a heap. Heap is represented as
 * sequence of elements in which first element has the greatest
 * priority. If swoCompare(a, b) == true, b has greater priority than a.
 *
 * @param first First element of the sequence representing heap.
 * @param last Iterator behind last element of the sequence
 *		representing heap.
 * @param element Iterator to the element to push down.
 */
template <typename TPL_Iterator, typename TPL_StrictWeakOrdering>
#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
requires std::RandomAccessIterator <TPL_Iterator>,
		std::StrictWeakOrder <TPL_StrictWeakOrdering, std::RandomAccessIterator <TPL_Iterator> ::value_type>
#endif
void heapify(TPL_Iterator first, TPL_Iterator last, TPL_Iterator element, TPL_StrictWeakOrdering swoCompare)
{
	#ifndef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
	BOOST_CONCEPT_ASSERT((boost::RandomAccessIterator <TPL_Iterator>));
	BOOST_CONCEPT_ASSERT((StrictWeakOrdering <TPL_StrictWeakOrdering, typename std::iterator_traits <TPL_Iterator> ::value_type>));
	#endif


	assert(first <= element && element < last);
	
	do
	{
		TPL_Iterator tmp = element;
		
		if (2 * (element - first) + 1 < (last - first) && swoCompare(*tmp, *(first + (2 * (element - first) + 1))))
		{
			tmp = first + (2 * (element - first) + 1);
		}
		
		if (2 * (element - first) + 2 < (last - first) && swoCompare(*tmp, *(first + (2 * (element - first) + 2))))
		{
			tmp = first + (2 * (element - first) + 2);
		}
		
		if (element == tmp)
		{
			break;
		}
		
		std::iter_swap(element, tmp);
		element = tmp;
	}
	while (true);
}

/**
 * Algorithms sort range [first; last) so that for every
 * two iterators a, b within that range the following
 * relationship holds:
 * if a < b, then !swoCompare(*b, *a).
 */
template <class TPL_Sorter_Iterator, class TPL_Sorter_StrictWeakOrdering>
#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
requires std::RandomAccessIterator <TPL_Sorter_Iterator>,
		std::StrictWeakOrder <TPL_Sorter_StrictWeakOrdering, std::RandomAccessIterator <TPL_Sorter_Iterator> ::value_type>
#endif
class Sorter
{
	#ifndef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
	BOOST_CONCEPT_ASSERT((boost::RandomAccessIterator <TPL_Sorter_Iterator>));
	BOOST_CONCEPT_ASSERT((StrictWeakOrdering <TPL_Sorter_StrictWeakOrdering, typename std::iterator_traits <TPL_Sorter_Iterator> ::value_type>));
	#endif


	private: typedef typename iterator_traits <TPL_Sorter_Iterator> ::difference_type difference_type;


	private: TPL_Sorter_Iterator first, last;
	private: TPL_Sorter_StrictWeakOrdering swoCompare;


	public: Sorter(TPL_Sorter_Iterator first, TPL_Sorter_Iterator last, TPL_Sorter_StrictWeakOrdering swoCompare = TPL_Sorter_StrictWeakOrdering()):
			first(first),
			last(last),
			swoCompare(swoCompare)
	{
		assert(first <= last);
	}

	/**
	 * Initializes the sorter object with the range [first; last).
	 */
	public: void init(TPL_Sorter_Iterator first, TPL_Sorter_Iterator last)
	{
		assert(first <= last);
		this->first = first;
		this->last = last;
	}

	public: void selectionSort()
	{
		Sorter::selectionSort(this->first, this->last, this->swoCompare);
	}
	
	public: void bubbleSort()
	{
		Sorter::bubbleSort(this->first, this->last, this->swoCompare);
	}
	
	public: void heapSort()
	{
		Sorter::heapSort(this->first, this->last, this->swoCompare);
	}
	
	public: void quickSort()
	{
		Sorter::quickSort(this->first, this->last, this->swoCompare);
	}
	
	/**
	 * Returns number of inversions, which are defined as follows:
	 * inversion in sequence A is pair of elements (A[i], A[j]) such
	 * that i < j and swoCompare(A[j], A[i]) == true.
	 */
	public: int mergeSort()
	{
		return Sorter::mergeSort(this->first, this->last, this->swoCompare);
	}

	private: static void selectionSort(TPL_Sorter_Iterator first, TPL_Sorter_Iterator last, TPL_Sorter_StrictWeakOrdering swoCompare)
	{
		for (difference_type j = 1; j < last - first; j++)
		{
			for (difference_type k = 0; k < j; k++)
			{
				if (swoCompare(*(first + j), *(first + k)))
				{
					std::iter_swap(first + j, first + k);
				}
			}
		}
	}

	private: static void bubbleSort(TPL_Sorter_Iterator first, TPL_Sorter_Iterator last, TPL_Sorter_StrictWeakOrdering swoCompare)
	{
		const difference_type n = last - first;
		
		for (difference_type i = 0; i < n; ++i)
		{
			difference_type min = i;
			
			for (difference_type j = i + 1; j < n; ++j)
			{
				if (swoCompare(*(first + j), *(first + min)))
				{
					min = j;
				}
			}
			
			if (i != min)
			{
				std::iter_swap(first + i, first + min);
			}
		}
	}

	private: static void heapSort(TPL_Sorter_Iterator first, TPL_Sorter_Iterator last, TPL_Sorter_StrictWeakOrdering swoCompare)
	{
		// take care of corner cases
		if (first == last || first == last - 1)
		{
			return;
		}

		difference_type size = last - first;

		/*
		 * Build heap [first..last).
		 * Heapify all nodes which have at least one child.
		 * "first" points to the root, the greatest element.
		 */
		for (difference_type i = (size - 2) / 2; i >= 0; i--)
		{
			heapify(first, last, first + i, swoCompare);
		}
		
		/*
		 * One element will be put in its place in each iteration.
		 * Heap size descreases by 1 during every iteration.
		 */
		while (size > 1)
		{
			/*
			 * Invariant:
			 *	1) elements [first .. (first + size)) form a heap
			 *	2) elements [(first + size) .. last) are sorted
			 */

			--size;
			std::iter_swap(first, first + size);
			heapify(first, first + size, first, swoCompare);
		}
	}

	private: static void quickSort(TPL_Sorter_Iterator first, TPL_Sorter_Iterator last, TPL_Sorter_StrictWeakOrdering swoCompare)
	{
		if (first >= last - 1)
		{
			return;
		}

		// array has at least 2 elements

		TPL_Sorter_Iterator i = first, j = last - 1;
		bool c = false;

		while (i < j)
		{
			/*
			 * 1) if c == true, pivot == *j; if c == false, pivot == *i
			 * 2) for all k (k > j => a[k] >= pivot; k < i => a[k] <= pivot)
			 */

			if (swoCompare(*j, *i))
			{
				std::iter_swap(i, j);
				c = !c;
			}
			
			c ? (++i) : (--j);
		}

		assert(i == j);
		
		Sorter::quickSort(first, i + 1, swoCompare);
		Sorter::quickSort(i + 1, last, swoCompare);
	}

	private: static int mergeSort(TPL_Sorter_Iterator first, TPL_Sorter_Iterator last, TPL_Sorter_StrictWeakOrdering swoCompare)
	{
		if (first == last || first == last - 1)
		{
			return 0;
		}
		
		int count = Sorter::mergeSort(first, first + (last - first) / 2, swoCompare);
		count += Sorter::mergeSort(first + (last - first) / 2, last, swoCompare);
		
		count += merge(
			first,
			first + (last - first) / 2,
			first + (last - first) / 2,
			last,
			first,
			swoCompare
		);
		
		return count;
	}
}


}


#endif
