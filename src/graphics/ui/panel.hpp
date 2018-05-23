#ifndef PANEL_HPP_
#define PANEL_HPP_


#include "../../global.hpp"
#include "../../model/container.hpp"

#include "widget.hpp"
#include "picture_box.hpp"

class Engine;
class Panel;

/**
    \author Zebralt
    \brief A class used to layout elements in a panel.
    Similar to the Java implementation.
*/
class Layout {
public:
    Layout() {}
    Layout(Panel* t) { target = t;}
    
    /// \brief Main method to redefine for a new layout.
    /// To be called after constructor.
    virtual void layoutTarget() = 0;
    void setTarget(Panel *p) { target = p;}

protected:
    Panel* target;
    unsigned int margin = 1;
};

class ColumnLayout : public Layout {
public:
    ColumnLayout() : Layout() {}
    ColumnLayout(Panel* t) : Layout(t) {}
    void layoutTarget();
};

class GridLayout : public Layout {
public:
    GridLayout(int r, int c) : rows(r), cols(c), Layout() {}
    GridLayout(Panel* t, int r, int c) : rows(r), cols(c), Layout(t) {}
    void layoutTarget();
    
protected:
    int rows,cols;
    bool orientation = true; // left to right / f=top to bot
};

/**

    \brief How I see what a Panel would be :
    - container of Widget*
    - do not share its internal widgets with the engine
    - but this is wrong, because you want the internal
    elements to be subjected to events
    - so, you would need to trickle down events to widgets
    - not just panel, because it would be hard to detect
    if a widget is panel and only in that case pass on events
    

*/
class Panel : public Widget, public Container<Widget*> {
public:
    Panel();
    ~Panel();

    virtual void setPosition(sf::Vector2f v);
    virtual void setOrigin(sf::Vector2f v);
    virtual void setSize(int,int);
    void adjustSize(int,int);
    
    virtual void setOpacity(int r);
    virtual void update();
    
    virtual void setStatus(short);
    
    /// \brief redifinition of Container::add
    virtual void add(Widget* w);
    
    Widget* getItem(std::string);
    
//    // add all items to app
//    virtual void move_in(Engine*);

    virtual void register_elements();
//    
//    // remove all items from app
//    virtual void move_out(Engine*);
//    
    void setLayout(Layout* l);
    
//    void setBackgroundImage(PictureBox* p);
//    
//    void setBackgroundImageSize(int w, int h);
//    
//    void adjustBackgroundImage();
//    
//    void fitBackgroundImage(float fx, float fy);
//    void fitBackgroundImage(float);
//    
    //void setBackgroundImagePosition(sf::Vector2f);    
    

protected:
//    bool drawElements = true;
    Layout* layout = nullptr;
    PictureBox* background_image = nullptr;

    virtual int hash_code() { return Widget::hash_code() | CONTAINER; }
    
//    virtual void draw(sf::RenderTarget& tar, sf::RenderStates states) const {
//        states.transform *= getTransform();
//        tar.draw(background,states);
////        if (drawElements) {
////        for (uint i=0;i<items.size();i++) {
////            tar.d   raw(*items[i],states);
////        }
////        }
//
//    }
};

#endif // PANEL_HPP_
