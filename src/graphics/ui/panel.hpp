#ifndef PANEL_HPP_
#define PANEL_HPP_


#include "../../global.hpp"
#include "../../model/container.hpp"

#include "widget.hpp"
#include "picture_box.hpp"

class Engine;
class Panel;

class Layout {
public:
    Panel* target;
    unsigned int margin = 1;
    Layout(Panel* t) { target = t;}
//    void addComponent(Widget* w);
//    void removeComponent(Widget* w);
    virtual void layoutTarget() = 0;
};

class ColumnLayout : public Layout {
public:
    ColumnLayout(Panel* t) : Layout(t) {}
    void layoutTarget();
};

class GridLayout : public Layout {
    int rows,cols;
    bool orientation = true; // left to right / f=top to bot
public:
    GridLayout(Panel* t, int r, int c) : rows(r), cols(c), Layout(t) {}
    void layoutTarget();
};

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
    
    // add to own list, and add to parent list ?
    virtual void add(Widget* w);
    Widget* getItem(std::string);
    
    // add all items to app
    virtual void move_in(Engine*);
    
    // remove all items from app
    virtual void move_out(Engine*);
    
    void setLayout(Layout* l);
    
    void setBackgroundImage(PictureBox* p);
    
    void setBackgroundImageSize(int w, int h);
    
    void adjustBackgroundImage();
    
    void fitBackgroundImage(float fx, float fy);
    void fitBackgroundImage(float);
    
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
