# Atlas

This project aims to make a video game on the theme of shoot-them-up games. Then we will see if we can make our own game by tweaking things and adding  interesting features. 

**Techs:** C++, SFML, pugixml

## Salvaging and designing

*For now, I am just writing this so that we can talk about it. Then I will add the code that can be salvaged.*

I have a previous project from which I can salvage a lot of design concepts and the code that goes with it. The thing is, this code is old in my memory and not completely documented, so we need to establish first how we want to proceed when building this thing. Once we have set the fundations for it, we'll see what we can salvage. Here more or less how it went in the previous project :

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

### Animated images

Once you get spritesheets, you'll want animated pictures. I wrote a system for that, which uses animation graphs. This still need work, but it works well. What would be needed next is to be able to interact with the graph (for example, when pressing a key : when jumping, you want your character to follow the animation frames for the action of jumping).

It is kind of a hassle to describe this directly in the code, so it could be interesting to store that in a XML file.

## Time

The refresh frequency is resumed to a set quantity of milliseconds between updates.  

**Clock** from SFML does not allow you to pause, only to reset. Thus the class **Timer** was built atop of **Clock** to allow for pausing. It is used to keep track of time in the main class and all time-related objects.

Tracking FPS may be a hindrance to performance.



## The game itself

The game itself is stored and handled in a separate class inheriting from **Game**.  This was to separate the engine from the game mechanics, as to be able to develop it independently and to make it reusable for other projects and games.

## States and transitions

It can be seen as fancy and superfluous, but if you want to have loading screens, I have tried building a system for it with transitions. A state is simply anything that can happen in the game application. For example, you launch any game :

* fade in > logo of company X, animated or not > fade out (transition); repeat Y times
* optional loading screen to load the resources for the main menu > transition
* fade in or animation > main menu
* you select 'play' in the main menu > fade out
* loading screen : free unnecessary resources, load game resources
* play the game through the **Game** class.
* pause the game, return to main title (transition)
* etc.

## About the shmup

I don't remember all that well the inner workings of this part, but I will try.

### Bullets

Bullets of any shape.

### Lasers

Whoo, lasers ! WIP. Basically, lines through the screen with specific breadth.

### Hitboxes

This is the complicated part. Grid scanning may be the solution (Only scan the items in the same region).

### Patterns

Can be a pattern for a bullet or for a vessel (player, enemy).

A function *f* to extrapolate a pattern rather than a sequence of points. A pattern also has a *rotation* parameter. (Linear patterns are actually pretty much all you need. The rest would be quite misleading. Oooor you can have a tracé for weird patterns).

### Stages

I see a stage as a sequence of events. For example :

* <start>
* play music X
* show stage name (fade in fade out)
* 10 sec before first enemies
* wave of enemy 1, 2, 3, pause, 4, 5 , 6 ...
* boss event (see below)
* win
* show scores
* <end>

A boss fight, simply as a sequence of phases. A boss phase would require a list of bullet shooting patterns, movements and their order. Duration and life to be depleted to win this phase. Show name of the phase if it has one.

### Waves

They are two types of waves : 

* waves of enemies during a stage
* waves of bullets when shooting
