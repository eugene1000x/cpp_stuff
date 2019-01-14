
#ifndef EUGENEJONAS__CPP_STUFF__ABSTRACT_ALGEBRA__CONCEPTS_H
#define EUGENEJONAS__CPP_STUFF__ABSTRACT_ALGEBRA__CONCEPTS_H


#include <cassert>
#include <functional>

#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
#include <concepts>
#else
#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#endif


/*
 * Concepts related to algebraic structures.
 * Models of these concepts are classes whose instances represent
 * elements of the corresponding algebraic structure.
 */


namespace eugenejonas::cpp_stuff
{


concept SemiGroup <typename TPL_SemiGroup_T, typename TPL_SemiGroup_Op>
{
	requires std::EqualityComparable <TPL_SemiGroup_T>;
	requires std::CopyConstructible <TPL_SemiGroup_T>;
	requires std::CopyAssignable <TPL_SemiGroup_T>;
	requires std::Callable2 <TPL_SemiGroup_Op, TPL_SemiGroup_T, TPL_SemiGroup_T>;
	requires std::SameType <Callable2 <TPL_SemiGroup_Op, TPL_SemiGroup_T, TPL_SemiGroup_T> ::result_type, TPL_SemiGroup_T>;
	
	
	axiom associativity(TPL_SemiGroup_Op op, TPL_SemiGroup_T a, TPL_SemiGroup_T b, TPL_SemiGroup_T c)
	{
		op(op(a, b), c) == op(a, op(b, c));
	}
}

concept Monoid <typename TPL_Monoid_T, typename TPL_Monoid_Op> : SemiGroup <TPL_Monoid_T, TPL_Monoid_Op>
{
	TPL_Monoid_T getIdentityElement();
	
	
	axiom identityElement(TPL_Monoid_Op op, TPL_Monoid_T x)
	{
		op(x, this->getIdentityElement()) == x;
		op(this->getIdentityElement(), x) == x;
	}
}

concept Group <typename TPL_Group_T, typename TPL_Group_Op> : Monoid <TPL_Group_T, TPL_Group_Op>
{
	TPL_Group_T getInverseElement(TPL_Group_T const &x);
	
	
	axiom inverseElement(TPL_Group_Op op, TPL_Group_T x)
	{
		op(x, this->getInverseElement(x)) == this->getIdentityElement();
		op(this->getInverseElement(x), x) == this->getIdentityElement();
	}
}

concept CommutativeGroup <typename TPL_CommutativeGroup_T, typename TPL_CommutativeGroup_Op> : Group <TPL_CommutativeGroup_T, TPL_CommutativeGroup_Op>
{
	axiom commutativity(TPL_CommutativeGroup_Op op, TPL_CommutativeGroup_T a, TPL_CommutativeGroup_T b)
	{
		op(a, b) == op(b, a);
	}
}

concept Ring <typename TPL_Ring_T>
{
	requires CommutativeGroup <TPL_Ring_T, std::plus <TPL_Ring_T> >;
	requires Monoid <TPL_Ring_T, std::multiplies <TPL_Ring_T> >;


	TPL_Ring_T getAdditiveIdentity();
	
	TPL_Ring_T operator+(TPL_Ring_T const &a, TPL_Ring_T const &b);
	
	TPL_Ring_T operator-(TPL_Ring_T const &a, TPL_Ring_T const &b);
	
	TPL_Ring_T operator*(TPL_Ring_T const &a, TPL_Ring_T const &b);
	
	TPL_Ring_T operator-(TPL_Ring_T const &x)
	{
		return this->getAdditiveIdentity() - x;
	}
	
	TPL_Ring_T &operator+=(TPL_Ring_T &a, TPL_Ring_T const &b)
	{
		a = a + b;
		return a;
	}
	
	TPL_Ring_T &operator-=(TPL_Ring_T &a, TPL_Ring_T const &b)
	{
		a = a - b;
		return a;
	}
	
	TPL_Ring_T &operator*=(TPL_Ring_T &a, TPL_Ring_T const &b)
	{
		a = a * b;
		return a;
	}


	axiom consistency()
	{
		this->getAdditiveIdentity() == CommutativeGroup <TPL_Ring_T, std::plus <TPL_Ring_T> > ::getIdentityElement();
	}

	axiom distributivity(TPL_Ring_T a, TPL_Ring_T b, TPL_Ring_T c)
	{
		a * (b + c) == a * b + a * c;
		(a + b) * c == a * c + b * c;
	}
}

concept CommutativeRing <typename TPL_CommutativeRing_T> : Ring <TPL_CommutativeRing_T>
{
	axiom commutativity(TPL_CommutativeRing_T a, TPL_CommutativeRing_T b)
	{
		a * b == b * a;
	}
}

concept AssociativeRing <typename TPL_AssociativeRing_T> : Ring <TPL_AssociativeRing_T>
{
	axiom associativity(TPL_AssociativeRing_T a, TPL_AssociativeRing_T b, TPL_AssociativeRing_T c)
	{
		(a * b) * c == a * (b * c);
	}
}

concept RingWithIdentity <typename TPL_RingWithIdentity_T> : Ring <TPL_RingWithIdentity_T>
{
	requires Monoid <TPL_RingWithIdentity_T, std::multiplies <TPL_RingWithIdentity_T> >;
	
	
	TPL_RingWithIdentity_T getMultiplicativeIdentity();
	
	
	axiom consistency()
	{
		this->getMultiplicativeIdentity() == Monoid <TPL_RingWithIdentity_T, std::multiplies <TPL_RingWithIdentity_T> > ::getIdentityElement();
	}
}

concept Field <typename TPL_Field_T> : CommutativeRing <TPL_Field_T>, AssociativeRing <TPL_Field_T>, RingWithIdentity <TPL_Field_T>
{
	TPL_Field_T operator/(TPL_Field_T const &a, TPL_Field_T const &b);
	
	TPL_Field_T &operator/=(TPL_Field_T &a, TPL_Field_T const &b);


	axiom inverseElement(TPL_Field_T a, TPL_Field_T b)
	{
		b == this->getAdditiveIdentity() || (a / b) * b == a;
	}
	
	axiom hasTwoElements()
	{
		this->getMultiplicativeIdentity() != this->getAdditiveIdentity();
	}
}

/**
 * Real numbers form commutative group with ordinary "+" operation.
 */
concept_map CommutativeGroup <float, std::plus <float> >
{
	float getIdentityElement()
	{
		return 0;
	}
	
	float getInverseElement(float x)
	{
		return -x;
	}
}

/**
 * Real numbers form monoid with ordinary "*" operation.
 */
concept_map Monoid <float, std::multiplies <float> >
{
	float getIdentityElement()
	{
		return 1;
	}
}

/**
 * Real numbers form field with ordinary "+" and "*" operations.
 */
concept_map Field <float>
{
	float getMultiplicativeIdentity()
	{
		return 1;
	}
	
	float getAdditiveIdentity()
	{
		return 0;
	}
}


}


#endif
