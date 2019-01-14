
#ifndef EUGENEJONAS__CPP_STUFF__COMBINATORICS__GENERATORS_H
#define EUGENEJONAS__CPP_STUFF__COMBINATORICS__GENERATORS_H


#include <eugenejonas/cpp_stuff/combinatorics/permutation.h>
#include <eugenejonas/cpp_stuff/consumers.h>

#include <algorithm>
#include <ostream>
#include <vector>


namespace eugenejonas::cpp_stuff
{


/**
 * Generates all partitions of set [n], where n is non-negative integer.
 */
class SetPartitionGenerator
{
	/**
	 * This class represents partition of set [n].
	 */
	public: class SetPartition: private std::vector <int>
	{
		private: friend class SetPartitionGenerator;
		private: friend std::ostream &operator<<(std::ostream &os, SetPartitionGenerator::SetPartition const &setPartition);


		/*
		 * Partition of set [n] is represented as vector <int>, where vector[k]
		 * denotes the block in which element <k + 1> is placed. Vector
		 * elements (blocks) are enumerated starting from 1.
		 */


		public: SetPartition(int n):
				std::vector <int> (n)
		{
			//nothing
		}
	}
	
	
	private: SetPartition partition;
	private: Consumer <SetPartition> *consumer;


	/**
	 * Constructor that does the work.
	 * 
	 * @param n Cardinality of the set, n >= 0.
	 */
	public: SetPartitionGenerator(Consumer <SetPartition> *consumer, int n):
			partition(n)
	{
		assert(n >= 0);
		
		this->consumer = consumer;
		this->consumer->start();
		this->generate(0, 1);
	}

	/**
	 * Destructor that sends "finish" message to the consumer.
	 */
	public: ~SetPartitionGenerator()
	{
		this->consumer->finish();
	}

	private: void generate(int i, int j)
	{
		if (i == this->partition.size())
		{
			return this->consumer->feed(this->partition);
		}
		
		for (int block = 1; block <= j; block++)
		{
			this->partition.at(i) = block;
			
			if (block == j)
			{
				this->generate(i + 1, j + 1);
			}
			else
			{
				this->generate(i + 1, j);
			}
		}
	}
}

/**
 * Prints set partition.
 */
std::ostream &operator<<(std::ostream &os, SetPartitionGenerator::SetPartition const &setPartition)
{
	int blockCount = setPartition.empty() ? 0 : *std::max_element(setPartition.begin(), setPartition.end());

	// blocks are enumerated starting from 1

	for (int i = 1; i <= blockCount; i++)
	{
		for (int j = 0; j < setPartition.size(); j++)
		{
			if (setPartition.at(j) == i)
			{
				os << (j + 1);
				os << "";
			}
		}
		
		os << "|";
	}
	
	return os;
}

/**
 * Generates all n-permutations. Every permutation is generated once, in no particular order.
 */
class PermutationGenerator
{
	private: Consumer <Permutation> *consumer;
	private: Permutation permutation;


	/**
	 * Constructor that does the work.
	 * 
	 * @param n Length of permutations, n >= 0.
	 * @param consumer Consumer of permutation sequence.
	 */
	public: PermutationGenerator(Consumer <Permutation> *consumer, int n):
			permutation(n)
	{
		assert(n >= 0);
		
		this->consumer = consumer;
		this->consumer->start();
		this->permute(0);
	}

	/**
	 * Destructor that sends "finish" message to the consumer.
	 */
	public: ~PermutationGenerator()
	{
		this->consumer->finish();
	}

	private: void permute(int start)
	{
		assert(this->permutation.getLength() >= start);
		assert(start >= 0);
		
		
		// University of Exeter permutation algorithm

		if (start == this->permutation.getLength())
		{
			return this->consumer->feed(this->permutation);
		}
		
		for (int i = start; i < this->permutation.getLength(); i++)
		{
			this->permutation.swap(start, i);
			
			//if (start < this->permutation.getLength() - 1)
			//{
			//	this->permutation.swap(this->permutation.getLength() - 1, start + 1);
			//}
			
			this->permute(start + 1);
			
			//if (start < this->permutation.getLength() - 1)
			//{
			//	this->permutation.swap(this->permutation.getLength() - 1, start + 1);
			//}
			
			this->permutation.swap(start, i);
		}
	}
}


}


#endif
