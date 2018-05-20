#ifndef mouseover_hpp__
#define mouseover_hpp__

#include "../graphic_obj.hpp"

#include <functional>

/**
    \author Zebralt
    \brief This class is the one you want to inherit from
    if you want your sprite or anything visual to be able to
    receive events from the mouses, such as clicking and hovering.
    On second thought, I have updated them to lambda functions,
    so that you can define on the fly. That's pretty handy. dunnow
    about efficiency though.

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
    virtual int hash_code() { return ON_HOVER | ON_CLICK; }
    
    /// \brief This method will be called upon having the mouse enter
    /// the boundaries of the object. The point for you is to redefine
    /// it so that you can have what you want happen when the mouse 
    /// enters the object's boundaries (such as changing background color,
    /// for example).
    void onMouseEnter() { on_mouse_enter_action(); }
    void setMouseEnterAction(const std::function<void(void)>& f) {
        on_mouse_enter_action = f;
    }
    
    /// \brief This method will be called upon having the mouse leave
    /// the boundaries of the object.
    void onMouseLeave() { on_mouse_leave_action(); }
    void setMouseLeaveAction(const std::function<void(void)>& f) {
        on_mouse_leave_action = f;
    }
    /// \brief Not sure, but I think this will be called upon everytime
    /// the mouse moves inside of the object's boundaries, having entered
    /// it previously.
    void onMouseMove(const Vec2& pos) { on_mouse_move_action(pos); }
    void setMouseMoveAction(const std::function<void(const Vec2&)>& f) {
        on_mouse_move_action = f;
    }
    /// \brief This method will be called upon havint the user click
    /// on the object. It should be nice to be able to know which button
    /// was used.
    void onClick() { on_mouse_click_action(); }
    void setMouseClickAction(const std::function<void(void)>& f) {
        on_mouse_click_action = f;
    }
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
    std::function<void(void)> on_mouse_enter_action = [this](){
        setBackgroundColor(sf::Color::Blue);
    };
    std::function<void(void)> on_mouse_leave_action = [this](){
        setBackgroundColor(sf::Color::Green);
    };
    std::function<void(void)> on_mouse_click_action = [](){};
    std::function<void(const Vec2&)> on_mouse_move_action = [](const Vec2&){};
};

#endif // mouseover_hpp__