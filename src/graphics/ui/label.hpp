#ifndef label_hpp__
#define label_hpp__

#include <SFML/Graphics.hpp>

#include "widget.hpp"
//#include "ui.hpp"

/// SOme ideas before I forget :
/// Label could use Engine::global_font by default if no font specified
/// If initial text, have label of the length of the text (duh...)
/// or at least have the position of label refers to the left edge
/// of the text.

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
