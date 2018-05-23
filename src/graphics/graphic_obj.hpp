#ifndef graphic_obj_hpp__
#define graphic_obj_hpp__

#include "../model/object.hpp"
#include "../model/drawable.hpp"
#include "../model/temporary.hpp"
#include "animation.hpp"

/**
	\author Zebralt
	\brief This class is supposed to be the main class for
	graphical objects. It can be animated, has a temporary
	life expectancy, and can be identified by its ID parameter.
	Ugh, I can't help but hate that name, 'Blob'. But 'GraphicObj'
	is no better. Can't find a better one.
*/
class Blob : public Drawable, public Temporary, public Object {
protected:
    std::map<AnimationType, Action*> typed_animations;
    std::vector<Action*> generic_animations;
public:
    Blob();
    virtual ~Blob();

    /// \brief Run an animation on this object. The animation
    /// will be stored in the object, and will be deleted upon
    /// completion.
    void runAnimation(Action*);
    
    /// \brief You may want to delete an item only after all its
    /// animations have ended. That is why as long as animations
    /// are running, even if the object is terminated, it won't be
    /// deleted till all animations have been completed and freed.
    /// This method is a simple test whether there are still animations
    /// running on the object.
    bool animated();
    
    virtual void update();
    
    /// \brief Says if the object is ready to be deleted or not.
    bool terminated();
    
    virtual short getStatus() { return Temporary::getStatus() ? Temporary::getStatus() : !terminated(); }
};

#endif
