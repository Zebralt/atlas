#include "scene.hpp"
#include "engine.hpp"
#include "../graphics/ui/picture.hpp"
#include "../graphics/animations/translation.hpp"
#include "../graphics/ui/label.hpp"

// You should explore the principle of 'Scene's

Scene::Scene() {}

Scene::~Scene() {
	for (auto ptr : sprites) {
		if (ptr) delete ptr;
	}
}

EngineLogoScene::EngineLogoScene() {}

void EngineLogoScene::initialize() {
	auto logo = Engine::create_sprite("resources/textures/logo.jpg");
	
	if (logo) {		
		logo->setPosition(sf::Vector2f(Engine::get_setting("video/resolution/width").as_int()/2 - logo->getSize().w/2, Engine::get_setting("video/resolution/height").as_int()/2 - logo->getSize().h/2));
		sprites.push_back( (Blob*) logo);
	}
	
	label = new Label("No scene found. Exiting in " + std::to_string(count) + ".", Engine::get().get_global_font());
	label->setPosition(sf::Vector2f(Engine::get_setting("video/resolution/width").as_int()/2 - label->getSize().w/2, 5));
	label->setTextColor(sf::Color::Black);
	
	sprites.push_back(label);
}

void EngineLogoScene::terminate() {

}

void EngineLogoScene::update() {
	int now = timer.getTime().asMilliseconds();
	if (status == RUNNING && now - past > 1000) {
		
		count--;
		label->setText("No scene found. Exiting in " + std::to_string(count) + ".");
	
		if (!count) {
			Engine::quit();
		}
				
		past = now;
	}
}

SceneSequence::SceneSequence() {}

SceneSequence::~SceneSequence() {
	for (auto ptr : scenes) {
		if (ptr) delete ptr;
	}
}

void SceneSequence::initialize() {
	if (scenes.size() && index < scenes.size()) {
		scenes[index]->initialize();
	}
	else {
		status = TERMINATED;
	}
}

void SceneSequence::terminate() {
	if (scenes.size() && index < scenes.size()) {
		scenes[index]->terminate();
	}
	else {
		status = TERMINATED;
	}
}

void SceneSequence::update() {
	if (!scenes.size() || index >= scenes.size()) {
		status = TERMINATED;
	}
	else if (!scenes[index] || !scenes[index]->getStatus()) {
		if (scenes[index]) {
			scenes[index]->terminate();
		}
		index++;
		if (index < scenes.size()) {
			scenes[index]->initialize();
		}
	}
}