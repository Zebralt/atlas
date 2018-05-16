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
class Scene : public Temporary, public sf::Drawable {
public:
	Scene();
	
//	virtual void in() {}
	virtual void initialize() {}
//	virtual void run() {}
	virtual void terminate() {}
	virtual void update() {}
//	virtual void out() {}
	
	virtual void handle_events(sf::Event& event) {}
	
	virtual ~Scene();	
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates rss) const {
		for (auto sprite : sprites) {
//			sprite->draw(target, rss);
			target.draw(*sprite, rss);
		}
	}
	
protected:
	std::vector<Blob*> sprites;
};

class SceneSequence : public Scene, public Container<Scene*> {
public:
	SceneSequence();
	
	~SceneSequence();
	void initialize();
	void terminate();
	void update();
	
private:
	std::vector<Scene*> scenes;
	int index = 0;
};

#include "time/timer.hpp"

class Label;

class EngineLogoScene : public Scene, public TimeEnabled {
public:
	EngineLogoScene();
	
	void initialize();
	void terminate();
	void update();
	
private:
	int count = 5;
	Label* label = nullptr;
	
};

#endif // ENGINE_PROGRAM_HPP_
