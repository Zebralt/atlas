#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <SFML/Graphics.hpp>

#include "global.hpp"
#include "model/temporary.hpp"
#include "model/container.hpp"
#include "engine/timer.hpp"
#include "engine/engine.hpp"


#define TIMEWISE_PARAMS float duration, int wait = 0, int interval = 0
#define TARGETTIMEWISE_PARAMS Blob* target, TIMEWISE_PARAMS

// namespace atlas_engine {
//namespace Graphics {


class Label;
class Blob;

enum AnimationType {
    None, 
    Fading,
    Movement,
    Scaling,
    Text,
    Value
};

/**
    \brief Animations are processes with a finite time duration.
*/
class Animation : public Temporary, public TimeEnabled {
public:
    Animation(TIMEWISE_PARAMS);
    bool isRunning();
    int getPast();
    virtual AnimationType type() { return AnimationType::None; };
    virtual ~Animation() {}
protected:
    int interval = Engine::update_interval;
    float duration = 1;
};

/**
    \brief Actions allow you to operate gradual processes on target objects,
    such as gradually moving from point A to point B, or progressively 
    decreasing opacity to smoothly close a visual element. 
    If you wish to destroy an object only once all actions operating on it (for 
    example if you want to have a graphical element exit by moving out of the screen, 
    you would want to be deleted after it has gone out of screen), you can simply
    terminate the object (setStatus(TERMINATED)) while animations are still running.
    The engine will delete the object only when all animations have been terminated
    as well.
    */
class Action : public Animation {
public:
    Action(TIMEWISE_PARAMS);
    virtual void set_target(Blob* target);
protected:
    Blob* target = nullptr;
};

/**
    \brief This action allows to have the target object gradually disappear from
    screen.
*/
class FadeIn : public Action {
public:
    FadeIn(TIMEWISE_PARAMS);
    void update();
    virtual AnimationType type() { return AnimationType::Fading; }
};

class FadeOut : public Action {
public:
    FadeOut(TIMEWISE_PARAMS);
    void update();
    virtual AnimationType type() { return AnimationType::Fading; }
};

class Fade : public Action {
public:
    Fade(int goal, TIMEWISE_PARAMS);
    void udpate();
    virtual AnimationType type() { return AnimationType::Fading; }
protected:
    int goal;
};

class Move : public Action {
public:
    Move(const Vec2&, TIMEWISE_PARAMS);
    void update();
    virtual AnimationType type() { return AnimationType::Movement; }
protected:
    Vec2f vec;
    Vec2f buffer;
    Vec2f factors;
};

class GoTo : public Move {
public:
    GoTo(const Vec2&, TIMEWISE_PARAMS);
    void set_target(Blob* target);
    virtual AnimationType type() { return AnimationType::Movement; }
};

class TextAnimation : public Action {
public:
    TextAnimation(TIMEWISE_PARAMS);
    void set_target(Label* target);
    virtual AnimationType type() { return AnimationType::Text; }
};

class RollNumbers : public TextAnimation {
public:
    RollNumbers(TIMEWISE_PARAMS);
    void update();
};

class RollText : public TextAnimation {
public:
    RollText(TIMEWISE_PARAMS);
    void update();
};

///////////////////////////////// ANIMATION COLLECTIONS

class Sequence : public Action, public Container<Action*> {
public:
    Sequence(float duration = 0, int wait = 0, int interval = 0);
    Sequence(const std::vector<Action*>& , float duration = 0, int wait = 0, int interval = 0);
    void update();
    void set_target(Blob* target);
private:
    uint it = 0;
};

class Group : public Action, public Container<Action*> {
public:
    Group(TIMEWISE_PARAMS);
    Group(const std::vector<Action*>&, TIMEWISE_PARAMS);
    void update();
    void set_target(Blob* target);
};

///////////////////////////////////////////////////////////////////////

class WaitAndBeStill : public Animation {
public:
    WaitAndBeStill(Blob* w, int wait);
    void update();
};

//} 
// } // namespace Video

#endif // ANIMATION_HPP_
