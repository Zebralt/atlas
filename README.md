# Atlas

This project aims to make a video game on the theme of shoot-them-up games. Then we will see if we can make our own game by tweaking things and adding  interesting features. 

**Techs:** C++, SFML, pugixml

## Scrapping and designing

I have a previous project from which I can scrap a lot of design concepts and the code with it. The thing is, this code is old in my memory and not completely documented, so we need to establish first how we want to proceed when building this thing. Once we have set the fundations for it, we'll see what we can scrap. Here more or less how it went in the previous project :

The whole program takes place in a central class called **Application** or **Engine**. This object will handle resources, settings, time management, audio & video and store all objects relevant to the screen.

## Settings

We can store settings in XML files and parse them with pugixml. We can also use simple config files : 
    
    [Category]
    jump=spacebar
    up=z
    left=q
    right=d
    down=s
    ...

Settings could include : 

* resolution (width, height)
* fullscreen/windowed
* global volume
* sfx volume
* music volume
* controls
* ...

## Base models

### Drawable

SFML provides two generic classes, **Drawable** for objects to be drawn on screen, and **Transformable** for objects that can be subjected to transformations (translation, rotation, etc.). For now, let's just focus on **Drawable**. This will be the base class for all our graphical objects.

### Temporary

In the engine, all objects have an undefined but finite life expectancy. You need them to be able to notify the engine that they can be discarded. Their possible state can vary between 3 values :

* RUNNING : all is well and the object must be updated.
* PAUSED  : the process in which the object plays a role is paused. No need to update the object.
* TERMINATED : the object can be deleted.

### ID object

In an attempt to speed up widget scanning for mouse detection and make class identification an easier process, I had the idea to create a base model which contains an id relative to the class. 

## Graphical objects

Called Blob in the original code.

To be able to delete a graphical object after all its animations have passed, we can do it this way : delete the object only if it is TERMINATED and no animation is running on it.

## User Interface

### Widgets

Basic widgets, such as what you would encounter in Java Swing : labels, buttons, panels, images. Others include the progress bar, loading screen.

### Menus

Menus ... a complicated matter.

It could be interesting to describe them with XML, like JavaFX.

## Animations

Every graphical object (or blob) can be animated with temporary objects of the class Animation. Animations are simply objects that when updating, alter gradually the parameters of the target object(s).  All animations have a set duration or a parameter goal (go to position (x,y), set opacity to 0). Animations also handle their own interval, although since they are called by the main class, they cannot be faster than it when updating (but they can be slower, which is of interest). Should animations hold their own timer object (each) ?

As some animations can work against each other, a graphical object holds a map of animations : it can only hold one animation of each type at a time. For example, you cannot put a FadeIn and a FadeOut on the same object (as they would never reach their goal, counteracting each other until the end of time). For now there are 3 types :
* fading (fade in, fade out)
* movement (translation)
* text (action on text)


Animations that have been implemented so far :

* Fade in (appear gradually through opacity)
* Fade out (disappear gradually through opacity)
* Rolling numbers (for a numerical label, to go gradually from a number to another)
* Translation (moving across the screen)
* Animation queue (animation container, one animation after the other)
* Grouped animation (multiple animations at the same time)
* Progress bar animation (for the widget ProgressBar, to have a smooth transition from a percentage to another)
* "Stay still" animation : An animation that does nothing. I think the purpose was to create a pause in a grouped animation.

## Time

The refresh frequency is resumed to a set quantity of milliseconds between updates.  

**Clock** from SFML does not allow you to pause, only to reset. Thus the class **Timer** was built atop of **Clock** to allow for pausing. It is used to keep track of time in the main class and all time-related objects.

Tracking FPS may be a hindrance to performance.
