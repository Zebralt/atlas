#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include "mouseover.hpp"

class Widget : public MouseReceptiveSurface {
protected:
    std::string name;
public:
    static int id;
    
    Widget();
    Widget(const std::string& n);
    
    void setName(const std::string& n);
    
    std::string getName();
    
    virtual void onMouseEnter();
    virtual void onMouseLeave();
    virtual int hashcode();
};

#endif // WIDGET_HPP_