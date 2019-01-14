
#ifndef EUGENEJONAS__CPP_STUFF__TWO_LEVEL_LOOP_H
#define EUGENEJONAS__CPP_STUFF__TWO_LEVEL_LOOP_H


#include <cassert>
#include <cstddef>


namespace eugenejonas::cpp_stuff
{


/**
 * This class allows to emulate two-level nested loops with a single loop.
 * It can be used to iterate through a 2D structure, where instead of:

	for (int i = 0; i < height; i++)				//dim1
	{
		for (int j = 0; j < width; j++)				//dim2
		{
			// access data at [i * width + j]
		}
	}

 * in some cases it may be more convenient to use the class like this:

	for (TwoLevelLoop it = x.getStartIterator(); it != x.getEndIterator(); ++it)
	{
		// access i, j as it.getI(), it.getJ()
		// access [i * dim2 + j] as [*it]
	}

 */
class TwoLevelLoop
{
	private: std::size_t i, j, index, dim1, dim2;
	
	
	public: TwoLevelLoop(std::size_t dim1, std::size_t dim2):
			i(0),
			j(0),
			index(0)
	{
		this->dim1 = dim1;
		this->dim2 = dim2;
		assert(this->invariant());
	}
	
	/*
	public: TwoLevelLoop(TwoLevelLoop const &other)
	{
		
	}
	*/
	
	private: bool invariant()
	{
		assert(this->dim1 > 0 && this->dim2 > 0);
		assert(this->index == this->dim2 * this->i + this->j);
		assert(this->index <= this->dim1 * this->dim2);
		assert(this->i >= 0 && this->i <= this->dim1);
		if (this->i == this->dim1)
		{
			assert(this->j == 0);
		}
		assert(this->j >= 0 && this->j < this->dim2);
		
		return true;
	}
	
	public: void moveToEnd()
	{
		this->index = this->dim1 * this->dim2;
		this->i = this->dim1;
		this->j = 0;
		assert(this->invariant());
	}
	
	/**
	 * Counter of the main loop (dim1).
	 */
	public: std::size_t getI() const
	{
		return this->i;
	}

	/**
	 * Counter of the inner loop (dim2).
	 */
	public: std::size_t getJ() const
	{
		return this->j;
	}

	/**
	 * One-dimensional index, which is equal to
	 * getI() * dim2 + getJ().
	 */
	public: std::size_t operator*() const
	{
		return this->index;
	}

	/**
	 * Prefix operators ++it and --it.
	 *
	 * @return Post-state of the iterator.
	 */
	public: TwoLevelLoop &operator++()
	{
		this->j++;
		this->index++;
		
		if (this->j == this->dim2)
		{
			this->j = 0;
			this->i++;
		}
		
		assert(this->invariant());
		return *this;
	}
	/*
	public: TwoLevelLoop &operator--()
	{
		
	}
	*/
	
	public: bool operator==(TwoLevelLoop const &other) const
	{
		return this->index == other.index;
	}

	public: bool operator!=(TwoLevelLoop const &other) const
	{
		return this->index != other.index;
	}
		
	/*
	public: TwoLevelLoop &operator=(TwoLevelLoop const &other)
	{
		
	}
	*/
}


}


#endif
