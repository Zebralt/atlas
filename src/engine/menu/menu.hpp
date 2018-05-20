#ifndef MENU_HPP_
#define MENU_HPP_

#include "../../global.hpp"
#include "../../model/container.hpp"

class MenuItem {
public:
	MenuItem();
	MenuItem(const std::string& text);
	
private:
	std::string name;
};

class Menu : public CycleList<MenuItem*> {
public:
	Menu();
	bool load_from_file(const std::string& filepath);
	
};

//class MenuItemView : public Label {
//public:
//	MenuItem(MenuItem* mi, sf::Font* f);
//	virtual void onMouseEnter();
//	virtual void onClick();
//};
//
//class MenuView : public Panel {
//public:
//	MenuView();
//	MenuView(Menu* m);
//	
//private:
//	Blob* selection_background = nullptr;
//};

#endif // MENU_HPP_