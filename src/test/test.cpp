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
//	RUN_TEST test_extract_substring();
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
	
//	RUN_TEST test_menu_load_from_file();
	
	CHECK_TEST_GROUP(name);
}

#include "test_xml.hpp"

void run_xml_tests() {
	std::string name = "xml_document";
	
	INIT_RESULT;
	TEST_PREFIX(name);
	
	RUN_TEST test_load();
	RUN_TEST test_has();
	RUN_TEST test_get();
	
	CHECK_TEST_GROUP(name);
}

void run_all_tests() {
	run_strmanip_tests();
	run_xml_tests();
}

void run_tests(const std::string& output) {
	std::string log_file = output.empty() ? "log/tests.log" : output;
	
	if (log_file != "cout" && !log_file.empty()) {
		TEST_LOG("Running tests. Output at " + log_file);
		/// reroute output
		std::ofstream out(log_file);
		std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
		std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
		
		/// and others ...
		run_all_tests();
		
		/// reset cout
		std::cout.rdbuf(coutbuf); //reset to standard output again
	}
	else {
		run_all_tests();
	}
}