
#include <eugenejonas/cpp_stuff/misc.h>

#include <cxxtest/TestSuite.h>


namespace eugenejonas::cpp_stuff
{


class UnitTest_findSubstring: public CxxTest::TestSuite
{
	public: void test1()
	{
		char str[] = "xyzabc";
		char substr[] = "ab";
		int res = findSubstring(substr, str);
		TS_ASSERT_EQUALS(3, res);
	}
	
	public: void test2()
	{
		char str[] = "";
		char substr[] = "";
		int res = findSubstring(substr, str);
		TS_ASSERT_EQUALS(0, res);
	}
	
	public: void test3()
	{
		char str[] = "dsh";
		char substr[] = "";
		int res = findSubstring(substr, str);
		TS_ASSERT_EQUALS(0, res);
	}
	
	public: void test4()
	{
		char str[] = "";
		char substr[] = "ds";
		int res = findSubstring(substr, str);
		TS_ASSERT_EQUALS(std::string::npos, res);
	}
	
	public: void test5()
	{
		char str[] = "abcdef";
		char substr[] = "ef";
		int res = findSubstring(substr, str);
		TS_ASSERT_EQUALS(4, res);
	}
	
	public: void test6()
	{
		char str[] = "abcde";
		char substr[] = "ef";
		int res = findSubstring(substr, str);
		TS_ASSERT_EQUALS(std::string::npos, res);
	}
}

class UnitTest_areBracketsCorrect: public CxxTest::TestSuite
{
	public: void test1()
	{
		char s[] = "([](<{}>))";
		bool res = areBracketsCorrect(s);
		TS_ASSERT(res);
	}
	
	public: void test2()
	{
		char s[] = "({<)>}";
		bool res = areBracketsCorrect(s);
		TS_ASSERT_EQUALS(false, res);
	}
	
	public: void test3()
	{
		char s[] = "(<{})";
		bool res = areBracketsCorrect(s);
		TS_ASSERT_EQUALS(false, res);
	}
	
	public: void test4()
	{
		char s[] = "{(<><{[][[]]}>)}()";
		bool res = areBracketsCorrect(s);
		TS_ASSERT(res);
	}
}

class UnitTest_compareIgnoreCase_with_lower_case: public CxxTest::TestSuite
{
	public: void test1()
	{
		TS_ASSERT_LESS_THAN(compareIgnoreCase("ab", "abc"), 0);
	}
	
	public: void test2()
	{
		TS_ASSERT_EQUALS(0, compareIgnoreCase("", ""));
	}
	
	public: void test3()
	{
		TS_ASSERT_EQUALS(0, compareIgnoreCase("ab", "ab"));
	}
	
	public: void test4()
	{
		TS_ASSERT_LESS_THAN(0, compareIgnoreCase("def", "de"));
	}
	
	public: void test5()
	{
		TS_ASSERT_LESS_THAN(0, compareIgnoreCase("def", "abc"));
	}
	
	public: void test6()
	{
		TS_ASSERT_LESS_THAN(0, compareIgnoreCase("t", ""));
	}
}

class UnitTest_compareIgnoreCase_with_mixed_case: public CxxTest::TestSuite
{
	public: void test1()
	{
		TS_ASSERT_EQUALS(0, compareIgnoreCase("AbC", "abc"));
	}
	
	public: void test2()
	{
		TS_ASSERT_EQUALS(0, compareIgnoreCase("dEf", "Def"));
	}
	
	public: void test3()
	{
		TS_ASSERT_LESS_THAN(compareIgnoreCase("AbC", "bc"), 0);
	}
	
	public: void test4()
	{
		TS_ASSERT_LESS_THAN(compareIgnoreCase("BC", "bD"), 0);
	}
	
	public: void test5()
	{
		TS_ASSERT_LESS_THAN(compareIgnoreCase("bC", "bD"), 0);
	}
}


}
