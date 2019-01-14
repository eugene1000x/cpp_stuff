
#ifndef EUGENEJONAS__CPP_STUFF__ABSTRACT_ALGEBRA__TRIVIAL_RING_H
#define EUGENEJONAS__CPP_STUFF__ABSTRACT_ALGEBRA__TRIVIAL_RING_H


#include <eugenejonas/cpp_stuff/abstract_algebra/concepts.h>

#include <cassert>
#include <functional>

#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
#include <concepts>
#else
#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#endif


namespace eugenejonas::cpp_stuff
{


/**
 * Class representing trivial ring, which consists of a single element.
 */
template <typename TPL_TrivialRing_T>
#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
requires std::CopyAssignable <TPL_TrivialRing_T>
		&& std::CopyConstructible <TPL_TrivialRing_T>
		&& std::EqualityComparable <TPL_TrivialRing_T>
#endif
class TrivialRing
{
	private: TPL_TrivialRing_T element;


	public: TrivialRing(TPL_TrivialRing_T const &x):
			element(x)
	{
		//nothing
	}
	
	public: TrivialRing(TrivialRing <TPL_TrivialRing_T> const &other):
			element(other.element)
	{
		//nothing
	}

	public: bool operator==(TrivialRing <TPL_TrivialRing_T> const &other) const
	{
		return other.element == this->element;
	}

	public: TrivialRing <TPL_TrivialRing_T> &operator=(TrivialRing <TPL_TrivialRing_T> const &other)
	{
		this->element = other.element;
		return *this;
	}

	public: TrivialRing <TPL_TrivialRing_T> operator+(TrivialRing <TPL_TrivialRing_T> const &other) const
	{
		assert(other.element == this->element);
		return *this;
	}
	
	public: TrivialRing <TPL_TrivialRing_T> operator-(TrivialRing <TPL_TrivialRing_T> const &other) const
	{
		assert(other.element == this->element);
		return *this;
	}
	
	public: TrivialRing <TPL_TrivialRing_T> operator*(TrivialRing <TPL_TrivialRing_T> const &other) const
	{
		assert(other.element == this->element);
		return *this;
	}
}

#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP

/**
 * The only element of any trivial ring forms commutative group
 * under addition (ordinary "+" operation).
 */
concept_map CommutativeGroup <TrivialRing, std::plus <TrivialRing> >
{
	TrivialRing getIdentityElement()
	{
		return TrivialRing();
	}
	
	TrivialRing getInverseElement(TrivialRing const &x)
	{
		return TrivialRing();
	}
}

/**
 * The only element of any trivial ring forms commutative group
 * under multiplication (ordinary "*" operation).
 */
concept_map CommutativeGroup <TrivialRing, std::multiplies <TrivialRing> >
{
	TrivialRing getIdentityElement()
	{
		return TrivialRing();
	}
	
	TrivialRing getInverseElement(TrivialRing const &a)
	{
		return TrivialRing();
	}
}

/**
 * Any trivial ring is ring with identity with ordinary "+" and "*" operations.
 */
concept_map RingWithIdentity <TrivialRing>
{
	//nothing
}

#endif


}


#endif
