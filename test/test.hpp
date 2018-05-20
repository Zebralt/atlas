#ifndef TEST_HPP_
#define TEST_HPP_

#include <iostream>
#include <iomanip>

/// MACROS
#define TEST_LOG(x) std::cout << x << std::endl

#define FAIL_TEST(x) { TEST_LOG(std::setw(30) << std::left << x << std::setw(20) << "\t FAILED"); return false; }
#define PASS_TEST(x) { TEST_LOG(std::setw(30) << std::left << x << std::setw(20) << "\t OK"); return true; }

#define CHECK_TEST_GROUP(name) (result ? PASS_TEST_GROUP(name) : FAIL_TEST_GROUP(name))

#define FAIL_TEST_GROUP(x) TEST_LOG(std::setw(30) << std::left << x << std::setw(20) << "\t FAILED\n")
#define PASS_TEST_GROUP(x) TEST_LOG(std::setw(30) << std::left << x << std::setw(20) << "\t OK\n")

#define INIT_RESULT bool result = true
#define RUN_TEST result &=

class Test {
public:
	static std::string test_prefix;
};

#define TEST_PREFIX(x) Test::test_prefix = x
#define FREE_PREFIX Test::test_prefix = ""

#define APPEND_PREFIX Test::test_prefix + "::"

void run_tests();

#endif // TEST_HPP_