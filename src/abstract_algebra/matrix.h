
#ifndef EUGENEJONAS__CPP_STUFF__ABSTRACT_ALGEBRA__MATRIX_H
#define EUGENEJONAS__CPP_STUFF__ABSTRACT_ALGEBRA__MATRIX_H


#include <eugenejonas/cpp_stuff/two_level_loop.h>

#include <cassert>
#include <cmath>
#include <cstddef>
#include <valarray>

#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
#include <concepts>
#else
#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#endif


namespace eugenejonas::cpp_stuff
{


/**
 * Implementation of matrices over arbitrary ring.
 * The basic requirement that the matrix elements (of type TPL_Matrix_T) must meet
 * is that they form a ring. Methods may have additional requirements.
 *
 * @param TPL_Matrix_T Type of the elements (scalars).
 */
template <std::size_t TPL_Matrix_rows, std::size_t TPL_Matrix_columns, typename TPL_Matrix_T> class Matrix
{
	private: template <std::size_t TPL_MatrixIterator_rows, std::size_t TPL_MatrixIterator_columns> class MatrixIterator: private TwoLevelLoop
	{
		public: using TwoLevelLoop::moveToEnd;
		public: using TwoLevelLoop::operator*;
		public: using TwoLevelLoop::operator--;
		public: using TwoLevelLoop::operator++;
	
	
		public: MatrixIterator():
				TwoLevelLoop(TPL_MatrixIterator_rows, TPL_MatrixIterator_columns)
		{
			//do nothing
		}

		/*
		public: MatrixIterator(MatrixIterator <TPL_MatrixIterator_rows, TPL_MatrixIterator_columns> const &other):
				TwoLevelLoop(other)
		{
			
		}
		*/

		/**
		 * Postfix operator: it++.
		 * Less efficient than the prefix operator because it
		 * must backup the old state.
		 * 
		 * @param dummy Dummy parameter needed to distinguish between prefix and postfix variations.
		 * @return Pre-state (state before the increment operation
		 *		is performed) of the iterator.
		 */
		private: MatrixIterator <TPL_MatrixIterator_rows, TPL_MatrixIterator_columns> operator++(int dummy)
		{
			MatrixIterator <TPL_MatrixIterator_rows, TPL_MatrixIterator_columns> res = *this;
			++(*this);
			return res;
		}
		
		public: std::size_t getRowNo() const
		{
			return this->getI();
		}
		
		public: std::size_t getColumnNo() const
		{
			return this->getJ();
		}
	}
	
	
	/*
	 * Internally, this class uses the following representation:
	 * if M is a matrix <rows> * <columns> and M[i, j] denotes the
	 * element in the i-th row and the j-th column,
	 * then M[i, j] = valarray[columns * i + j]
	 *
	 * valarray[0 .. columns - 1]:					M[0, 0] M[0, 1] ... M[0, columns - 1]
	 * valarray[columns .. 2 * columns - 1]:		M[1, 0] M[1, 1] ... M[1, columns - 1]
	 *								...
	 *
	 * Useful links:
	 *
	 * [13.10] How do I create a subscript operator for a Matrix class?
	 * http://www.parashift.com/c++-faq/operator-overloading.html#faq-13.10
	 *
	 * VPF::Шабл.класс "Матрица".Помогите сделать пожалуйста! - Форум программистов
	 * http://forum.vingrad.ru/forum/s/90fea4d08caae4b92aacc43ac4d80c52/topic-215162/anchor-entry1539483/15.html
	 *
	 */


	private: static const TPL_Matrix_T ZERO, ONE;		//scalars representing multiplicative identity and zero
	
	
	private: std::valarray <TPL_Matrix_T> elements;


	public: Matrix():
			elements(TPL_Matrix_rows * TPL_Matrix_columns)
	{
		//do nothing
	}

	public: Matrix(const Matrix <TPL_Matrix_rows, TPL_Matrix_columns, TPL_Matrix_T> &other)
	{
		*this = other;
	}

	/**
	 * @param arr Array of elements to initialize with. Must have length <TPL_Matrix_rows> * <TPL_Matrix_columns>.
	 */
	public: Matrix(TPL_Matrix_T arr[]):
			elements(arr, TPL_Matrix_rows * TPL_Matrix_columns)
	{
		//do nothing
	}

	/**
	 * Assignment operator.
	 */
	public: Matrix <TPL_Matrix_rows, TPL_Matrix_columns, TPL_Matrix_T> &operator=(const Matrix <TPL_Matrix_rows, TPL_Matrix_columns, TPL_Matrix_T> &other)
	{
		this->elements = other.elements;
		return *this;
	}

	/**
	 * Two matrices are equal if they have the same dimensions and elements.
	 */
	public: bool operator==(Matrix <TPL_Matrix_rows, TPL_Matrix_columns, TPL_Matrix_T> const &other) const
	{
		return Matrix <TPL_Matrix_rows, TPL_Matrix_columns, TPL_Matrix_T> ::doVectorsEqual(this->elements, other.elements);
	}
	public: bool operator!=(Matrix <TPL_Matrix_rows, TPL_Matrix_columns, TPL_Matrix_T> const &other) const
	{
		return !(*this == other);
	}

	/**
	 * Returns the size of the matrix (the number of elements in it).
	 */
	public: std::size_t getSize() const
	{
		return TPL_Matrix_rows * TPL_Matrix_columns;
	}

	public: TPL_Matrix_T &operator()(std::size_t row, std::size_t column)
	{
		return this->getRow(row)[column];
	}
	public: TPL_Matrix_T operator()(std::size_t row, std::size_t column) const
	{
		return this->getRow(row)[column];
	}

	/**
	 * The first operator multiplies this matrix by a scalar, the second
	 * operator multiplies it by a vector, the third operator multiplies it by
	 * another matrix.
	 *
	 * @param v Must have length <TPL_Matrix_rows>.
	 * @return Vector of length <TPL_Matrix_rows>.
	 */
	public: Matrix <TPL_Matrix_rows, TPL_Matrix_columns, TPL_Matrix_T> &operator*=(const TPL_Matrix_T &scalar)
	{
		this->elements *= scalar;
		return *this;
	}
	public: std::valarray <TPL_Matrix_T> operator*(const std::valarray <TPL_Matrix_T> &v) const
	{
		std::valarray <TPL_Matrix_T> res(TPL_Matrix_rows);
		for (std::size_t i = 0; i < TPL_Matrix_rows; i++)
		{
			res[i] = Matrix::multiply(this->getRow(i), v);
		}
		return res;
	}
	public: template <std::size_t TPL_columns2> Matrix <TPL_Matrix_rows, TPL_columns2, TPL_Matrix_T> operator*(const Matrix <TPL_Matrix_columns, TPL_columns2, TPL_Matrix_T> &other) const
	{
		Matrix <TPL_Matrix_rows, TPL_columns2, TPL_Matrix_T> res;
		MatrixIterator <TPL_Matrix_rows, TPL_columns2> it = res.getStartIterator();

		while (it != res.getEndIterator())
		{
			res.getElement(*it) = Matrix::multiply(this->getRow(it.getRowNo()), other.getColumn(it.getColumnNo()));
			++it;
		}
		
		return res;
	}

	private: std::slice_array <TPL_Matrix_T> getRow(std::size_t row)
	{
		return this->elements[std::slice(row * TPL_Matrix_columns, TPL_Matrix_columns, 1)];
	}

	private: std::valarray <TPL_Matrix_T> getRow(std::size_t row) const
	{
		return this->elements[std::slice(row * TPL_Matrix_columns, TPL_Matrix_columns, 1)];
	}

	private: std::slice_array <TPL_Matrix_T> getColumn(std::size_t column)
	{
		return this->elements[std::slice(column, TPL_Matrix_rows, TPL_Matrix_columns)];
	}

	private: std::valarray <TPL_Matrix_T> getColumn(std::size_t column) const
	{
		return this->elements[std::slice(column, TPL_Matrix_rows, TPL_Matrix_columns)];
	}

	/**
	 * Compares two valarrays of the same size.
	 */
	public: template <typename TPL_T> static bool doVectorsEqual(std::valarray <TPL_T> const &v1, std::valarray <TPL_T> const &v2)
	{
		// min() is not defined if valarray is empty
		if (v1.size() == 0)
		{
			return true;
		}

		std::valarray <bool> b = v1 == v2;
		return b.min() == true;
	}

	private: TPL_Matrix_T &getElement(std::size_t n)
	{
		return this->elements[n];
	}

	private: static TPL_Matrix_T multiply(const std::valarray <TPL_Matrix_T> &v1, const std::valarray <TPL_Matrix_T> &v2)
	{
		TPL_Matrix_T res = Matrix <TPL_Matrix_rows, TPL_Matrix_columns, TPL_Matrix_T> ::ZERO;
		for (std::size_t i = 0; i < v1.size(); i++)
		{
			res += v1[i] * v2[i];
		}
		return res;
	}

	private: MatrixIterator <TPL_Matrix_rows, TPL_Matrix_columns> getStartIterator()
	{
		MatrixIterator <TPL_Matrix_rows, TPL_Matrix_columns> res();
		return res;
	}

	private: MatrixIterator <TPL_Matrix_rows, TPL_Matrix_columns> getEndIterator()
	{
		MatrixIterator <TPL_Matrix_rows, TPL_Matrix_columns> res();
		res.moveToEnd();
		return res;
	}
}

template <std::size_t TPL_Matrix_rows, std::size_t TPL_Matrix_columns, typename TPL_Matrix_T> const TPL_Matrix_T Matrix <TPL_Matrix_rows, TPL_Matrix_columns, TPL_Matrix_T> ::ONE = TPL_Matrix_T(1);
template <std::size_t TPL_Matrix_rows, std::size_t TPL_Matrix_columns, typename TPL_Matrix_T> const TPL_Matrix_T Matrix <TPL_Matrix_rows, TPL_Matrix_columns, TPL_Matrix_T> ::ZERO = TPL_Matrix_T(0);


}


#endif
