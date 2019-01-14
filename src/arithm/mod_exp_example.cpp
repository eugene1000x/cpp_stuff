
#include <eugenejonas/cpp_stuff/arithm/arithm_functions.h>
#include <eugenejonas/cpp_stuff/arithm/big_int.h>

#include <iostream>
#include <string>


extern "C"
{
	typedef long* verylong;
	long zsread(char *str, verylong *a);
	void zexpmod(verylong a, verylong e, verylong n, verylong *b);
	long zwrite(verylong a);
	long zwriteln(verylong a);
	void zfree(verylong *x);
}


using eugenejonas::cpp_stuff::BigInt;
using eugenejonas::cpp_stuff::modExp;

using std::cin;
using std::cout;
using std::string;


/**
 * This program calculates a ^ b mod c and prints results
 * calculated using cpp_stuff function and the results
 * calculated using Freelip functions.
 */
int main()
{
	BigInt a1, b1, c1, res1;
	verylong a2 = 0, b2 = 0, c2 = 0, res2 = 0;

	string s;		// string read from standard input

	do
	{
		cout << "Enter a: ";
		cin >> s;
		a1.read(s);
		zsread((char*) s.c_str(), &a2);

		do
		{
			cout << "Enter b: ";
			cin >> s;
			b1.read(s);
			zsread((char*) s.c_str(), &b2);
			
			if (b1 < 0)
			{
				cout << "Error: b must be non-negative!\n";
			}
		}
		while (b1 < 0);
		
		cout << "Enter c: ";
		cin >> s;
		c1.read(s);
		zsread((char*) s.c_str(), &c2);
		
		res1 = modExp(a1, b1, c1);
		zexpmod(a2, b2, c2, &res2);

		cout << "cpp_stuff: ";
		a1.write();
		cout << " ^ ";
		b1.write();
		cout << " mod ";
		c1.write();
		cout << " == ";
		res1.writeln();

		cout << "Freelip: ";
		zwrite(a2);
		cout << " ^ ";
		zwrite(b2);
		cout << " mod ";
		zwrite(c2);
		cout << " == ";
		zwriteln(res2);
	}
	while (true);

	zfree(&a2);
	zfree(&b2);
	zfree(&c2);

	return 0;
}
