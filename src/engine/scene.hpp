#ifndef ENGINE_PROGRAM_HPP_
#define ENGINE_PROGRAM_HPP_

#include "../global.hpp"
#include "../model/temporary.hpp"
#include "../model/container.hpp"
#include "../graphics/graphic_obj.hpp"

#include <SFML/Graphics.hpp>

class Engine;

// A scene essentially :
// "In your game you probably want a main menu, a few levels and an ending scene. 
// How do you organize all of these into the separate pieces they are? You guessed it, 
// Scene. When you think about your favorite movie you can see that it's distinctly 
// broken down into scenes, or separate parts of the story line. If we apply this same 
// thought process to games, we should come up with at least a few scenes no matter 
// how simple the game is."

// http://cocos2d-x.org/docs/cocos2d-x/en/basic_concepts/scene.html
// http://cocos2d-x.org/docs/cocos2d-x/en/basic_concepts/sprites.html

/**
	\author Zebralt
	\brief This class is a key component of the engine. It allows you to make things
	happen within the engine, calling upon its features, such as creating sprites,
	playing sounds and musics, etc. This is where you will program what you actually
	want to see, such as a game, or a cutscene animated within the engine, etc.
	The engine holds only one scene at any moment. It will pass on events to the 
	current scene (handle_events) so you can handle the events and decide what to
	do with them. The scene will store all sprites you create.
*/
class Scene : public Temporary, public sf::Drawable {
public:
	Scene();
	
//	virtual void in() {}

	/// \brief This is an abstract method that will be the first called upon
	/// when playing a scene. You can create all your variables and other things
	/// you need to do once, in the beginning.
	virtual void initialize() = 0;
//	virtual void run() {}

	/// \brief This is an abstract method that will be called last when playing 
	/// a scene. This is where you can clean up things, if you don't already do
	/// it in the destructor.
	virtual void terminate() = 0;
	
	/// \brief This method is common to all temporary objects. It will be called
	/// upon at every iteration of the main loop.
	virtual void update();
//	virtual void out() {}
	
	/// \brief This method will be called to trickle down events from the engine.
	/// You can redefine it to decide what to do with the events the engine receives
	// (mouse clicks, keys pressed, etc.)
	virtual void handle_events(sf::Event& event) = 0;
	
	virtual ~Scene();	
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates rss) const {
		for (auto sprite : sprites) {
			target.draw(*sprite, rss);
		}
	}
	
protected:
	std::vector<Blob*> sprites;
};

/**
	\author Zebralt
	\brief A sequence of Scenes. Once one is over, it will go over to the next.
*/
class SceneSequence : public Scene, public Container<Scene*> {
public:
	SceneSequence();
	
	~SceneSequence();
	void initialize();
	void terminate();
	void update();
	
private:
	std::vector<Scene*> scenes;
	uint index = 0;
};

#include "time/timer.hpp"

class Label;

/**
	\author Zebralt
	\brief If no scene is loaded before starting the engine, this will be the
	default scene. Closes after X seconds. Demonstrates sprite loading and 
	animations.
*/
class EngineLogoScene : public Scene, public TimeEnabled {
public:
	EngineLogoScene();
	
	void initialize();
	void terminate();
	void update();
	
	void handle_events(sf::Event&) {}
	
private:
	int count = 20;
	Label* label = nullptr;
	
};

#endif // ENGINE_PROGRAM_HPP_
