
#ifndef EUGENEJONAS__CPP_STUFF__ARITHM__RATIONAL_NUMBER_H
#define EUGENEJONAS__CPP_STUFF__ARITHM__RATIONAL_NUMBER_H


#include <eugenejonas/cpp_stuff/arithm/big_int.h>
#include <eugenejonas/cpp_stuff/arithm/gcd.h>

#include <cassert>


namespace eugenejonas::cpp_stuff
{


class RationalNumber
{
	private: BigInt p, q;		// object represents the value p / q (numerator / denominator)


	public: RationalNumber(long p = 0, long q = 1):
			p(p),
			q(q)
	{
		assert(q != 0);
		this->normalize();
	}

	public: RationalNumber(RationalNumber const &other):
			p(other.p),
			q(other.q)
	{
		assert(this->invariant());
	}

	public: RationalNumber(BigInt const &x):
			p(x),
			q(1)
	{
		assert(this->invariant());
	}
	
	private: bool invariant()
	{
		assert(this->q > 0);
		assert(calculateGcdEuclidAlg(this->p, this->q) == 1);
		return true;
	}

	public: RationalNumber operator+(RationalNumber const &other) const
	{
		RationalNumber res = *this;
		res += other;
		return res;
	}

	public: RationalNumber operator-(RationalNumber const &other) const
	{
		RationalNumber res = *this;
		res -= other;
		return res;
	}

	public: RationalNumber operator*(RationalNumber const &other) const
	{
		RationalNumber res = *this;
		res *= other;
		return res;
	}

	public: RationalNumber operator/(RationalNumber const &other) const
	{
		assert(other != 0);
		RationalNumber res = *this;
		res /= other;
		return res;
	}

	public: bool operator==(RationalNumber const &other) const
	{
		return (other.p == this->p && other.q == this->q);
	}

	public: bool operator==(long x) const
	{
		return (*this == RationalNumber(x));
	}

	public: bool operator!=(RationalNumber const &other) const
	{
		return !(*this == other);
	}

	public: bool operator!=(long x) const
	{
		return !(*this == x);
	}

	public: RationalNumber operator-()
	{
		RationalNumber res = *this;
		res.p = -res.p;
		assert(res.invariant());
		return res;
	}
	
	public: RationalNumber &operator+=(RationalNumber const &other)
	{
		this->p *= other.q;
		this->p += (other.p * this->q);
		this->q *= other.q;
		this->normalize();
		return *this;
	}

	public: RationalNumber &operator-=(RationalNumber const &other)
	{
		this->p *= other.q;
		this->p -= (other.p * this->q);
		this->q *= other.q;
		this->normalize();
		return *this;
	}

	public: RationalNumber &operator*=(RationalNumber const &other)
	{
		this->p *= other.p;
		this->q *= other.q;
		this->normalize();
		return *this;
	}

	public: RationalNumber &operator/=(RationalNumber const &other)
	{
		assert(other != 0);
		this->p *= other.q;
		this->q *= other.p;
		this->normalize();
		return *this;
	}

	private: void normalize()
	{
		assert(this->q != 0);
		BigInt gcd = calculateGcdEuclidAlg(this->p, this->q);
		if (this->q < 0)
		{
			gcd = -gcd;
		}
		this->p /= gcd;
		this->q /= gcd;
		assert(this->invariant());
	}
}


}


#endif
