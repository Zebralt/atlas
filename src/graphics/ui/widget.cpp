#include "widget.hpp"

int Widget::id = 0;

Widget::Widget() : MouseReceptiveSurface() { 
	name = "widget_" + std::to_string(id++); 
}
Widget::Widget(const std::string& n) : name(n), MouseReceptiveSurface() {}

void Widget::setName(const std::string& n) { 
	name = n; 
}

std::string Widget::getName() { 
	return name; 
}

void Widget::onMouseEnter() { 
	std::cout << "entered " << name << std::endl; 
	/*setBackgroundColor(sf::Color::Blue);*/
}

void Widget::onMouseLeave() { 
	std::cout << "left " << name << std::endl;
	/*setBackgroundColor(sf::Color::Red);*/
}

int Widget::hashcode() { 
	return MouseReceptiveSurface::hashcode() | Blob::hashcode(); 
	}