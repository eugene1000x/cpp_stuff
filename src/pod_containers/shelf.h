
#ifndef EUGENEJONAS__CPP_STUFF__POD_CONTAINERS__SHELF_H
#define EUGENEJONAS__CPP_STUFF__POD_CONTAINERS__SHELF_H


#include <eugenejonas/cpp_stuff/pod_containers/pod_containers.h>

#include <cassert>
#include <cstdint>
#include <cstring>

#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
#include <concepts>
#else
#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#endif


namespace eugenejonas::cpp_stuff
{


/**
 * This class represents specific data structure created to solve task
 * http://lio.lv/arhivs/lio06/ino19kopa5.pdf (Latvian 19-th
 * Olympiad in Informatics, 3-rd stage, day 1, task 1).
 * 
 * In short: It stores up to 2 ^ 31 - 1 elements. It allows to add N instances
 * of the same element so that they take up first N empty positions (closest to
 * index 0). It allows to remove N instances of the same element closest to the
 * end (index 2 ^ 31 - 2).
 * 
 * This class supports only byte-copyable element types.
 * 
 * @param TPL_Shelf_T Type of elements stored in the container.
 */
template <typename TPL_Shelf_T> class Shelf: public PodContainer <TPL_Shelf_T>
{
	/**
	 * Represents continuos block of same elements (or empty cells).
	 */
	private: struct ElementBlock
	{
		public: TPL_Shelf_T element;

		/**
		 * Negative value indicates that there are -count empty elements.
		 */
		public: int32_t count;


		public: bool isEmpty() const
		{
			return this->count < 0;
		}

		public: bool operator==(const ElementBlock &other) const
		{
			return !(*this != other);
		}

		public: bool operator!=(const ElementBlock &other) const
		{
			if (other.isEmpty() != this->isEmpty())
			{
				return true;
			}
			
			if (this->isEmpty())
			{
				return false;
			}
			else
			{
				return other.element != this->element;
			}
		}
	}
	
	
	/**
	 * capacity is length of array arr.
	 * size indicates how many array arr elements (of type ElementBlock) are used,
	 * 		it's not number of elements of type TPL_Shelf_T stored in the container.
	 * emptyCount indicates how many elements can be put into the container.
	 *
	 * Methods can safely access elements at indexes [0 .. size - 1].
	 * Maximum possible value for capacity, size and k is 2 ^ 31 - 1.
	 */
	private: int32_t capacity, size, emptyCount;
	private: mutable int32_t k;				//start search for first empty block from this index
	private: ElementBlock *arr;


	public: Shelf():
			arr(new ElementBlock[100000]),
			capacity(100000),
			size(1),
			emptyCount(2147483647),
			k(0)
	{
		this->arr[0].count = -2147483647;
		assert(this->invariant());
	}

	public: ~Shelf()
	{
		delete[] this->arr;
	}

	private: bool invariant() const
	{
		assert(this->arr != nullptr);
		assert(this->capacity > 0 && this->size > 0 && this->size <= this->capacity && this->emptyCount >= 0 && this->k >= 0);
		
		if (this->emptyCount > 0)
		{
			assert(this->k < this->size);
		}
		else
		{
			assert(this->k <= this->size);
		}
		
		int32_t countSum = 0, emptyCountSum = 0;
		
		for (int32_t i = 0; i < this->size; i++)
		{
			assert(this->arr[i].count != -2147483648 && this->arr[i].count != 0);
			
			countSum += (this->arr[i].isEmpty() ? -this->arr[i].count : this->arr[i].count);
			
			if (this->arr[i].isEmpty())
			{
				emptyCountSum -= this->arr[i].count;
			}
			
			if (i > 0)
			{
				assert(this->arr[i] != this->arr[i - 1]);
			}
		}
		
		assert(emptyCountSum == this->emptyCount);
		assert(countSum == 2147483647);
		
		for (int32_t i = 0; i < this->k; i++)
		{
			assert(!this->arr[i].isEmpty());
		}
		
		return true;
	}

	/**
	 * Returns number of elements in the container.
	 */
	public: int32_t getSize() const
	{
		return 2147483647 - this->emptyCount;
	}

	/**
	 * Adds <count> instances of an element.
	 * 
	 * @param element Element to add.
	 * @param count Number of instances to add (count > 0).
	 * @pre There must be enough place for <count> elements.
	 */
	public: void add(TPL_Shelf_T element, int32_t count)
	{
		assert(this->invariant());
		assert(this->emptyCount >= count && count > 0);
		
		while (count > 0)
		{
			int32_t i = this->getFirstEmptyBlock();
			
			if (-this->arr[i].count > count)
			{
				// enough place in arr[i] for all elements
				// ensure that arr[i].element != arr[i - 1].element

				bool isPreviousBlockEqual = i > 0 && this->arr[i - 1].count > 0 && this->arr[i - 1].element == element;
				
				if (isPreviousBlockEqual)
				{
					//subcase 1.1.1 (shelf.odt)

					// do not need to call memmove

					this->arr[i - 1].count += count;
					this->arr[i].count += count;			// (!) not -=
					assert(this->arr[i].count < 0 && this->arr[i - 1].count > 0);
				}
				else
				{
					//subcase 1.1.2 (shelf.odt)

					// move to the right
					this->ensureCapacity(this->size + 1);
					std::memmove(&this->arr[i + 1], &this->arr[i], sizeof(ElementBlock) * (this->size - i));

					assert(this->size - i > 0);
					this->arr[i].count = count;
					this->arr[i].element = element;
					this->arr[i + 1].count += count;		// (!) not -=
					assert(this->arr[i + 1].count < 0);
					this->size++;
					assert(this->k < i + 1);
					this->k = i + 1;
				}
				
				this->emptyCount -= count;
				count = 0;
			}
			else
			{
				bool isPreviousBlockEqual = i > 0 && this->arr[i - 1].count > 0 && element == this->arr[i - 1].element;
				bool isNextBlockEqual = i < this->size - 1 && this->arr[i + 1].count > 0 && element == this->arr[i + 1].element;
				
				this->emptyCount += this->arr[i].count;
				count += this->arr[i].count;		// this->arr[i].count < 0
				
				if (isPreviousBlockEqual)
				{
					if (isNextBlockEqual)
					{
						//subcase 1.2.1 (shelf.odt)
						
						this->arr[i - 1].count += this->arr[i + 1].count - this->arr[i].count;
						assert(this->size - i - 2 >= 0);
						
						if (this->size - i - 2 > 0)
						{
							std::memmove(&this->arr[i], &this->arr[i + 2], sizeof(ElementBlock) * (this->size - i - 2));
						}
						
						this->size -= 2;
					}
					else
					{
						//subcase 1.2.2 (shelf.odt)
						
						this->arr[i - 1].count -= this->arr[i].count;
						assert(this->size - i - 1 >= 0);
						
						if (this->size - i - 1 > 0)
						{
							std::memmove(&this->arr[i], &this->arr[i + 1], sizeof(ElementBlock) * (this->size - i - 1));
						}
						
						this->size--;
					}
				}
				else
				{
					if (isNextBlockEqual)
					{
						//subcase 1.2.3 (shelf.odt)
						
						this->arr[i + 1].count -= this->arr[i].count;
						assert(this->size - i - 2 >= 0);
						std::memmove(&this->arr[i], &this->arr[i + 1], sizeof(ElementBlock) * (this->size - i - 1));
						this->size--;
						this->k = i + 1;
					}
					else
					{
						//subcase 1.2.4 (shelf.odt)
						
						this->arr[i].count = -this->arr[i].count;
						this->arr[i].element = element;
						this->k = i + 1;
					}
				}
			}
		}
		
		assert(this->invariant());
	}

	/**
	 * Removes <count> instances of an element.
	 * 
	 * @param element Element to remove.
	 * @param count Number of instances to remove (count > 0).
	 * @pre Container must contain at least <count> instances of the element.
	 */
	public: void remove(TPL_Shelf_T element, int32_t count)
	{
		assert(this->invariant());
		assert(count > 0);
		
		while (count > 0)
		{
			ElementBlock elementBlock = {element, 1};
			int32_t i = this->size - 1;
			
			while (this->arr[i] != elementBlock)
			{
				i--;
			}
			
			assert(i >= 0);
			
			if (this->arr[i].count > count)
			{
				bool isNextBlockEmpty = i < this->size - 1 && this->arr[i + 1].isEmpty();
			
				if (isNextBlockEmpty)
				{
					//subcase 2.1.1 (shelf.odt)

					// do not need to call memmove

					this->arr[i + 1].count -= count;
					this->arr[i].count -= count;
					
					assert(this->arr[i].count > 0 && this->arr[i + 1].count < 0);
				}
				else
				{
					//subcase 2.1.2 (shelf.odt)

					this->ensureCapacity(this->size + 1);
					assert(this->size - i - 1 >= 0);

					// move to the right
					if (this->size - i - 1 > 0)
					{
						std::memmove(&this->arr[i + 2], &this->arr[i + 1], sizeof(ElementBlock) * (this->size - i - 1));
					}

					this->arr[i + 1].count = -count;
					this->arr[i].count -= count;
					
					assert(this->arr[i + 1].count < 0);
					this->size++;
					
					if (this->k > i + 1)
					{
						this->k = i + 1;
					}
				}
				
				this->emptyCount += count;
				count = 0;
			}
			else
			{
				bool isPreviousBlockEmpty = i > 0 && this->arr[i - 1].isEmpty();
				bool isNextBlockEmpty = i < this->size - 1 && this->arr[i + 1].isEmpty();
				
				this->emptyCount += this->arr[i].count;
				count -= this->arr[i].count;
				
				if (isPreviousBlockEmpty)
				{
					if (isNextBlockEmpty)
					{
						//subcase 2.2.1 (shelf.odt)
						
						this->arr[i - 1].count += this->arr[i + 1].count - this->arr[i].count;
						assert(this->size - i - 2 >= 0);
						
						if (this->size - i - 2 > 0)
						{
							std::memmove(&this->arr[i], &this->arr[i + 2], sizeof(ElementBlock) * (this->size - i - 2));
						}
						
						this->size -= 2;
						assert(this->k < i);
					}
					else
					{
						//subcase 2.2.2 (shelf.odt)
						
						this->arr[i - 1].count -= this->arr[i].count;
						assert(this->size - i - 1 >= 0);
						
						if (this->size - i - 1 > 0)
						{
							std::memmove(&this->arr[i], &this->arr[i + 1], sizeof(ElementBlock) * (this->size - i - 1));
						}
						
						this->size--;
					}
				}
				else
				{
					if (isNextBlockEmpty)
					{
						//subcase 2.2.3 (shelf.odt)
						
						this->arr[i + 1].count -= this->arr[i].count;
						assert(this->size - i - 2 >= 0);
						
						std::memmove(&this->arr[i], &this->arr[i + 1], sizeof(ElementBlock) * (this->size - i - 1));
						this->size--;
						
						if (this->k > i)
						{
							this->k = i;
						}
						else
						{
							this->k = 0;
						}
					}
					else
					{
						//subcase 2.2.4 (shelf.odt)
						
						this->arr[i].count = -this->arr[i].count;
						
						if (this->k > i)
						{
							this->k = i;
						}
						else
						{
							this->k = 0;
						}
					}
				}
			}
		}
	}

	/**
	 * Returns pointer to the element at specified index, or nullptr if
	 * position specified by index is empty.
	 * 
	 * @param n Index of the element (2 ^ 31 - 2 >= n >= 0).
	 */
	public: const TPL_Shelf_T *poll(int32_t n) const
	{
		assert(n >= 0 && n < 2147483647);
		
		int sum = 0;
		
		for (int i = 0; i < this->size; i++)
		{
			/*
			 * Loop invariant:
			 * sum == |arr[0].count| + |arr[1].count| + ... + |arr[i - 1].count| <= n
			 */

			sum += (this->arr[i].isEmpty() ? -this->arr[i].count : this->arr[i].count);
			
			if (sum > n)
			{
				return this->arr[i].isEmpty() ? nullptr : &this->arr[i].element;
			}
		}
		
		assert(false);
	}

	private: int32_t getFirstEmptyBlock() const
	{
		assert(this->invariant());
		assert(this->emptyCount > 0);						// => this->k < this->size
		
		for ( ; this->k < this->size; this->k++)
		{
			if (this->arr[this->k].isEmpty())
			{
				return this->k;
			}
		}
		
		assert(false);
	}

	private: void ensureCapacity(int32_t minCapacity)
	{
		assert(this->invariant());
		assert(minCapacity > 0);
		
		if (minCapacity <= this->capacity)
		{
			return;
		}
		
		this->capacity = minCapacity;
		ElementBlock *tmp = new ElementBlock[this->capacity];
		std::memcpy(tmp, this->arr, this->size * sizeof(ElementBlock));
		delete[] this->arr;
		this->arr = tmp;
		
		assert(this->invariant());
	}
}


}


#endif
