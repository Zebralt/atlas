//#ifndef MENU_HPP_
//#define MENU_HPP_
//
//#include "global.hpp"
//#include "model/container.hpp"
//
//#include <functional>
//
//// namespace atlas_engine {
//
////class MenuStack : public Stack<MenuController*> {
////	
////};
//
//class MenuItem {
//public:
//	MenuItem();
//	MenuItem(const std::string& text);
//	MenuItem(const std::string& text, const std::function<void(void)>&);
//	
//	void set_action(const std::function<void(void)>&);
//	std::function<void(void)> get_action();
//	std::string getText();
//	
//private:
//	std::string text;
//	std::function<void(void)> action;
//};
//
//class MenuModel : public CycleList<MenuItem*> {
//public:
//	MenuModel();
//	bool load_from_file(const std::string& filepath);
//	
//};
//
//#include "graphics/ui/label.hpp"
//
//class MenuItemView : public Label {
//public:
//	MenuItemView(MenuItem* mi) : Label() {
//		if (mi) {
//			setText(mi->getText());
//			setMouseClickAction(mi->get_action());
//		}
//	}
//};
//
//#include "graphics/ui/panel.hpp"
//
//class MenuView : public Panel {
//public:
//	MenuView();
//	~MenuView();
//	MenuView(MenuModel* m);
//	
//private:
////	Blob* selection_background = nullptr;
//};
//
//class Menu : public Cycle<MenuItem*> {
//public:
//	Menu();
//	Menu(MenuModel*);
//	
//	virtual void next();
//	virtual void previous();
//	virtual MenuItem* get();
//	
//protected:
//	MenuModel* model;
//	MenuView* view;
//};
//
//// } // namespace
//
//#endif // MENU_HPP_