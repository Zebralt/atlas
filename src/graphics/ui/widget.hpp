#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include "mouseover.hpp"

/**
    \author Zebralt
    \brief This class is the basis for all widgets.
*/
class Widget : public MouseReceptiveSurface {
protected:
    std::string name;
    static int id;
public:
    
    Widget();
    Widget(const std::string& n);
    
    void setName(const std::string& n);
    
    std::string getName();
    
    virtual void onMouseEnter();
    virtual void onMouseLeave();
    virtual int hashcode();
};

#endif // WIDGET_HPP_