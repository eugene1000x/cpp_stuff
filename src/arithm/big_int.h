
#ifndef EUGENEJONAS__CPP_STUFF__ARITHM__BIGINT_H
#define EUGENEJONAS__CPP_STUFF__ARITHM__BIGINT_H


#include <eugenejonas/cpp_stuff/error_handling.h>

#include <cassert>
#include <string>


namespace eugenejonas::cpp_stuff
{


//Note: Freelip's modular exponentiation functions (zexpmod, zsexpmod, z2expmod, zexpmods)
//incorrectly calculate a ^ 0 % 1 and a ^ 0 % (-1). They return 1 (for every a) instead of 0.


extern "C"
{
	typedef long* verylong;
	void zintoz(long d, verylong *a);
	long zsread(char *str, verylong *a);
	void zfree(verylong *x);
	long zcompare(verylong a, verylong b);
	long zscompare(verylong a, long b);
	void zadd(verylong a, verylong b, verylong *c);
	void zsub(verylong a, verylong b, verylong *c);
	void zmul(verylong a, verylong b, verylong *c);
	void zdiv(verylong a, verylong b, verylong *q, verylong *r);
	long ziszero(verylong a);
	void zmod(verylong a, verylong b, verylong *r);
	void zsadd(verylong a, long d, verylong *b);
	void zsmul(verylong a, long d, verylong *b);
	long zsdiv(verylong a, long d, verylong *b);
	long zsmod(verylong a, long d);
	void znegate(verylong *a);
	void zcopy(verylong a, verylong *b);
	void zmulin(verylong a, verylong *b);
	void zsqin(verylong *a);
	long zwrite(verylong a);
	long zwriteln(verylong a);
	long zread(verylong *a);
	void zabs(verylong *a);
}


/**
 * Wrapper for the type "verylong" from FreeLip library.
 * Handles memory management; all operations implement true value semantics
 * in contrast to FreeLip's reference semantics.
 * "verylong" type is just pointer to long and it can be
 * reallocated during the lifetime of the object.
 *
 * Example problems:
 * 

	#include <lip.h>
	

	verylong a = 0;
	zintoz(12323323, &a);
	verylong b = a;
	zsqin(&b);					// reallocation may happen

	// a points to garbage

	// need to call zfree:
	zfree(&b);

 * 
 * With wrapper:
 * 

	BigInt a(12323323);
	BigInt b = a;
	b *= b;

 * 
 */
class BigInt
{
	/**
	 * Exception that is thrown if string format is incorrect.
	 */
	public: class FormatException: public ExpectedException
	{
		//nothing
	}
	
	
	/*
	 * Implementation of mod and div operators
	 *
	 * FreeLip functions "zsdiv", "zdiv", "zsmod", "zmod"
	 * produce following results:
	 *
	 * 12 / 5 == 2, 12 % 5 == 2
	 * 12 / (-5) == -3, 12 % (-5) == -3
	 * (-12) / 5 == -3, (-12) % 5 == 3
	 * (-12) / (-5) == 2, (-12) % (-5) == -2
	 *
	 * To reproduce:
	
		#include <iostream>
	
	
		extern "C"
		{
			typedef long* verylong;
			void zintoz(long d, verylong *a);
			long zsdiv(verylong a, long d, verylong *b);
			long zswrite(char *str, verylong a);
			void zfree(verylong *x);
		}
	
	
		using std::cout;
	
	
		int main(int argc, char **argv)
		{
			verylong a = 0;
			verylong b = 0;
			long c = 0;
			char s[3];
			cout << "\n";
	
			zintoz(12, &a);
			c = zsdiv(a, 5, &b);
			zswrite(s, b);
			cout << "zsdiv: 12 / 5 == " << s << "; 12 % 5 == " << c << "\n";
			
			zintoz(12, &a);
			c = zsdiv(a, -5, &b);
			zswrite(s, b);
			cout << "zsdiv: 12 / (-5) == " << s << "; 12 % (-5) == " << c << "\n";
			
			zintoz(-12, &a);
			c = zsdiv(a, 5, &b);
			zswrite(s, b);
			cout << "zsdiv: (-12) / 5 == " << s << "; (-12) % 5 == " << c << "\n";
			
			zintoz(-12, &a);
			c = zsdiv(a, -5, &b);
			zswrite(s, b);
			cout << "zsdiv: (-12) / (-5) == " << s << "; (-12) % (-5) == " << c << "\n";
	
			zfree(&a);
			zfree(&b);
	
			return 0;
		}
	
	 * BigInt mod operations must produce non-negative
	 * remainder (and div operations must be consistent with that)
	 * as do functions myMod and myDiv.
	 *
	 *
	 * Input same as output problem
	 *
	 * When implementing operations, must correctly handle that
	 * some FreeLip operations allow input to be the same as output,
	 * but some do not.
	 */
	

	private: verylong int;


	public: BigInt(long n = 0):
			int(0)
	{
		zintoz(n, &this->int);
	}

	/**
	 * Constructs a new BigInt object from a string.
	 * 
	 * @throws FormatException If string format is incorrect.
	 */
	public: BigInt(const std::string &str):
			int(0)
	{
		this->read(str);
	}

	public: BigInt(BigInt const &other):
			int(0)
	{
		*this = other;
	}

	public: ~BigInt()
	{
		zfree(&this->int);
	}

	public: bool operator==(BigInt const &other) const
	{
		return zcompare(this->int, other.int) == 0;
	}
	public: bool operator==(long other) const
	{
		return zscompare(this->int, other) == 0;
	}
	public: bool operator!=(BigInt const &other) const
	{
		return zcompare(this->int, other.int) != 0;
	}
	public: bool operator!=(long other) const
	{
		return zscompare(this->int, other) != 0;
	}
	public: bool operator<(BigInt const &other) const
	{
		return zcompare(this->int, other.int) < 0;
	}
	public: bool operator<(long other) const;
	{
		return zscompare(this->int, other) < 0;
	}
	public: bool operator>(BigInt const &other) const
	{
		return zcompare(this->int, other.int) > 0;
	}
	public: bool operator>(long other) const
	{
		return zscompare(this->int, other) > 0;
	}
	public: bool operator<=(BigInt const &other) const
	{
		return zcompare(this->int, other.int) <= 0;
	}
	public: bool operator<=(long other) const
	{
		return zscompare(this->int, other) <= 0;
	}
	public: bool operator>=(BigInt const &other) const
	{
		return zcompare(this->int, other.int) >= 0;
	}
	public: bool operator>=(long other) const
	{
		return zscompare(this->int, other) >= 0;
	}

	/**
	 * The "...=" versions of operators return the object which they
	 * have been applied to ("this").
	 * Division operators throw away remainder.
	 * 
	 * Div and mod operators work the same way as functions in div_mod.h:
	 * 1) operators "%", "%=" always produce non-negative remainder
	 *		(and operators "/", "/=" are consistent with that)
	 * 2) rounding policy of operators "/", "/=" is the same
	 * 
	 * Behaviour of operators "/", "%", "/=", "%=" is
	 * undefined if divisor is zero.
	 */
	public: BigInt operator+(BigInt const &other) const
	{
		BigInt res;
		zadd(other.int, this->int, &(res.int));				// output can be input
		return res;
	}
	public: BigInt operator+(long other) const
	{
		BigInt res;
		zsadd(this->int, other, &(res.int));
		return res;
	}
	public: BigInt operator-(BigInt const &other) const
	{
		BigInt res;
		zsub(this->int, other.int, &(res.int));				// output can be input
		return res;
	}
	public: BigInt operator-(long other) const
	{
		BigInt res;
		zsadd(this->int, -other, &(res.int));
		return res;
	}
	public: BigInt operator*(BigInt const &other) const
	{
		BigInt res;
		zmul(other.int, this->int, &(res.int));				// output cannot be input
		return res;
	}
	public: BigInt operator*(long other) const
	{
		BigInt res;
		zsmul(this->int, other, &(res.int));
		return res;
	}
	public: BigInt operator/(BigInt const &other) const
	{
		BigInt res;
		if (other < 0)
		{
			verylong tmp = 0;
			zdiv(this->int, other.int, &(res.int), &tmp);	// output can be input
			if (!ziszero(tmp))
			{
				res += 1;
			}
		}
		else
		{
			verylong tmp = 0;
			zdiv(this->int, other.int, &(res.int), &tmp);	// output can be input
		}
		return res;
	}
	public: BigInt operator/(long other) const
	{
		BigInt res;
		if (other < 0)
		{
			long tmp = zsdiv(this->int, other, &(res.int));		// output can be input
			if (tmp != 0)
			{
				res += 1;
			}
		}
		else
		{
			zsdiv(this->int, other, &(res.int));					// output can be input
		}
		return res;
	}
	public: BigInt operator%(BigInt const &other) const
	{
		BigInt res;
		if (other < 0)
		{
			zmod(this->int, (-other).int, &(res.int));
		}
		else
		{
			zmod(this->int, other.int, &(res.int));					// output can be input
		}
		return res;
	}
	public: BigInt operator%(long other) const
	{
		if (other < 0)
		{
			return zsmod(this->int, -other);				// output can be input
		}
		else
		{
			return zsmod(this->int, other);				// output can be input
		}
	}
	public: BigInt operator-() const
	{
		BigInt res = *this;
		znegate(&res.int);
		return res;
	}
	public: BigInt &operator=(BigInt const &other)
	{
		zcopy(other.int, &this->int);
		return *this;
	}
	public: BigInt &operator=(long other)
	{
		zintoz(other, &this->int);
		return *this;
	}
	public: BigInt &operator+=(BigInt const &other)
	{
		zadd(other.int, this->int, &this->int);
		return *this;
	}
	public: BigInt &operator+=(long other)
	{
		zsadd(this->int, other, &this->int);
		return *this;
	}
	public: BigInt &operator-=(BigInt const &other)
	{
		zsub(this->int, other.int, &this->int);
		return *this;
	}
	public: BigInt &operator-=(long other)
	{
		return *this += -other;
	}
	public: BigInt &operator*=(BigInt const &other)
	{
		if (this != &other)
		{
			zmulin(other.int, &this->int);				// output cannot be input
		}
		else
		{
			zsqin(&this->int);
		}
		return *this;
	}
	public: BigInt &operator*=(long other)
	{
		zsmul(this->int, other, &this->int);
		return *this;
	}
	public: BigInt &operator/=(BigInt const &other)
	{
		if (this == &other)
		{
			*this = 1;
		}
		else if (other < 0)
		{
			verylong tmp = 0;
			zdiv(this->int, other.int, &this->int, &tmp);			// output can be input
			if (!ziszero(tmp))
			{
				*this += 1;
			}
		}
		else
		{
			verylong tmp = 0;
			zdiv(this->int, other.int, &this->int, &tmp);			// output can be input
		}
		return *this;
	}
	public: BigInt &operator/=(long other)
	{
		if (other < 0)
		{
			long tmp = zsdiv(this->int, other, &this->int);
			if (tmp != 0)
			{
				*this += 1;
			}
		}
		else
		{
			zsdiv(this->int, other, &this->int);
		}
		return *this;
	}
	public: BigInt &operator%=(BigInt const &other)
	{
		if (other < 0)
		{
			zmod(this->int, (-other).int, &this->int);
		}
		else
		{
			zmod(this->int, other.int, &this->int);				// output can be input
		}
		return *this;
	}
	public: BigInt &operator%=(long other)
	{
		if (other < 0)
		{
			*this = zsmod(this->int, -other);
		}
		else
		{
			*this = zsmod(this->int, other);				// output can be input
		}
		return *this;
	}

	/**
	 * Writes/reads number to/from standard input/output or string.
	 */
	public: void write() const
	{
		zwrite(this->int);
	}
	public: void writeln() const
	{
		zwriteln(this->int);
	}
	/**
	 * @throws FormatException If input format is incorrect.
	 */
	public: void read()
	{
		zread(&this->int);
	}
	public: void read(const std::string &str)
	{
		//using hack converting to pointer to non-const char.
		if (!zsread((char*) str.c_str(), &this->int))
		{
			throw FormatException();
		}
	}

	public: BigInt abs()
	{
		BigInt res = *this;
		zabs(&res.int);
		return res;
	}
}

bool operator==(long a, BigInt const &b)
{
	return b == a;
}
bool operator!=(long a, BigInt const &b)
{
	return b != a;
}
bool operator<(long a, BigInt const &b)
{
	return b > a;
}
bool operator>(long a, BigInt const &b)
{
	return b < a;
}
bool operator<=(long a, BigInt const &b)
{
	return b >= a;
}
bool operator>=(long a, BigInt const &b)
{
	return b <= a;
}

/**
 * These operators have the same semantics as operators defined in class.
 */
BigInt operator+(long a, BigInt const &b)
{
	return b + a;
}
BigInt operator-(long a, BigInt const &b)
{
	return BigInt(a) - b;
}
BigInt operator*(long a, BigInt const &b)
{
	return b * a;
}
BigInt operator/(long a, BigInt const &b)
{
	return BigInt(a) / b;
}
BigInt operator%(long a, BigInt const &b)
{
	return BigInt(a) % b;
}


}


#endif
