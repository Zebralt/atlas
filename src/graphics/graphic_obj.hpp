#ifndef graphic_obj_hpp__
#define graphic_obj_hpp__

#include "../model/object.hpp"
#include "../model/drawable.hpp"
#include "../model/temporary.hpp"
#include "animation.hpp"

class Blob : public Drawable, public Temporary, public Object {
protected:
    std::map<AnimationType, Animation*> animations;
public:
    Blob();

    void animate(Animation*, AnimationType);
    bool isAnimated();
    virtual void update();
    bool isDead();
};

#endif
