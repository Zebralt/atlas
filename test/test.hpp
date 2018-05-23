#ifndef TEST_HPP_
#define TEST_HPP_

#include <iostream>
#include <iomanip>

/// MACROS
#define TEST_LOG(x) std::cout << x << std::endl

#define SHOW_TEST_RESULT(expected, obtained) TEST_LOG(std::setw(30) << std::left << name << std::setw(20) << expected << std::setw(20) << obtained)
#define FAIL_TEST { TEST_LOG(std::setw(30) << std::left << name << std::setw(20) << "\t FAILED"); return false; }
#define PASS_TEST { TEST_LOG(std::setw(30) << std::left << name << std::setw(20) << "\t OK"); return true; }

//#define FAIL_TEST FAIL_TEST
//#define PASS_TEST PASS_TEST

#define CHECK_TEST_GROUP(name) (result ? PASS_TEST_GROUP(name) : FAIL_TEST_GROUP(name))

#define FAIL_TEST_GROUP(x) TEST_LOG(std::setw(30) << std::left << x << std::setw(20) << "\t FAILED\n")
#define PASS_TEST_GROUP(x) TEST_LOG(std::setw(30) << std::left << x << std::setw(20) << "\t OK\n")

#define INIT_RESULT bool result = true
#define RUN_TEST result &=

/**
	\brief This is a rudimentary way of performing tests.
	To create additional tests, you should create your own
	.hpp/.cpp files. You can write as many tests functions 
	as you want, however they should follow the following
	format : All test functions returns boolean. Always 
	begin a test function by giving its name :   
	    
	    std::string name = APPEND_PREFIX + "load";
	    
	To fail a test, use `FAIL_TEST`. To pass a test,
	use `PASS_TEST`. This will print the results.
	You can take a look at existing test files for reference.
	Once you have written your individual test functions,
	you can pass them as one test package (for example, you 
	would write one function per method in your class, and 
	gather those in one test function for your class). To
	write a test package function, you should first write :
	
		std::string name = "MyClass";
		INIT_RESULT;
		TEST_PREFIX(name);
	
	Those macros are syntactic sugar mostly. TEST_PREFIX allows
	you to prefix each individual test function with the name
	of the test package inside of which it is run. To run a 
	test function, do it like this :
	
		RUN_TEST myTestFunction();
		
	Once this is done, you can end the test package function by
	`CHECK_TEST_GROUP(name)`. Then you can simply add it to the
	list of functions in the function `run_all_tests` in `test.cpp`.
	
*/
class Test {
public:
	static std::string test_prefix;
};

#define TEST_PREFIX(x) Test::test_prefix = x
#define FREE_PREFIX Test::test_prefix = ""
#define APPEND_PREFIX Test::test_prefix + "::"

void run_tests(const std::string& output = "");

#endif // TEST_HPP_