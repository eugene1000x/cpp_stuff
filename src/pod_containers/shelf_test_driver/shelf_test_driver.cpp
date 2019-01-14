
#include <eugenejonas/cpp_stuff/pod_containers/shelf.h>

#include <cstdint>
#include <ostream>

#ifdef EUGENEJONAS__CPP_STUFF__SHELF_STREAM_IO
#include <fstream>
#else
#include <cstdio>
#endif


/**
 * Test driver for class Shelf. It uses format of test cases as given in the
 * original task from the Latvian Olympiads in Informatics. This program reads
 * input file "shelf.dat", calls methods of class Shelf and writes output to file
 * "shelf.rez".
 *
 * Preprocessor macro definitions:
 *
 * EUGENEJONAS__CPP_STUFF__SHELF_STREAM_IO - if defined, C++ style I/O (<fstream>) will be used.
 * If not defined, C style I/O (<cstdio> and "fscanf") will be used.
 */
int main(int argc, char **argv)
{
	#ifdef EUGENEJONAS__CPP_STUFF__SHELF_STREAM_IO
	
	
	std::fstream fin("./shelf.dat", ios::in);
	std::fstream fout("./shelf.rez", ios::out);
	
	int32_t pos, count;
	int n;
	char c;
	eugenejonas::cpp_stuff::Shelf <char> shelf;
	
	fin >> n;
	
	for (int i = 0; i < n; ++i)
	{
		fin >> c;
		
		if (c == '?')
		{
			fin >> pos;
			const char *p = shelf.poll(pos - 1);
			
			if (p == nullptr)
			{
				fout << "." << "\n";
			}
			else
			{
				fout << *p << "\n";
			}
		}
		else
		{
			fin >> count;
			
			if (count > 0)
			{
				shelf.add(c, count);
			}
			else
			{
				shelf.remove(c, -count);
			}
		}
	}
	
	fin.close();
	fout.close();
	
	
	#else
	
	
	FILE *fin = std::fopen("./shelf.dat", "r"), *fout = std::fopen("./shelf.rez", "w");
	
	int32_t m;
	int n;
	char c;
	eugenejonas::cpp_stuff::Shelf <char> shelf;
	
	std::fscanf(fin, "%d\n", &n);
	
	for (int i = 0; i < n; ++i)
	{
		std::fscanf(fin, "%c %d\n", &c, &m);
		
		if (c == '?')
		{
			const char *p = shelf.poll(m - 1);
			
			if (p == nullptr)
			{
				std::fprintf(fout, ".\n");
			}
			else
			{
				std::fprintf(fout, "%c\n", *p);
			}
		}
		else
		{
			if (m > 0)
			{
				shelf.add(c, m);
			}
			else
			{
				shelf.remove(c, -m);
			}
		}
	}
	
	std::fclose(fin);
	std::fclose(fout);
	
	
	#endif
	

	return 0;
}
