#include "test_menu.hpp"
#include "../../src/engine/menu/menu.hpp"

bool test_menu_load_from_file() {
	std::string name = APPEND_PREFIX + "replace_all";
	
	std::string test_file = "";
	
	Menu menu;
	menu.load_from_file(test_file);
	
	std::vector<MenuItem*> a1;
	
	
	PASS_TEST(name);
}