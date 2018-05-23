#include "xml_document.hpp"
#include "strmanip.hpp"
#include "../global.hpp"

//pugi::xml_document parse_xml(const std::string& filepath) {
//	pugi::xml_document doc;
//	pugi::xml_parse_result result = doc.load_file(filepath.c_str());
////	std::cout << "Load result: " << result.description() << std::endl;
////	std::cout << "Some probing : " << doc.child("scene").child("content") << std::endl;
////	
////	pugi::xpath_node_set nodes = doc.select_nodes("//choice");
////	
////	for (const pugi::xpath_node& node : nodes) {
////		println('\n' << "Found a choice :");
////		for (auto& choice : node.node().attributes()) {
////			println(choice.name() << ':' << choice.value());
////		}
////	}
////	
////	println(doc.select_node("scene").node().child_value());
//	
//	return doc;
//}

XmlDocument parse_xml(const std::string& filepath) {
	return XmlDocument(filepath);
}

XmlDocument::XmlDocument() {}
XmlDocument::XmlDocument(const std::string& filepath) {
	load_from_file(filepath);
}

void XmlDocument::load_from_file(const std::string& filepath) {
	pugi::xml_parse_result result = load_file(filepath.c_str());
}

int XmlDocument::geti(const std::string& name) {
	auto value = gets(name);
	return value.empty() ? - 1 : std::stoi(value);
}

std::string XmlDocument::gets(const std::string& name) {
	
	if (name.empty()) return "";

	auto elements = split(name, '/');
	auto node = first_child();
	
	for (uint i=0; i<elements.size() - 1; i++) {
		if (node.child(elements[i].c_str())) {
			node = node.child(elements[i].c_str());
		}
		else {
			return "";
		}
	}
	
	auto last_name = elements[elements.size() - 1];
	
	if (node.child(last_name.c_str())) {
		return node.child(last_name.c_str()).child_value();
	}
	else if (node.attribute(last_name.c_str())) {
		return node.attribute(last_name.c_str()).value();
	}

	return "";
}

bool XmlDocument::has(const std::string& name) {
	
	if (name.empty()) return false;
	
	auto elements = split(name, '/');
	auto node = first_child();
	
	for (uint i=0; i<elements.size() - 1; i++) {
		if (node.child(elements[i].c_str())) {
			node = node.child(elements[i].c_str());
		}
		else {
			return false;
		}
	}
	
	auto last_name = elements[elements.size() - 1];
	
	return node.child(last_name.c_str()) || node.attribute(last_name.c_str());
	
}