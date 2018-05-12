/*#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "widget.hpp"
#include "clickable.hpp"
#include "MouseOverActive.hpp"

class GraphicalUserInterface;

class Button : public GraphicObj{
public:
    Button(GraphicalUserInterface& gui);

    void setPosition(sf::Vector2f v);
    void setOrigin(sf::Vector2f v);

    void setText(std::string s);

    void setTextSize(int s);

    void setTextColor(sf::Color c);

    void setTextAlign(TextAlign a);

    /// ABSTRACT METHODS
    //void onMouseOverIn();
    //void onMouseOverOut();
    void onClick();

    bool isAnimated();

    void setOpacity(int r);
private:
    sf::Text label;
    sf::Font textFont;
    TextAlign align;
    void alignText();

    virtual void draw(sf::RenderTarget& tar, sf::RenderStates states) const{
        states.transform *= getTransform();
        tar.draw(background,states);
        tar.draw(label,states);
    }
};



#endif // BUTTON_HPP_
*/