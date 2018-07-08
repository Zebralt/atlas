#include "test_xml.hpp"
#include "tools/xml_document.hpp"

void test_pugixml() {
	TEST_LOG("TESTS-\n\n");
	pugi::xml_document doc;
	doc.load_file("settings.xml");
	
	TEST_LOG((doc.first_child().child("title").child_value()));
	TEST_LOG((doc.child("title")));
	TEST_LOG((doc.child("settings")));
	TEST_LOG((doc.child("settings").child("video").child("resolution").attribute("width")));
	TEST_LOG((doc.child("settings").child("video").child("resolution").attribute("width").as_int()));
	
	
	
	exit(0);
}

bool test_load() {
	std::string name = APPEND_PREFIX + "load_from_file";
	
	XmlDocument xdoc;
	xdoc.load_from_file("resources/test/settings.xml");
	
	if (xdoc.document_element().empty()) FAIL_TEST;
	
	PASS_TEST;
}

bool test_get() {
	std::string name = APPEND_PREFIX + "get";
	
	XmlDocument xdoc;
	xdoc.load_from_file("resources/test/settings.xml");
	
	//xml_attribute
	// querying PCDATA
//	if (xdoc.get("title").as_string() != "Show Cards") FAIL_TEST;
	// querying an attribute
//	if (xdoc.get("video/resolution/width").as_int() != 1024) FAIL_TEST;
	
	//as_int/as_string
	// querying an attribute
	if (xdoc.geti("video/resolution/width") != 1024) FAIL_TEST;
	// querying PCDATA
	if (xdoc.gets("title") != "Show Cards") FAIL_TEST;
	
	PASS_TEST;
}

bool test_has() {
	std::string name = APPEND_PREFIX + "has";
	
	XmlDocument xdoc;
	xdoc.load_from_file("resources/test/settings.xml");
	
	if (!xdoc.has("title")) 					FAIL_TEST;
	if (!xdoc.has("video/resolution")) 			FAIL_TEST;
	if (!xdoc.has("video/resolution/width")) 	FAIL_TEST;
	if (xdoc.has("xdoc")) 						FAIL_TEST;
	
	PASS_TEST;
}