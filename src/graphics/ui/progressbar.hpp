#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include "widget.hpp"

class ProgressBar : public Widget {
public:
    ProgressBar();
    void setValue(float t);
    void goToValue(float t);
    void setSize(int w, int h);
    void setColor(sf::Color c);
    bool animated();
    void setPosition(sf::Vector2f v);
    void setOrigin(sf::Vector2f v);
    void onMouseOverIn();
    void onMouseOverOut();
    void setOpacity(int r);

    float getValue();
private:
    float value;
    sf::RectangleShape foreground;

    virtual void draw(sf::RenderTarget& tar, sf::RenderStates states) const {
        tar.draw(background);
        tar.draw(foreground);
    }
};

#endif // PROGRESSBAR_HPP
