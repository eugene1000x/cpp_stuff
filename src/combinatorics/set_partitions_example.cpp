
#include <eugenejonas/cpp_stuff/combinatorics/generators.h>
#include <eugenejonas/cpp_stuff/consumers.h>

#include <iostream>
#include <vector>


using eugenejonas::cpp_stuff::Collector;
using eugenejonas::cpp_stuff::Counter;
using eugenejonas::cpp_stuff::Printer;
using eugenejonas::cpp_stuff::SetPartitionGenerator;

using std::cin;
using std::cout;
using std::vector;


int main()
{
	const int length = 7;



	// test printer
	
	Printer <SetPartitionGenerator::SetPartition> printer(cout);
	SetPartitionGenerator(&printer, length);



	// test collector
	
	cout << "\n";
	
	Collector <SetPartitionGenerator::SetPartition, vector <SetPartitionGenerator::SetPartition> > collector;
	SetPartitionGenerator(&collector, length);
	
	cout << "Printing vector elements...\n";
	
	for (vector <SetPartitionGenerator::SetPartition> ::const_iterator it = collector.getElements().begin(); it != collector.getElements().end(); ++it)
	{
		cout << *it << "\n";
	}
	
	cout << "Vector length: " << collector.getElements().size() << "\n";



	// test counter
	
	Counter <SetPartitionGenerator::SetPartition> c;
	SetPartitionGenerator(&c, length);
	
	cout << "Total number of set partitions: " << c.getCount() << "\n";



	return 0;
}
