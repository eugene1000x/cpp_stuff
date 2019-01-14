
#ifndef EUGENEJONAS__CPP_STUFF__CONSUMERS_H
#define EUGENEJONAS__CPP_STUFF__CONSUMERS_H


#include <iostream>
#include <string>
#include <vector>

#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
#include <concepts>
#else
#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#endif


namespace eugenejonas::cpp_stuff
{


/**
 * Interface for classes that consume elements of some type, one by one.
 */
template <typename TPL_Consumer_T> class Consumer
{
	/**
	 * Signal the start of element sequence.
	 * Implementations may or may not support starting a new sequence with the
	 * same consumer object after the previous sequence was finished.
	 */
	public: virtual void start() = 0;

	public: virtual void feed(TPL_Consumer_T const &element) = 0;

	/**
	 * Signal the end of element sequence.
	 */
	public: virtual void finish() = 0;
}

/**
 * This class is used to count the number of produced elements.
 */
template <typename TPL_Counter_T> class Counter: public Consumer <TPL_Counter_T>
{
	private: int count;


	public: Counter()
	{
		//nothing
	}

	public: void start()
	{
		this->count = 0;
	}

	public: void feed(TPL_Counter_T const &element)
	{
		this->count++;
	}

	public: void finish()
	{
		//nothing
	}

	public: int getCount()
	{
		return this->count;
	}
}

#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP

auto concept OutputStreamable <typename TPL_OutputStreamable_T>
{
	std::ostream &operator<<(std::ostream &outputStream, const TPL_OutputStreamable_T &x);
}

#else

template <typename TPL_OutputStreamable_T> struct OutputStreamable
{
	BOOST_CONCEPT_USAGE(OutputStreamable)
	{
		std::cout << this->x;
	}
	
	
	private: TPL_OutputStreamable_T const x;
}

#endif

/**
 * This class implements the Consumer interface
 * and prints all elements to the specified std::ostream.
 */
template <typename TPL_Printer_T>
#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
requires OutputStreamable <TPL_Printer_T>
#endif
class Printer: public Consumer <TPL_Printer_T>
{
	#ifndef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
	BOOST_CONCEPT_ASSERT((OutputStreamable <TPL_Printer_T>));
	#endif


	private: std::ostream &outputStream;
	private: const std::string before, after, delim;
	private: bool isEmpty;


	/**
	 * @param delim What is printed between the elements.
	 */
	public: Printer(std::ostream &outputStream, const std::string &before = "Printing...\n", const std::string &after = "\nFinished printing\n", const std::string &delim = "\n"):
			outputStream(outputStream),
			before(before),
			after(after),
			delim(delim),
			isEmpty(true)
	{
		//nothing
	}

	public: void start()
	{
		this->outputStream << this->before;
	}

	public: void feed(TPL_Printer_T const &element)
	{
		if (this->isEmpty == false)
		{
			this->outputStream << this->delim;
		}
		this->outputStream << element;
		this->isEmpty = false;
	}

	public: void finish()
	{
		this->outputStream << this->after;
	}
}

/**
 * This class implements Consumer interface and collects elements into std::vector.
 */
template <typename TPL_Collector_T>
#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
requires std::CopyAssignable <TPL_Collector_T>,
		std::CopyConstructible <TPL_Collector_T>
#endif
class Collector: public Consumer <TPL_Collector_T>
{
	#ifndef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
	BOOST_CONCEPT_ASSERT((boost::Assignable <TPL_Collector_T>));
	BOOST_CONCEPT_ASSERT((boost::CopyConstructible <TPL_Collector_T>));
	#endif


	private: std::vector <TPL_Collector_T> vector;


	public: Collector()
	{
		//nothing
	}

	/**
	 * Supports starting new sequence after the previous one was finished.
	 */
	public: void start()
	{
		this->vector.clear();
	}

	public: void feed(TPL_Collector_T const &element)
	{
		this->vector.insert(this->vector.end(), element);
	}

	public: void finish()
	{
		//nothing
	}

	/**
	 * Returns vector of all elements in the same order in which they were fed.
	 */
	public: std::vector <TPL_Collector_T> const &getElements()
	{
		return this->vector;
	}
}


}


#endif
