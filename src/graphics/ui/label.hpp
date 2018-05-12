#ifndef label_hpp__
#define label_hpp__

#include <SFML/Graphics.hpp>

#include "widget.hpp"
//#include "ui.hpp"

enum TextAlign {Left,Center,Right};

class Label : public Widget {
public:
    Label();
    Label(sf::Font*);
    Label(std::string text, sf::Font*);
    
    void setOrigin(sf::Vector2f v);
    void setPosition(sf::Vector2f v);

    virtual void setOpacity(int r);

    void setText(std::string s);
    void setTextSize(int s);
    void setTextColor(sf::Color c);
    void setTextAlign(TextAlign a);
    void setFont(sf::Font*);

    sf::Text& getText();

    /// ABSTRACT METHODS

    virtual void onMouseEnter();
    virtual void onMouseLeave();

    bool isAnimated();
protected:
    sf::Text label;
    sf::Font* textFont;
    TextAlign align;
    void alignText();

    virtual void draw(sf::RenderTarget& tar, sf::RenderStates states) const {
//        states.transform *= getTransform();
        //tar.draw(background);
        Widget::draw(tar,states);
        tar.draw(label);
    }
};

//////////////////
/*
class TextBox : public Label {
public:
	TextBox();
	TextBox(sf::Font*);
	TextBox(std::string,sf::Font*);
	
	void generateLabels(int);
	void setPosition(sf::Vector2f);
	void setOrigin(sf::Vector2f);
	
	void setOpacity(int);
	
	void setTextSize(int);
	
	bool direction = 0; // 1 = downward, 0 = upward
	
protected:
	sf::Text label;
	TextAlign align;
	sf::Font* font;
	
};*/

#endif
