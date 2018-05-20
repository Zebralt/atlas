#include "../global.hpp"
#include "settings.hpp"
#include "../tools/strmanip.hpp"
#include <iostream>

Settings::Settings() {}

Settings::Settings(const std::string& filepath) {
    load_from_file(filepath);
}

pugi::xml_document parse_xml(const std::string& filepath) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filepath.c_str());
//	std::cout << "Load result: " << result.description() << std::endl;
//	std::cout << "Some probing : " << doc.child("scene").child("content") << std::endl;
//	
//	pugi::xpath_node_set nodes = doc.select_nodes("//choice");
//	
//	for (const pugi::xpath_node& node : nodes) {
//		println('\n' << "Found a choice :");
//		for (auto& choice : node.node().attributes()) {
//			println(choice.name() << ':' << choice.value());
//		}
//	}
//	
//	println(doc.select_node("scene").node().child_value());
	
	return doc;
}

void Settings::load_from_file(const std::string& filepath) {
    xml_data = parse_xml(filepath);
}

setting_variant Settings::get(const std::string& name) {
    std::vector<std::string> elements = split(name, '/');
    
    pugi::xml_node node = xml_data.child("settings");
//    std::cout << node << std::endl;
//    
//    for (auto& child : node.children()) {
//		std::cout << child.name() << std::endl;
//    }
//        
	pugi::xml_attribute attr;
    
    if (elements.size()) {

        for (uint i=0; i<elements.size() - 1; i++) {
            node = node.child(elements[i].c_str());
//            std::cout << node << std::endl;
        }

		if ((attr = node.attribute(elements[elements.size() - 1].c_str()))) {
//			if (type == "int") {
//				return setting_variant(attr.as_int());
//			}
//			else if (type == "double") {
//				return setting_variant(attr.as_double());
//			}
//			else {
//				return setting_variant(attr.value());
//			}
		}

    }
    
	return attr;
}


int Settings::as_int(const std::string& name) {
	return get(name).as_int();
}
std::string Settings::as_string(const std::string& name) {
	return get(name).as_string();
}