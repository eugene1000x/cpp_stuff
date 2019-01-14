
#ifndef EUGENEJONAS__CPP_STUFF__POD_CONTAINERS__POD_CONTAINERS_H
#define EUGENEJONAS__CPP_STUFF__POD_CONTAINERS__POD_CONTAINERS_H


#include <eugenejonas/cpp_stuff/orderings.h>

#include <cassert>
#include <cstddef>

#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
#include <concepts>
#else
#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#endif


namespace eugenejonas::cpp_stuff
{


/**
 * Base class for all data structures that support only POD (Plain Old Data) types,
 * which can be copied byte by byte without deep copy semantics.
 */
template <typename TPL_PodContainer_T>
#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
requires std::CopyAssignable <TPL_PodContainer_T>,
		std::CopyConstructible <TPL_PodContainer_T>,
		std::TrivialType <TPL_PodContainer_T>
#endif
class PodContainer
{
	#ifndef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
	BOOST_CONCEPT_ASSERT((boost::Assignable <TPL_PodContainer_T>));
	BOOST_CONCEPT_ASSERT((boost::CopyConstructible <TPL_PodContainer_T>));
	#endif


	protected: struct ListElement
	{
		public: TPL_PodContainer_T data;
		public: ListElement *next;
		
		
		public: ListElement(TPL_PodContainer_T data, ListElement *next):
				data(data),
				next(next)
		{
			//nothing
		}
		
		public: ListElement(TPL_PodContainer_T data):
				data(data),
				next(nullptr)
		{
			//nothing
		}
	}


	/**
	 * Creates a byte-by-byte copy of an array.
	 * 
	 * @param len Length of the array (number of elements).
	 * @return Copy of the array.
	 */
	protected: static TPL_PodContainer_T *copyBytes(const TPL_PodContainer_T *arr, std::size_t len)
	{
		char *res = new char[len * sizeof(TPL_PodContainer_T)];
		std::memcpy(res, arr, len * sizeof(TPL_PodContainer_T));
		//std::copy(arr, arr + len * sizeof(TPL_PodContainer_T), res);
		//for (std::size_t i = 0; i < len; i++)
		//{
		//	res[i] = arr[i];
		//}
		return (TPL_PodContainer_T*) res;
	}
}

/**
 * Abstract class representing a queue.
 */
template <typename TPL_Queue_T> class Queue: public PodContainer <TPL_Queue_T>
{
	public: virtual ~Queue()
	{
		//nothing
	}
	
	/**
	 * Enqueues element (places it at the end of the queue).
	 */
	public: virtual void enqueue(const TPL_Queue_T &element) = 0;
	
	/**
	 * Removes element at the head (or the front) of the queue.
	 * 
	 * @return The removed element.
	 */
	public: virtual TPL_Queue_T dequeue() = 0;
	
	/**
	 * Returns element at the head (or the front) of the queue,
	 * but doesn't remove it.
	 */
	public: virtual TPL_Queue_T peek() const = 0;
	
	public: virtual bool isEmpty() const = 0;
	
	/**
	 * Returns number of elements in the queue.
	 */
	public: virtual std::size_t getSize() const = 0;
}

/**
 * Abstract class representing a stack.
 */
template <typename TPL_Stack_T> class Stack: public PodContainer <TPL_Stack_T>
{
	public: virtual ~Stack()
	{
		//nothing
	}
	
	/**
	 * Pushes element to the top of the stack.
	 */
	public: virtual void push(const TPL_Stack_T &element) = 0;
	
	/**
	 * Removes element at the top of the stack.
	 * 
	 * @return The removed element.
	 */
	public: virtual TPL_Stack_T pop() = 0;
	
	/**
	 * Returns element at the top of the stack, but doesn't remove it.
	 */
	public: virtual TPL_Stack_T peek() const = 0;
	
	public: virtual bool isEmpty() const = 0;
	
	/**
	 * Returns number of elements in the stack.
	 */
	public: virtual std::size_t getSize() const = 0;
}

/**
 * Class representing a priority queue. The priority of elements in the
 * queue is determined by strict weak ordering relation swoCompare(a, b).
 * If swoCompare(a, b) == true, element b has greater priority than element a.
 * 
 * @param TPL_PriorityQueue_StrictWeakOrdering Functor used to compare priorities of two elements.
 */
template <typename TPL_PriorityQueue_T, class TPL_PriorityQueue_StrictWeakOrdering = std::less <TPL_PriorityQueue_T> >
#ifdef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
requires std::StrictWeakOrder <TPL_PriorityQueue_StrictWeakOrdering, TPL_PriorityQueue_T>
#endif
class PriorityQueue: public PodContainer <TPL_PriorityQueue_T>
{
	#ifndef EUGENEJONAS__CPP_STUFF__CONCEPT_CPP
	BOOST_CONCEPT_ASSERT((StrictWeakOrdering <TPL_PriorityQueue_StrictWeakOrdering, TPL_PriorityQueue_T>));
	#endif


	/**
	 * Why mutable:
	 * If TPL_PriorityQueue_StrictWeakOrdering is a class rather that function pointer,
	 * its operator() is allowed to change functor's state. This means that
	 * either swoCompare must be made mutable or invariant() must be made non-const.
	 */
	private: mutable TPL_PriorityQueue_StrictWeakOrdering swoCompare;

	/**
	 * Priority queue is represented as array of elements: arr[0..size).
	 * Element with the greatest priority is arr[0] (binary heap).
	 */
	private: TPL_PriorityQueue_T *arr;

	/**
	 * Capacity is the maximum number of elements queue can store.
	 */
	private: const std::size_t capacity;

	/**
	 * Current number of elements.
	 */
	private: std::size_t size;


	/**
	 * Constructs a new empty priority queue with limited capacity.
	 * 
	 * @param capacity Maximum number of elements queue can store.
	 * @param swoCompare Comparison object used to determine priority of
	 *		elements.
	 */
	public: PriorityQueue(std::size_t capacity, TPL_PriorityQueue_StrictWeakOrdering swoCompare = TPL_PriorityQueue_StrictWeakOrdering()):
			capacity(capacity)
	{
		this->size = 0;
		this->arr = (TPL_PriorityQueue_T*) new char[this->capacity * sizeof(TPL_PriorityQueue_T)];
		this->swoCompare = swoCompare;
		assert(this->invariant());
	}
	
	public: PriorityQueue(PriorityQueue <TPL_PriorityQueue_T, TPL_PriorityQueue_StrictWeakOrdering> const &other):
			capacity(other.capacity)
	{
		this->size = other.size;
		this->swoCompare = other.swoCompare;
		//this->arr = new TPL_PriorityQueue_T[this->capacity];
		//std::copy(other.arr, other.arr + this->capacity, this->arr);
		this->arr = PriorityQueue::copyBytes(other.arr, other.capacity);
		assert(this->invariant());
	}

	public: ~PriorityQueue()
	{
		delete[] this->arr;
	}

	private: bool invariant() const
	{
		assert(this->arr != nullptr && this->size <= this->capacity);
		
		for (std::size_t i = 0; i < this->size; i++)
		{
			std::size_t lc = PriorityQueue::getLeftChild(i), rc = PriorityQueue::getRightChild(i);
			
			if (lc < this->size)
			{
				assert(!this->swoCompare(this->arr[i], this->arr[lc]));
			}
			
			if (rc < this->size)
			{
				assert(!this->swoCompare(this->arr[i], this->arr[rc]));
			}
		}
		
		return true;
	}

	/**
	 * Adds an element with an associated priority to the queue.
	 * Queue must not be full.
	 */
	public: void insert(const TPL_PriorityQueue_T &element)
	{
		assert(this->invariant());
		assert(this->size < this->capacity);
		
		std::size_t insertPos = this->size;
		
		while (true)
		{
			if (insertPos == 0)
			{
				break;
			}
			
			std::size_t parent = PriorityQueue::getParent(insertPos);
			
			if (!this->swoCompare(this->arr[parent], element))
			{
				break;
			}
			
			this->arr[insertPos] = this->arr[parent];
			insertPos = parent;
		}
		
		this->arr[insertPos] = element;
		this->size++;
		
		assert(this->invariant());
	}

	/**
	 * Deletes element at the top of the queue (with the highest priority).
	 * Queue must not be empty.
	 * 
	 * @return The deleted element.
	 */
	public: TPL_PriorityQueue_T extract()
	{
		assert(this->invariant());
		assert(this->size > 0);
		
		TPL_PriorityQueue_T res = this->arr[0];
		this->arr[0] = this->arr[--this->size];
		
		if (this->size > 1)
		{
			heapify(this->arr, this->arr + this->size, this->arr, this->swoCompare);
		}
		
		assert(this->invariant());
		
		return res;
	}

	/**
	 * Returns element at the head of the queue (element
	 * with the highest priority), but doesn't remove it.
	 * Queue must not be empty.
	 */
	public: TPL_PriorityQueue_T peek() const
	{
		assert(this->invariant());
		assert(this->size > 0);
		return this->arr[0];
	}

	public: bool isEmpty() const
	{
		return this->size == 0;
	}

	/**
	 * Returns number of elements in the queue.
	 */
	public: std::size_t getSize() const
	{
		return this->size;
	}

	private: static std::size_t getLeftChild(std::size_t i)
	{
		return 2 * i + 1;
	}

	private: static std::size_t getRightChild(std::size_t i)
	{
		return 2 * i + 2;
	}

	private: static std::size_t getParent(std::size_t i)
	{
		assert(i > 0);
		return (i - 1) / 2;
	}
}

/**
 * Stack implementation using array.
 */
template <typename TPL_ArrayStack_T> class ArrayStack: public Stack <TPL_ArrayStack_T>
{
	private: TPL_ArrayStack_T *arr;
	private: std::size_t capacity, size;


	/**
	 * Constructs new empty stack with limited capacity.
	 * 
	 * @param capacity Maximum number of elements stack can store.
	 */
	public: ArrayStack(std::size_t capacity)
	{
		assert(capacity >= 0);
		this->arr = new TPL_ArrayStack_T[capacity];
		this->capacity = capacity;
		this->size = 0;
		assert(this->invariant());
	}

	public: ArrayStack(const ArrayStack &other)
	{
		this->arr = ArrayStack::copyBytes(other.arr, other.capacity);
		this->capacity = other.capacity;
		this->size = other.size;
		assert(this->invariant());
	}

	public: virtual ~ArrayStack()
	{
		delete[] this->arr;
	}

	private: bool invariant() const
	{
		assert(this->arr != nullptr && this->size >= 0 && this->capacity >= 0
				&& this->size <= this->capacity);
		return true;
	}

	public: void push(const TPL_ArrayStack_T &element)
	{
		assert(this->invariant());
		assert(this->size < this->capacity);
		this->arr[this->size++] = element;
	}

	public: TPL_ArrayStack_T pop()
	{
		assert(this->invariant());
		assert(this->size > 0);
		return this->arr[--this->size];
	}

	public: TPL_ArrayStack_T peek() const
	{
		assert(this->invariant());
		assert(this->size > 0);
		return this->arr[this->size - 1];
	}

	public: bool isEmpty() const
	{
		return (this->size == 0);
	}

	public: std::size_t getSize() const
	{
		return this->size;
	}
}

/**
 * Queue implementation using array.
 */
template <typename TPL_ArrayQueue_T> class ArrayQueue: public Queue <TPL_ArrayQueue_T>
{
	private: TPL_ArrayQueue_T *arr;
	private: std::size_t first, capacity, size;


	/**
	 * Constructs new empty queue with limited capacity.
	 * 
	 * @param capacity Maximum number of elements queue can store.
	 */
	public: ArrayQueue(std::size_t capacity)
	{
		assert(capacity > 0);
		this->arr = new TPL_ArrayQueue_T[capacity];
		this->capacity = capacity;
		this->first = 0;
		this->size = 0;
		assert(this->invariant());
	}

	public: ArrayQueue(ArrayQueue const &other)
	{
		this->arr = ArrayQueue::copyBytes(other.arr, other.capacity);
		this->capacity = other.capacity;
		this->first = other.first;
		this->size = other.size;
		assert(this->invariant());
	}
	
	public: virtual ~ArrayQueue()
	{
		delete[] this->arr;
	}

	private: bool invariant() const
	{
		assert(this->arr != nullptr && this->size >= 0 && this->capacity > 0
				&& this->size <= this->capacity);
		assert(this->first >= 0);
		assert(this->first < this->capacity);
		return true;
	}

	public: void enqueue(const TPL_ArrayQueue_T &element)
	{
		assert(this->invariant());
		assert(this->size < this->capacity);
		this->arr[(this->first + this->size) % this->capacity] = element;
		this->size++;
	}

	public: TPL_ArrayQueue_T dequeue()
	{
		assert(this->invariant());
		assert(this->size > 0);
		this->size--;
		assert(this->invariant());
		TPL_ArrayQueue_T element = this->arr[this->first];
		this->first = (this->first + 1) % this->capacity;
		return element;
	}

	public: TPL_ArrayQueue_T peek() const
	{
		assert(this->invariant());
		assert(this->size > 0);
		return this->arr[this->first];
	}

	/**
	 * Adds element to the head (or the front) of the queue.
	 */
	public: void pushFront(const TPL_ArrayQueue_T &element)
	{
		assert(this->invariant());
		assert(this->size < this->capacity);
		
		if (this->first == 0)
		{
			this->first = this->capacity - 1;
		}
		else
		{
			this->first = this->first - 1;
		}
		
		this->arr[this->first] = element;
		this->size++;
	}

	/**
	 * Removes element at the end of the queue.
	 * 
	 * @return The removed element.
	 */
	public: TPL_ArrayQueue_T popLast()
	{
		assert(this->invariant());
		assert(this->size > 0);
		this->size--;
		assert(this->invariant());
		TPL_ArrayQueue_T element = this->arr[(this->first + this->size) % this->capacity];
		return element;
	}

	/**
	 * Returns element at the end of the queue,
	 * but doesn't remove it.
	 */
	public: TPL_ArrayQueue_T peekLast() const
	{
		assert(this->invariant());
		assert(this->size > 0);
		return this->arr[(this->first + this->size - 1) % this->capacity];
	}

	public: bool isEmpty() const
	{
		return (this->size == 0);
	}

	public: std::size_t getSize() const
	{
		return this->size;
	}
}

/**
 * Stack implementation using linked list.
 */
template <typename TPL_ListStack_T> class ListStack: public Stack <TPL_ListStack_T>
{
	private: struct ListElement *stackptr;
	private: std::size_t size;


	public: ListStack():
			size(0),
			stackptr(nullptr)
	{
		//nothing
	}

	public: ListStack(const ListStack &other)
	{
		this->size = other.size;

		if (!other.isEmpty())
		{
			this->stackptr = new ListElement(other.stackptr->data);
			ListElement tmp1 = this->stackptr, tmp2 = other.stackptr;
			
			while (tmp2->next != nullptr)
			{
				tmp1->next = new ListElement(tmp2->next->data);
				tmp1 = tmp1->next;
				tmp2 = tmp2->next;
			}
			
			assert(tmp1->next == nullptr);
		}
		else
		{
			this->stackptr = nullptr;
		}

		assert(this->invariant());
	}

	public: virtual ~ListStack()
	{
		ListElement *tmp;
		while (this->stackptr != nullptr)
		{
			tmp = this->stackptr;
			this->stackptr = this->stackptr->next;
			delete tmp;
		}
	}

	private: bool invariant() const
	{
		assert(this->size >= 0);
		
		if (this->size > 0)
		{
			assert(this->stackptr != nullptr);
			ListElement *tmp = this->stackptr;
			while (tmp->next != nullptr)
			{
				tmp = tmp->next;
			}
		}
		else
		{
			assert(this->stackptr == nullptr);
		}
		
		return true;
	}

	public: void push(const TPL_ListStack_T &element)
	{
		assert(this->invariant());
		
		if (this->stackptr == nullptr)
		{
			this->stackptr = new ListElement(element);
		}
		else
		{
			this->stackptr = new ListElement(element, this->stackptr);
		}
		
		this->size++;
	}

	public: TPL_ListStack_T pop()
	{
		assert(this->invariant());
		assert(this->size > 0);
		
		TPL_ListStack_T element = this->stackptr->data;
		ListElement *tmp = this->stackptr;
		this->stackptr = this->stackptr->next;
		delete tmp;
		this->size--;
		
		assert(this->invariant());
		
		return element;
	}

	public: TPL_ListStack_T peek() const
	{
		assert(this->invariant());
		assert(this->size > 0);
		return this->stackptr->data;
	}

	public: bool isEmpty() const
	{
		return (this->size == 0);
	}

	public: std::size_t getSize() const
	{
		return this->size;
	}
}

/**
 * Queue implementation using linked list.
 */
template <typename TPL_ListQueue_T> class ListQueue: public Queue <TPL_ListQueue_T>
{
	private: struct ListElement *first, *last;
	private: std::size_t size;


	public: ListQueue():
			size(0),
			first(nullptr),
			last(nullptr)
	{
		//nothing
	}

	public: ListQueue(ListQueue const &other)
	{
		this->size = other.size;

		if (!other.isEmpty())
		{
			this->first = new ListElement(other.first->data);
			ListElement tmp1 = this->first, tmp2 = other.first;
			while (tmp2->next != nullptr)
			{
				tmp1->next = new ListElement(tmp2->next->data);
				tmp1 = tmp1->next;
				tmp2 = tmp2->next;
			}
			assert(tmp1->next == nullptr);
			this->last = tmp1;
		}
		else
		{
			this->first = this->last = nullptr;
		}

		assert(this->invariant());
	}

	public: virtual ~ListQueue()
	{
		ListElement *tmp;
		while (this->first != nullptr)
		{
			tmp = this->first;
			this->first = this->first->next;
			delete tmp;
		}
	}

	private: bool invariant() const
	{
		/*
		 * Note: this function does not check if there are cycles.
		 */

		assert(this->size >= 0);
		
		if (this->size == 0)
		{
			assert(this->first == nullptr && this->last == nullptr);
		}
		else if (this->size == 1)
		{
			assert(this->first != nullptr);
			assert(this->first == this->last && this->first->next == nullptr);
		}
		else
		{
			assert(this->first != nullptr && this->last != nullptr);
			ListElement *tmp = this->first;
			assert(tmp->next != nullptr);
			
			while (tmp->next != nullptr)
			{
				tmp = tmp->next;
			}
			
			assert(tmp == this->last);
		}
		
		return true;
	}

	public: void enqueue(const TPL_ListQueue_T &element)
	{
		assert(this->invariant());
		
		if (this->last == nullptr)
		{
			this->first = this->last = new ListElement(element);
		}
		else
		{
			this->last = this->last->next = new ListElement(element);
		}
		
		this->size++;
		assert(this->invariant());
	}

	public: TPL_ListQueue_T dequeue()
	{
		assert(this->invariant());
		assert(this->size > 0);
		
		this->size--;
		
		ListElement *tmp = this->first;
		TPL_ListQueue_T element = this->first->data;
		this->first = this->first->next;
		
		if (this->first == nullptr)
		{
			this->last = nullptr;
		}
		
		delete tmp;
		
		assert(this->invariant());
		return element;
	}

	public: TPL_ListQueue_T peek() const
	{
		assert(this->invariant());
		assert(this->size > 0);
		return this->first->data;
	}

	public: bool isEmpty() const
	{
		return (this->size == 0);
	}

	public: std::size_t getSize() const
	{
		return this->size;
	}
}


}


#endif
