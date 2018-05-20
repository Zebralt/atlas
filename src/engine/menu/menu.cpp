#include "menu.hpp"
#include "../../pugixml/pugixml.hpp"

MenuItem::MenuItem() {}
MenuItem::MenuItem(const std::string& name) : name(name) {}

Menu::Menu() {}

bool Menu::load_from_file(const std::string& filepath) {
	pugi::xml_document xml_doc;
//	auto parse_result = xml_doc.load_file(filepath.c_str());
	
	pugi::xpath_node_set nodes = xml_doc.select_nodes("menu/item");
	
	for (auto& node : nodes) {
		// if type is this or this or this
		add(new MenuItem(node.node().attribute("text").as_string()));
	}
	
	return true;
}