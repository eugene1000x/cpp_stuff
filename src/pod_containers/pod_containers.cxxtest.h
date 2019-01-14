
#include <eugenejonas/cpp_stuff/orderings.h>
#include <eugenejonas/cpp_stuff/pod_containers/pod_containers.h>
#include <eugenejonas/cpp_stuff/sort.h>

#include <algorithm>
#include <string>

#include <cxxtest/TestSuite.h>


namespace eugenejonas::cpp_stuff
{


using std::string;


class UnitTest_PriorityQueue: public CxxTest::TestSuite
{
	public: void test_with_primitive_types()
	{
		const int capacity = 10;
		int arr[capacity] = {4, 7, -9, 1, 8, 12, 100, 15, 56, -29};
		PriorityQueue <int> queue(capacity);
		
		for (int i = 0; i < capacity; i++)
		{
			queue.insert(arr[i]);
		}
		
		std::sort(arr, arr + capacity);
		
		for (int i = capacity - 1; i >= 0; i--)
		{
			TS_ASSERT_EQUALS(arr[i], queue.peek());
			TS_ASSERT_EQUALS(arr[i], queue.extract());
		}
		
		TS_ASSERT(queue.isEmpty());
	}

	public: void test_with_pointers_to_objects()
	{
		string str1("abc"), str2("bc"), str3("c");
		PriorityQueue <string*, bool(*)(const string *str1, const string *str2)> queue(3, compareStrings);
		
		queue.insert(&str1);
		queue.insert(&str2);
		queue.insert(&str3);
		
		TS_ASSERT_EQUALS(&str3, queue.peek());
		TS_ASSERT_EQUALS(&str3, queue.extract());
		TS_ASSERT_EQUALS(&str2, queue.peek());
		TS_ASSERT_EQUALS(&str2, queue.extract());
		TS_ASSERT_EQUALS(&str1, queue.peek());
		TS_ASSERT_EQUALS(&str1, queue.extract());
		TS_ASSERT(queue.isEmpty());
	}
}

class UnitTest_ArrayStack: public CxxTest::TestSuite
{
	public: void test_with_primitive_types()
	{
		const int capacity = 10;
		int arr[capacity] = {4, 7, -9, 1, 8, 12, 100, 15, 56, -29};
		ArrayStack <int> stack(capacity);
		
		for (int i = 0; i < capacity; i++)
		{
			stack.push(arr[i]);
		}
		
		for (int i = capacity - 1; i >= 0; i--)
		{
			TS_ASSERT_EQUALS(arr[i], stack.peek());
			TS_ASSERT_EQUALS(arr[i], stack.pop());
		}
		
		TS_ASSERT(stack.isEmpty());
	}

	public: void test_with_pointers_to_objects()
	{
		string str1("abc"), str2("bc"), str3("c");
		ArrayStack <string*> stack(3);
		
		stack.push(&str1);
		stack.push(&str2);
		stack.push(&str3);
		
		TS_ASSERT_EQUALS(&str3, stack.peek());
		TS_ASSERT_EQUALS(&str3, stack.pop());
		TS_ASSERT_EQUALS(&str2, stack.peek());
		TS_ASSERT_EQUALS(&str2, stack.pop());
		TS_ASSERT_EQUALS(&str1, stack.peek());
		TS_ASSERT_EQUALS(&str1, stack.pop());
		TS_ASSERT(stack.isEmpty());
	}
}

class UnitTest_ArrayQueue: public CxxTest::TestSuite
{
	public: void test_with_primitive_types()
	{
		const int capacity = 10;
		int arr[capacity] = {4, 7, -9, 1, 8, 12, 100, 15, 56, -29};
		ArrayQueue <int> queue(capacity);
		
		for (int i = 0; i < capacity; i++)
		{
			queue.enqueue(arr[i]);
		}
		
		for (int i = 0; i < capacity; i++)
		{
			TS_ASSERT_EQUALS(arr[i], queue.peek());
			TS_ASSERT_EQUALS(arr[i], queue.dequeue());
		}
		
		TS_ASSERT(queue.isEmpty());
	}

	public: void test_with_pointers_to_objects()
	{
		string str1("abc"), str2("bc"), str3("c");
		ArrayQueue <string*> queue(3);
		
		queue.enqueue(&str1);
		queue.enqueue(&str2);
		queue.enqueue(&str3);
		
		TS_ASSERT_EQUALS(&str1, queue.peek());
		TS_ASSERT_EQUALS(&str1, queue.dequeue());
		TS_ASSERT_EQUALS(&str2, queue.peek());
		TS_ASSERT_EQUALS(&str2, queue.dequeue());
		TS_ASSERT_EQUALS(&str3, queue.peek());
		TS_ASSERT_EQUALS(&str3, queue.dequeue());
		TS_ASSERT(queue.isEmpty());
	}

	public: void test_as_deque()
	{
		const int capacity = 10;
		int arr[capacity] = {4, 7, -9, 1, 8, 12, 100, 15, 56, -29};
		ArrayQueue <int> queue(capacity);
		
		for (int i = capacity / 2 - 1; i >= 0; i--)
		{
			queue.pushFront(arr[i]);
		}
			
		for (int i = capacity / 2; i < capacity; i++)
		{
			queue.enqueue(arr[i]);
		}
		
		for (int i = 0; i < capacity; i++)
		{
			TS_ASSERT_EQUALS(arr[i], queue.peek());
			TS_ASSERT_EQUALS(arr[i], queue.dequeue());
		}
		
		TS_ASSERT(queue.isEmpty());
	}
}

class UnitTest_ListStack: public CxxTest::TestSuite
{
	public: void test_with_primitive_types()
	{
		const int capacity = 10;
		int arr[capacity] = {4, 7, -9, 1, 8, 12, 100, 15, 56, -29};
		ListStack <int> stack;
		
		for (int i = 0; i < capacity; i++)
		{
			stack.push(arr[i]);
		}
		
		for (int i = capacity - 1; i >= 0; i--)
		{
			TS_ASSERT_EQUALS(arr[i], stack.peek());
			TS_ASSERT_EQUALS(arr[i], stack.pop());
		}
		
		TS_ASSERT(stack.isEmpty());
	}

	public: void test_with_pointers_to_objects()
	{
		string str1("abc"), str2("bc"), str3("c");
		ListStack <string*> stack;
		
		stack.push(&str1);
		stack.push(&str2);
		stack.push(&str3);
		
		TS_ASSERT_EQUALS(&str3, stack.peek());
		TS_ASSERT_EQUALS(&str3, stack.pop());
		TS_ASSERT_EQUALS(&str2, stack.peek());
		TS_ASSERT_EQUALS(&str2, stack.pop());
		TS_ASSERT_EQUALS(&str1, stack.peek());
		TS_ASSERT_EQUALS(&str1, stack.pop());
		TS_ASSERT(stack.isEmpty());
	}
}

class UnitTest_ListQueue: public CxxTest::TestSuite
{
	public: void test_with_primitive_types()
	{
		const int capacity = 10;
		int arr[capacity] = {4, 7, -9, 1, 8, 12, 100, 15, 56, -29};
		ListQueue <int> queue;
		
		for (int i = 0; i < capacity; i++)
		{
			queue.enqueue(arr[i]);
		}
		
		for (int i = 0; i < capacity; i++)
		{
			TS_ASSERT_EQUALS(arr[i], queue.peek());
			TS_ASSERT_EQUALS(arr[i], queue.dequeue());
		}
		
		TS_ASSERT(queue.isEmpty());
	}

	public: void test_with_pointers_to_objects()
	{
		string str1("abc"), str2("bc"), str3("c");
		ListQueue <string*> queue;
		
		queue.enqueue(&str1);
		queue.enqueue(&str2);
		queue.enqueue(&str3);
		
		TS_ASSERT_EQUALS(&str1, queue.peek());
		TS_ASSERT_EQUALS(&str1, queue.dequeue());
		TS_ASSERT_EQUALS(&str2, queue.peek());
		TS_ASSERT_EQUALS(&str2, queue.dequeue());
		TS_ASSERT_EQUALS(&str3, queue.peek());
		TS_ASSERT_EQUALS(&str3, queue.dequeue());
		TS_ASSERT(queue.isEmpty());
	}
}


}
