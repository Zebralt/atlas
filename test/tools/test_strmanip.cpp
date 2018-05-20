#include "test_strmanip.hpp"
#include "../../src/tools/strmanip.hpp"

bool test_replace_all() {
	std::string name = APPEND_PREFIX + "replace_all";
	
	std::string m1 = "I for one am very happy to be here for once one more time!";
	std::string a1 = "I for two am very happy to be here for once two more time!";
	std::string o1 = "one"; std::string s1 = "two";
	std::string m2 = "I for one am very happy to be here for once one more time!";
	std::string a2 = "I for one am very happy to be here for once one more excalibur!";
	std::string o2 = "time"; std::string s2 = "excalibur";
	
	auto t1 = replace_all(m1, o1, s1);
	auto t2 = replace_all(m2, o2, s2);
	
	if (t1 != a1) FAIL_TEST(name);
	if (t2 != a2) FAIL_TEST(name);
	
	PASS_TEST(name);
}

bool test_insert_args() {
	std::string name = APPEND_PREFIX + "insert_args";
	
	std::string m1 = "$1 and $2";
	std::vector<std::string> v1 = {"Afix", "Alix"};
	std::string a1 = "Afix and Alix";
	std::string m2 = "No chance for $1, $2 and $3. But I still like $2.";
	std::vector<std::string> v2 = {"Paris", "Toronto", "Berlin"};
	std::string a2 = "No chance for Paris, Toronto and Berlin. But I still like Toronto.";
	
	auto t1 = insert_args(m1, v1);
	auto t2 = insert_args(m2, v2);
	
	if (t1 != a1) FAIL_TEST(name);
	if (t2 != a2) FAIL_TEST(name);
	
	PASS_TEST(name);
}

bool test_trim() {
	std::string name = APPEND_PREFIX + "trim";
	
	std::string m1 = "  Hello there ! I hope you'ven been well	";
	std::string a1 = "Hello there ! I hope you'ven been well";
	std::string m2 = "abcdef ghijkl";
	std::string a2 = "abcdef ghijkl";
	
	auto t1 = trim(m1);
	auto t2 = trim(m2);
	
	if (t1 != a1) FAIL_TEST(name);
	if (t2 != a2) FAIL_TEST(name);
	
	PASS_TEST(name);
}
bool test_extract_substring() {
	std::string name = APPEND_PREFIX + "extract_substring";
	
	std::string m1 = "hello there!";
	std::string a1 = "ello";
	std::string x1 = "1:4";
	std::string m2 = "hello there!";
	std::string a2 = "hello there";
	std::string x2 = ":-1";
	
	auto t1 = extract_substring(m1, x1);
	auto t2 = extract_substring(m2, x2);
	
	if (t1 != a1) FAIL_TEST(name);
	if (t2 != a2) FAIL_TEST(name);
	
	PASS_TEST(name);
}

bool test_split() {
	std::string name = APPEND_PREFIX + "split";
	
	std::string m1 = "Hello there! What is your name ?";
	char x1 = ' ';
	std::vector<std::string> a1 = {"Hello", "there!", "What", "is", "your", "name", "?"};
	
	auto t1 = split(m1, x1);
	
	if (t1 != a1) FAIL_TEST(name);
	
	PASS_TEST(name);
}

bool test_parse_file() {
	std::string name = APPEND_PREFIX + "parse_file";
	
	PASS_TEST(name);
}