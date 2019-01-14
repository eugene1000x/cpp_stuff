
#include <eugenejonas/cpp_stuff/consumers.h>

#include <iostream>
#include <string>


using eugenejonas::cpp_stuff::Printer;

using std::cin;
using std::cout;
using std::string;


/**
 * This program prints all of the supplied command-line arguments
 * to the standard output using Printer class.
 */
int main(int argc, char **argv)
{
	Printer <string> printer(
			cout,
			"\n\nThe arguments will be printed one per row:\n",
			"\nPress enter to exit",
			"\n"
	);
	
	cout << "Arguments passed: " << argc << "\n";
	
	printer.start();
	for (int i = 0; i < argc; ++i)
	{
		printer.feed(argv[i]);
	}
	printer.finish();

	char c;
	cin.get(c);
	
	return 0;
}
