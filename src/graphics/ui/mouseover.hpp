#ifndef mouseover_hpp__
#define mouseover_hpp__

#include "../graphic_obj.hpp"

/**
    \author Zebralt
    \brief This class is the one you want to inherit from
    if you want your sprite or anything visual to be able to
    receive events from the mouses, such as clicking and hovering.

*/
class MouseReceptiveSurface : public Blob {
public:
    
    MouseReceptiveSurface() : Blob() {}
    
    /// \brief The boolean 'hovering' simply tells the object whether
    /// it is currently hovered upon. Setting it should be the job of
    /// methods that are able to receive events and determine if the
    /// mouse is within the boundaries of the object.
    void setHover(bool b) { hovering = b; }
    
    bool getHover() { return hovering; }
    
    /// \brief Method inherited from the Object interface. Allows to
    /// quickly determine if an object is eligible to mouse events.
    virtual int hashcode() { return ON_HOVER | ON_CLICK; }
    
    /// \brief This method will be called upon having the mouse enter
    /// the boundaries of the object. The point for you is to redefine
    /// it so that you can have what you want happen when the mouse 
    /// enters the object's boundaries (such as changing background color,
    /// for example).
    virtual void onMouseEnter() {}
    
    /// \brief This method will be called upon having the mouse leave
    /// the boundaries of the object.
    virtual void onMouseLeave() {}
    
    /// \brief Not sure, but I think this will be called upon everytime
    /// the mouse moves inside of the object's boundaries, having entered
    /// it previously.
    virtual void onMouseMove(sf::Vector2i pos) {}
    
    /// \brief This method will be called upon havint the user click
    /// on the object. It should be nice to be able to know which button
    /// was used.
    virtual void onClick() {}
    
    /// \brief TODO
    sf::View* getTargetView() { return targetView; }
    
    /// \brief TODO
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
    
private:
    bool hovering = false;
    sf::View* targetView = nullptr;
};

#endif // mouseover_hpp__