
#ifndef EUGENEJONAS__CPP_STUFF__ORDERINGS_H
#define EUGENEJONAS__CPP_STUFF__ORDERINGS_H


#include <algorithm>
#include <cassert>
#include <vector>

#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
#include <concepts>
#else
#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#endif


namespace eugenejonas::cpp_stuff
{


/**
 * BCCL-compatible concept-checking class which can be used to check
 * whether a type models StrictWeakOrdering concept.
 * Description of the concept can be found at SGI website:
 * http://www.sgi.com/tech/stl/StrictWeakOrdering.html
 *
 * @param TPL_StrictWeakOrdering_T Type in question.
 * @param TPL_StrictWeakOrdering_Element Type of elements being compared by the ordering operation.
 */
#ifndef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
template <typename TPL_StrictWeakOrdering_T, typename TPL_StrictWeakOrdering_Element>
struct StrictWeakOrdering: boost::BinaryPredicate <
		TPL_StrictWeakOrdering_T,
		TPL_StrictWeakOrdering_Element,
		TPL_StrictWeakOrdering_Element
>
{
	//nothing
}
#endif

/**
 * This struct defines StrictTotalOrdering concept.
 * Strict total ordering is binary predicate that compares two objects,
 * returning true if the first precedes the second. This predicate must
 * satisfy standard mathematical definition of strict total ordering.
 * In strict total ordering no two distinct elements can be equivalent.
 */
template <typename TPL_StrictTotalOrdering_X, typename TPL_StrictTotalOrdering_Element>
struct StrictTotalOrdering: boost::BinaryPredicate <
		TPL_StrictTotalOrdering_X,
		TPL_StrictTotalOrdering_Element
>
{
	//nothing
}

/**
 * This function induces a strict weak ordering
 * on the set of all pointers to strings. Two unequal pointers to equal
 * strings are equivalent with respect to this ordering.
 */
bool compareStrings(const std::string *a, const std::string *b)
{
	return *a < *b;
}

/**
 * Utility function that compares two unsigned integers by the last digit
 * in their decimal representation. This function induces a strict weak
 * ordering on the set of all unsigned integers.
 */
bool compareLastDigit(unsigned a, unsigned b)
{
	return a % 10 < b % 10;
}

/**
 * Compares two integers by their last digit. This induces strict weak ordering
 * on the set of all non-negative integers.
 */
struct CompareLastDigit
{
	/**
	 * Compares two numbers.
	 * 
	 * @pre a, b >= 0
	 * @return true if the last digit of <a> is less than the last digit of <b>.
	 */
	public: bool operator()(int a, int b) const
	{
		assert(a >= 0 && b >= 0);
		return a % 10 < b % 10;
	}
}

struct StrictTotalIntegerOrdering
{
	/**
	 * Compares two elements.
	 */
	public: bool operator()(int a, int b) const
	{
		return a < b;
	}

	public: int getOrdinalNumber(int element) const
	{
		return element - 1;
	}

	public: int getElementByOrdinalNumber(int ordinalNumber) const
	{
		return ordinalNumber + 1;
	}
}

/**
 * Represents custom strict total ordering in which the order of elements is defined by an array
 * (the smallest element is at index 0).
 */
template <typename TPL_CustomStrictTotalOrdering_T> struct CustomStrictTotalOrdering: private std::vector <TPL_CustomStrictTotalOrdering_T>
{
	public: CustomStrictTotalOrdering(std::vector <TPL_CustomStrictTotalOrdering_T> const &v):
			std::vector <TPL_CustomStrictTotalOrdering_T> (v)
	{
		//nothing
	}

	public: int getOrdinalNumber(TPL_CustomStrictTotalOrdering_T const &element) const
	{
		return (int) (std::find(this->begin(), this->end(), element) - this->begin());
	}

	/**
	 * Compares two elements.
	 */
	public: bool operator()(TPL_CustomStrictTotalOrdering_T const &a, TPL_CustomStrictTotalOrdering_T const &b) const
	{
		return std::find(this->begin(), this->end(), a) < std::find(this->begin(), this->end(), b);
	}

	public: TPL_CustomStrictTotalOrdering_T const &getElementByOrdinalNumber(int ordinalNumber) const
	{
		return this->at(ordinalNumber);
	}
}


}


#endif
