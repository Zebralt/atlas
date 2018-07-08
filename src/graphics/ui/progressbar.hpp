#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include "widget.hpp"

// namespace atlas_engine {
//namespace Graphics {
//namespace gui {

class WidgetStyle {
public:
    WidgetStyle();
    virtual void stylize(Widget* w) = 0;
};

enum class ProgressBarStyle {
    None = 0, 
    Cursor = 1, 
    Caret = 2
};

class ProgressBar : public Widget {
public:
    ProgressBar(ProgressBarStyle p = ProgressBarStyle::None);
    void setValue(float t);
    void goToValue(float t);
    void setSize(int w, int h);
    void setColor(sf::Color c);
    bool animated();
    void setPosition(sf::Vector2f v);
    void setOrigin(sf::Vector2f v);
    void setOpacity(int r);

    void setStyle(ProgressBarStyle p);
    void setCursorSize(int w, int h);
    
    float getValue();
private:
    float value;
    sf::RectangleShape foreground;
    sf::Shape* cursor = nullptr;
    ProgressBarStyle style;

    virtual void draw(sf::RenderTarget& tar, sf::RenderStates states) const {
//        tar.draw(background);
        Widget::draw(tar, states);
        tar.draw(foreground);
        if (style != ProgressBarStyle::None && cursor) {
            tar.draw(*cursor);
        }
    }
};

//}
//}
// } // namespace Video::gui

#endif // PROGRESSBAR_HPP
