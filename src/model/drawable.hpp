#ifndef drawable_hpp__
#define drawable_hpp__

#include <SFML/Graphics.hpp>

#include "../global.hpp"

/**
    \author Zebralt
    \brief This is the base class for anything that needs to be drawn on screen.
    It has a background rectangle by default.
    You can draw a border by using setBorder. This does not increase the 
    size of the object ; the border is drawn inward.
*/
class Drawable : public sf::Drawable {
protected:
	sf::Vector2f position;
	sf::Vector2f origin;
    int width;
    int height;
    int border_thickness = 1;
    int padding = 8;
    int opacity = 255;

    sf::RectangleShape background;

public:
    Drawable() {
        background.setFillColor(sf::Color::Transparent);
    }

    /// \brief Set to different position.
    virtual void setPosition(sf::Vector2f);
    
    /// \brief Add vector to current position.
    virtual void move(sf::Vector2f);
    
    virtual void setOrigin(sf::Vector2f);
    virtual void setSize(int, int);
    virtual void setOpacity(int);
    virtual void setPadding(int);

    sf::Vector2f getPosition();
    sf::Vector2f getOrigin();
    sf::Rect<int> getRect();
    int getOpacity();
    Size getSize();

    virtual void setBackgroundColor(sf::Color);
    void setBorder(int,sf::Color);

    /// \brief This is the key method of this class. All child classes
    /// may want to redefine it and to make it virtual.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void adjustBackground();
    
//    void fitBackground(float f);
};

/*
template <typename T,typename U> bool encompass(sf::Vector2<T> point, sf::Rect<U> rect) {
    bool b = (point.x >= rect.left && point.x <= rect.left + rect.width
    && point.y >= rect.top && point.y <= rect.top + rect.height);
    return b;
}
*/

#endif
