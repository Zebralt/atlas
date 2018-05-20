#include "test.hpp"

#include "tools/test_strmanip.hpp"

#include <fstream>

std::string Test::test_prefix = "";

void run_strmanip_tests() {
	std::string name = "strmanip";
	
	INIT_RESULT;
	TEST_PREFIX(name);
	
	RUN_TEST test_replace_all();
	RUN_TEST test_insert_args();
	RUN_TEST test_extract_substring();
	RUN_TEST test_split();
	RUN_TEST test_parse_file();
	RUN_TEST test_trim();
	
	CHECK_TEST_GROUP(name);
}

#include "menu/test_menu.hpp"

void run_menu_tests() {
	std::string name = "menu";
	
	INIT_RESULT;
	TEST_PREFIX(name);
	
	RUN_TEST test_menu_load_from_file();
	
	CHECK_TEST_GROUP(name);
}

void run_tests() {
	std::string log_file = "log/tests.log";
	
	TEST_LOG("Running tests. Output at " + log_file);
	/// reroute output
	std::ofstream out(log_file);
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
	
	/// and others ...
	run_strmanip_tests();
	
	/// reset cout
    std::cout.rdbuf(coutbuf); //reset to standard output again
}