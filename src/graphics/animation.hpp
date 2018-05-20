#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <SFML/Graphics.hpp>

#include "../global.hpp"
#include "../model/temporary.hpp"
#include "../model/container.hpp"
#include "../engine/time/timer.hpp"
#include "../engine/engine.hpp"


#define TIMEWISE_PARAMS float duration, int wait = 0, int interval = 0
#define TARGETTIMEWISE_PARAMS Blob* target, TIMEWISE_PARAMS

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

class Animation : public Temporary, public TimeEnabled {
public:
    Animation(TIMEWISE_PARAMS);
    bool isRunning();
    int getPast();
    virtual AnimationType type() { return None; };
    virtual ~Animation() {}
protected:
    int interval = Engine::update_interval;
    float duration = 1;
};

class Action : public Animation {
public:
    Action(TIMEWISE_PARAMS);
    virtual void set_target(Blob* target);
protected:
    Blob* target = nullptr;
};

class FadeIn : public Action {
public:
    FadeIn(TIMEWISE_PARAMS);
    void update();
    virtual AnimationType type() { return Fading; }
};

class FadeOut : public Action {
public:
    FadeOut(TIMEWISE_PARAMS);
    void update();
    virtual AnimationType type() { return Fading; }
};

class Fade : public Action {
public:
    Fade(int goal, TIMEWISE_PARAMS);
    void udpate();
    virtual AnimationType type() { return Fading; }
protected:
    int goal;
};

class Move : public Action {
public:
    Move(const Vec2&, TIMEWISE_PARAMS);
    void update();
    virtual AnimationType type() { return Movement; }
protected:
    Vec2f vec;
    Vec2f buffer;
    Vec2f factors;
};

class GoTo : public Move {
public:
    GoTo(const Vec2&, TIMEWISE_PARAMS);
    void set_target(Blob* target);
    virtual AnimationType type() { return Movement; }
};

class TextAnimation : public Action {
public:
    TextAnimation(TIMEWISE_PARAMS);
    void set_target(Label* target);
    virtual AnimationType type() { return Text; }
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
    void update();
    void set_target(Blob* target);
private:
    uint it = 0;
};

class Group : public Action, public Container<Action*> {
public:
    Group(TIMEWISE_PARAMS);
    void update();
    void set_target(Blob* target);
};

///////////////////////////////////////////////////////////////////////

class WaitAndBeStill : public Animation {
public:
    WaitAndBeStill(Blob* w, int wait);
    void update();
};

#endif // ANIMATION_HPP_
