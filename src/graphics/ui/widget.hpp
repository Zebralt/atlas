#ifndef WIDGET_HPP_
#define WIDGET_HPP_

#include "mouseover.hpp"

// namespace atlas_engine {
//namespace Graphics {
//namespace gui {

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
    
//    virtual void onMouseEnter();
//    virtual void onMouseLeave();
    virtual int hash_code();
};

//}
//}
// } // namespace Video::gui

#endif // WIDGET_HPP_