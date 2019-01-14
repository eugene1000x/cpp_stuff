
#ifndef EUGENEJONAS__CPP_STUFF__ABSTRACT_ALGEBRA__RESIDUE_CLASS_H
#define EUGENEJONAS__CPP_STUFF__ABSTRACT_ALGEBRA__RESIDUE_CLASS_H


#include <eugenejonas/cpp_stuff/abstract_algebra/concepts.h>
#include <eugenejonas/cpp_stuff/arithm/big_int.h>

#include <cassert>

#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
#include <concepts>
#else
#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#endif


namespace eugenejonas::cpp_stuff
{


class ResidueClass
{
	private: BigInt num, mod;


	public: ResidueClass(BigInt const &num, BigInt const &mod):
			num(num % mod),
			mod(mod)
	{
		assert(this->invariant());
	}

	public: ResidueClass(ResidueClass const &other):
			num(other.num),
			mod(other.mod)
	{
		assert(this->invariant());
	}

	private: bool invariant()
	{
		assert(this->mod > 0);
		assert(this->num >= 0 && this->num < this->mod);
		return true;
	}

	public: ResidueClass &operator=(ResidueClass const &other)
	{
		this->num = other.num;
		this->mod = other.mod;
		assert(this->invariant());
		return *this;
	}

	public: ResidueClass operator+(ResidueClass const &other)
	{
		assert(other.mod == this->mod);
		ResidueClass res = other;
		res.num += this->num;
		res.num %= this->mod;
		return res;
	}
	
	public: ResidueClass operator-(ResidueClass const &other)
	{
		assert(other.mod == this->mod);
		ResidueClass res = other;
		res.num -= this->num;
		assert(res.num > -(this->mod));
		if (res.num < 0)
		{
			res.num += this->mod;
		}
		return res;
	}
	
	public: ResidueClass operator*(ResidueClass const &other)
	{
		assert(other.mod == this->mod);
		ResidueClass res = other;
		res.num *= this->num;
		res.num %= this->mod;
		return res;
	}
}

#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP

concept_map CommutativeRing <ResidueClass>
{
	//nothing
}

#endif


}


#endif
