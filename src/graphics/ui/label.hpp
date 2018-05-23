#ifndef label_hpp__
#define label_hpp__

#include <SFML/Graphics.hpp>

#include "widget.hpp"

/// You can wrap text with '\n', but you need to wrap it manually.

enum TextAlign {Left,Center,Right};

/**
	\brief A class to display text.
*/
class Label : public Widget {
public:
    Label();
    Label(const std::string& text);
    Label(sf::Font*);
    Label(const std::string& text, sf::Font*);
    
    void setOrigin(sf::Vector2f v);
    void setPosition(sf::Vector2f v);
	virtual void setPadding(int);
    virtual void setOpacity(int r);

    void setText(const std::string& s);
    void setTextSize(int s);
    void setTextColor(sf::Color c);
    void setTextAlign(TextAlign a);
    void setFont(sf::Font*);

    sf::Text& getText();

    bool animated();
protected:
    sf::Text label;
    sf::Font* textFont;
    TextAlign align = Left;
    void alignText();
    void computeTextSize();

    virtual void draw(sf::RenderTarget& tar, sf::RenderStates states) const {
//        states.transform *= getTransform();
        //tar.draw(background);
        Widget::draw(tar,states);
        tar.draw(label);
    }
};

#endif
