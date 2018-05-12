#ifndef mouseover_hpp__
#define mouseover_hpp__

#include "../graphic_obj.hpp"

class MouseReceptiveSurface : public Blob {
    bool hovering = false;
    sf::View* targetView = nullptr;
public:
    MouseReceptiveSurface() : Blob() {}
    void setHover(bool b) { hovering = b; }
    bool getHover() { return hovering; }
    virtual int hashcode() { return ONHOVER | ONCLICK; }
    virtual void onMouseEnter() {}
    virtual void onMouseLeave() {}
    virtual void onMouseMove(sf::Vector2i pos) {}
    virtual void onClick() {}
    sf::View* getTargetView() { return targetView; }
    void setTargetView(sf::View* v) { targetView = v; }
    
    sf::Color hoverForegroundColor = sf::Color::Red;
    sf::Color hoverBackgroundColor = sf::Color::Yellow;
    
    sf::Color regularForegroundColor = sf::Color::Black;
    sf::Color regularBackgroundColor = sf::Color::Transparent;
    
    virtual void setHoverColors(sf::Color fg, sf::Color bg) {
		hoverForegroundColor = fg;
		hoverBackgroundColor = bg;
    }
    
	virtual void setRegularColors(sf::Color fg, sf::Color bg) {
		regularForegroundColor = fg;
		regularBackgroundColor = bg;
    }
    
    virtual void setBackgroundColor(sf::Color c) {
		Blob::setBackgroundColor(c);
		regularBackgroundColor = c;
    }
};

#endif // mouseover_hpp__