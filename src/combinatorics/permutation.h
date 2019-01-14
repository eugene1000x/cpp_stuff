
#ifndef EUGENEJONAS__CPP_STUFF__COMBINATORICS__PERMUTATION_H
#define EUGENEJONAS__CPP_STUFF__COMBINATORICS__PERMUTATION_H


#include <eugenejonas/cpp_stuff/orderings.h>
#include <eugenejonas/cpp_stuff/sort.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
#include <concepts>
#else
#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#endif


namespace eugenejonas::cpp_stuff
{


template <typename TPL_InputIterator, typename TPL_StrictWeakOrdering> int calculateInversionsBruteForce(TPL_InputIterator first, TPL_InputIterator last, TPL_StrictWeakOrdering swoCompare)
{
	BOOST_CONCEPT_ASSERT((boost::InputIterator <TPL_InputIterator>));
	
	int count = 0;
	
	for ( ; first != last && first != last - 1; ++first)
	{
		TPL_InputIterator it = first;
		++it;
		
		for ( ; it != last; ++it)
		{
			if (swoCompare(*it, *first))
			{
				count++;
			}
		}
	}
	
	return count;
}

template <typename TPL_InputIterator> int calculateInversionsBruteForce(TPL_InputIterator first, TPL_InputIterator last)
{
	std::less <typename std::iterator_traits <TPL_InputIterator> ::value_type> less;
	return calculateInversionsBruteForce(first, last, less);
}

/**
 * Prints out standard representation of the permutation.
 */
template <typename TPL_T, typename TPL_StrictTotalOrdering> std::ostream &operator<<(std::ostream &os, Permutation <TPL_T, TPL_StrictTotalOrdering> const &p)
{
	typename Permutation <TPL_T, TPL_StrictTotalOrdering> ::const_iterator it = p.begin();
	bool isFirst = true;
	
	for ( ; it != p.end(); ++it)
	{
		if (!isFirst)
		{
			os << " ";
		}
		
		os << (*it);
		isFirst = false;
	}
	
	return os;
}

/**
 * Class representing permutation of arbitrary elements. A strict total
 * ordering must be defined for the elements.
 *
 * 
 * Notation:
 * 
 * Variable n is used to denote length of the permutation.
 * 
 * Standard representation of permutation p is denoted as [p(1) p(2) ... p(n)] or [p(1), p(2), ..., p(n)].
 * 
 * For example, [1 4 5 2 3] and [1, 4, 5, 2, 3] denote permutation p such that:
 * p(1) == 1, p(2) == 4, p(3) == 5, p(4) == 2, p(5) == 3.
 * 
 * Representation as a product of disjoint cycles is denoted as (2 3)(5 1 4).
 * 
 * 
 * @param TPL_Permutation_StrictTotalOrdering Must model concept eugenejonas::cpp_stuff::StrictTotalOrdering.
 */
template <typename TPL_Permutation_T = int, typename TPL_Permutation_StrictTotalOrdering = std::less <TPL_Permutation_T> > class Permutation: private std::vector <TPL_Permutation_T>
{
	//private: friend class CycleBuilder;
	private: friend std::ostream &operator<<(std::ostream &os, Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> const &p);
	

	public: typedef typename std::vector <TPL_Permutation_T> ::size_type size_type;
	
	
	private: class CycleBuilder
	{
		private: Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> res;
	
		/**
		 * isInserted[i] == true if element <i + 1> was inserted in the resulting array.
		 */
		private: std::vector <bool> isInserted;
	
		/**
		 * Position at which to insert next element.
		 */
		private: int insertPos;
	
		private: const Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> inverse;
	
		/**
		 * Maximal element which is not yet in res.
		 */
		private: int max;
	
	
		public: CycleBuilder(Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> const &p):
				inverse(p.getInverse()),
				max(p.size()),
				isInserted(p.size()),
				res(p.size()),
				insertPos(p.size() - 1)
		{
			//nothing
		}
	
		private: void next()
		{
			this->max--;
			
			while (this->max > 0)
			{
				if (!this->isInserted[this->res.stoCompare.getOrdinalNumber(this->max)])
				{
					break;
				}
				
				this->max--;
			}
		}
	
		public: Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> getDecompositionInCycles()
		{
			while (this->max > 0)
			{
				int j = this->inverse[this->res.stoCompare.getOrdinalNumber(this->max)];
				this->res[this->insertPos--] = j;
				this->isInserted[this->res.stoCompare.getOrdinalNumber(j)] = true;
			
				while (j != this->max)
				{
					// get element which is mapped to j
					j = this->inverse[this->res.stoCompare.getOrdinalNumber(j)];
	
					this->res[this->insertPos--] = j;
					this->isInserted[this->res.stoCompare.getOrdinalNumber(j)] = true;
				}
	
				this->next();
			}
	
			return this->res;
		}
	}
	
	
	private: TPL_Permutation_StrictTotalOrdering stoCompare;


	/**
	 * Creates identical permutation.
	 * 
	 * @param n Length of the permutation, n >= 0.
	 * @time O(n)
	 * @space O(1)
	 */
	public: Permutation(int n, TPL_Permutation_StrictTotalOrdering stoCompare = TPL_Permutation_StrictTotalOrdering()):
			std::vector <TPL_Permutation_T> (n),
			stoCompare(stoCompare)
	{
		for (int i = 0; i < n; i++)
		{
			(*this)[i] = this->stoCompare.getElementByOrdinalNumber(i);
		}
	}

	/**
	 * Constructs permutation from standard representation.
	 * 
	 * Example:
		
		int a[] = {5, 1, 6, 2, 4, 3};
		Permutation p = std::vector <int> (a, a + sizeof(a) / sizeof(int));

	 * This would construct permutation [5, 1, 6, 2, 4, 3].
	 *
	 * @time O(n)
	 * @space O(1)
	 */
	public: Permutation(const std::vector <TPL_Permutation_T> &standardRepresentation, TPL_Permutation_StrictTotalOrdering stoCompare = TPL_Permutation_StrictTotalOrdering()):
			std::vector <TPL_Permutation_T> (standardRepresentation),
			stoCompare(stoCompare)
	{
		//nothing
	}

	/**
	 * Comparison operators used for sorting in lexicographical order.
	 *
	 * @pre Permutations must be of equal size.
	 * @time O(n)
	 * @space O(1)
	 */
	public: bool operator==(Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> const &other) const
	{
		assert(other.size() == this->size());
		
		//return std::equal(this->begin(), this->end(), other.begin());
		return (std::vector <TPL_Permutation_T>) (*this) == (std::vector <TPL_Permutation_T>) other;
	}
	public: bool operator<(Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> const &other) const
	{
		assert(other.size() == this->size());
		
		//const_iterator it1 = this->begin(), it2 = other.begin();
		//
		//while (it1 != this->end())
		//{
		//	if (*it1 != *it2)
		//	{
		//		return *it1 < *it2;
		//	}
		//
		//	++it1;
		//	++it2;
		//}
		//
		//return false;
		
		return std::lexicographical_compare(this->begin(), this->end(), other.begin(), other.end());
	}
	public: bool operator>(Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> const &other) const
	{
		return other < *this;
	}

	public: size_type getLength() const
	{
		return std::vector <TPL_Permutation_T> ::size();
	}

	/**
	 * Swaps elements at indexes i and j.
	 * 
	 * @time O(1)
	 * @space O(1)
	 */
	public: void swap(int i, int j)
	{
		std::swap(this->at(i), this->at(j));
	}

	/**
	 * Multiplies two permutations. The two permutations must have the same ordering relation.
	 * 
	 * @return Permutation p such that p(element) == this(other(element)).
	 * @time O(n)
	 * @space O(1)
	 */
	public: Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> operator*(Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> const &other) const
	{
		assert(other.size() == this->size());
		
		std::vector <TPL_Permutation_T> resArr(this->size());
		
		for (int i = 0; i < this->size(); i++)
		{
			resArr[i] = this->at(this->stoCompare.getOrdinalNumber(other[i]));
		}
		
		return Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> (resArr, this->stoCompare);
	}

	/**
	 * Calculates the inverse permutation.
	 * 
	 * @time O(n)
	 * @space O(1)
	 */
	public: Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> getInverse() const
	{
		std::vector <TPL_Permutation_T> resArr(this->size());
		
		for (int i = 0; i < this->size(); i++)
		{
			resArr[this->stoCompare.getOrdinalNumber(this->at(i))] = this->stoCompare.getElementByOrdinalNumber(i);
		}
		
		return Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> (resArr, this->stoCompare);
	}

	/**
	 * Returns canonical representation of the decomposition of
	 * this permutation in a product of disjoint cycles.
	 * Canonical way of representing such cycles is to start by
	 * the largest element of each cycle. Cycles are ordered by their
	 * largest element in the ascending order.
	 *
	 * For example, canonical representation of permutation [1 3 4 2 5]
	 * is (1)(4 2 3)(5). In this case, function would return permutation [1 4 2 3 5].
	 *
	 * @time O(n)
	 * @space O(n)
	 */
	public: Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> getDecompositionInCycles() const
	{
		return CycleBuilder(*this).getDecompositionInCycles();
	}

	/**
	 * Reconstructs original permutation from canonical
	 * representation of its decomposition in a product of disjoint cycles.
	 *
	 * For example, canonical representation of permutation [4 2 7 1 3 6 5] is (2)(4 1)(6)(7 5 3).
	 * In this case, "decomposition" parameter would be [2 4 1 6 7 5 3].
	 * Function would return permutation [4 2 7 1 3 6 5].
	 *
	 * Relation between reconstructFromDecompositionInCycles and getDecompositionInCycles:
	 * 
	 * reconstructFromDecompositionInCycles(p.getDecompositionInCycles()) == p
	 * reconstructFromDecompositionInCycles(p).getDecompositionInCycles() == p
	 *
	 * @time O(n)
	 * @space O(1)
	 */
	public: void reconstructFromDecompositionInCycles(const Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> &decomposition)
	{
		assert(decomposition.size() == this->size());
		
		int recordIndex = 0;
		
		for (int i = 0; i < this->size(); i++)
		{
			bool isNewRecord = i + 1 == this->size() || decomposition[recordIndex] < decomposition[i + 1];
			
			if (isNewRecord)
			{
				(*this)[this->stoCompare.getOrdinalNumber(decomposition[i])] = decomposition[recordIndex];
				recordIndex = i + 1;
			}
			else
			{
				(*this)[this->stoCompare.getOrdinalNumber(decomposition[i])] = decomposition[i + 1];
			}
		}
	}

	/**
	 * Returns number of inversions.
	 *
	 * @time n * log(n)
	 */
	public: int calculateInversionsDivideAndConquer() const
	{
		Permutation <TPL_Permutation_T, TPL_Permutation_StrictTotalOrdering> copy = *this;
		return mergeSort(copy.begin(), copy.end());
	}

	/**
	 * Returns number of inversions.
	 *
	 * @time O(n ^ 2)
	 * @space O(1)
	 */
	public: int calculateInversionsBruteForce() const
	{
		return calculateInversionsBruteForce(this->begin(), this->end());
	}

	/**
	 * Generates the next permutation in lexicographical order.
	 * If this permutation is the last one in lexicographical order,
	 * this function does not change state of the Permutation object.
	 *
	 * @return false if the next permutation does not exist, true otherwise.
	 * @time O(n)
	 * @space O(1)
	 */
	public: bool next()
	{
		for (int i = this->size() - 2; i >= 0; i--)
		{
			if (this->stoCompare(this->at(i), this->at(i + 1)))
			{
				int j;
				
				for (j = this->size() - 1; j > i; j--)
				{
					if (this->stoCompare(this->at(i), this->at(j)))
					{
						break;
					}
				}
				
				assert(j > i);
				this->swap(j, i);
				std::reverse(this->begin() + i + 1, this->end());
				return true;
			}
		}
		
		return false;
	}
}


}


#endif
