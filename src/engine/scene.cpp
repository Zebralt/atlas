#include "scene.hpp"
#include "engine.hpp"
#include "../graphics/ui/picture.hpp"
#include "../graphics/animations/translation.hpp"
#include "../graphics/ui/label.hpp"
#include "../tools/strmanip.hpp"

// You should explore the principle of 'Scene's

Scene::Scene() {}

Scene::~Scene() {
	for (auto ptr : sprites) {
		_FREE(ptr);
	}
}

void Scene::update() {
	update_or_delete(sprites);
}

//////////////////////////////////////////////////////////////////////////////////

std::string default_message = "No scene found. Exit in $1.";

EngineLogoScene::EngineLogoScene() {}

void EngineLogoScene::initialize() {
	// load sprite
	auto logo = Engine::create_sprite("resources/textures/logo.jpg");
	
	// if sprite loaded, center it on screen
	if (logo) {		
		logo->setPosition(sf::Vector2f(Engine::get_setting("video/resolution/width").as_int()/2 - logo->getSize().w/2, Engine::get_setting("video/resolution/height").as_int()/2 - logo->getSize().h/2));
		sprites.push_back( (Blob*) logo);
		
		auto a1 = new Move(Vec2(100,0), 1);
		auto a2 = new Move(Vec2(-100,0), 1, 1000);
		auto as = new Sequence();
		as->add(a1);
		as->add(a2);

//		auto f1 = new FadeIn(5);
		
		logo->runAnimation(as);
//		logo->runAnimation(f1);
	}
	
	// create label
	label = new Label(Engine::get().get_global_font());
	label->setText(insert_args(default_message, {std::to_string(count)}));
	label->setPosition(sf::Vector2f(Engine::get_setting("video/resolution/width").as_int()/2 - label->getSize().w/2, 5));
	label->setTextColor(sf::Color::Black);
	
	Engine::register_widget(label);
	
	auto a1 = new GoTo(Vec2(300,300), 5.5);	
	label->runAnimation(a1);
	
	sprites.push_back(label);
	
	// initialize timer
	create_timer("countdown_to_exit");
}

void EngineLogoScene::terminate() {
	if (label) delete label;
}

void EngineLogoScene::update() {
	int now = timer.as_milliseconds();
	if (status == RUNNING && now - past > 17) {
		Scene::update();
		label->setText(insert_args(default_message, {std::to_string(count)}));
				
		past = now;
	}
	
	if (status == RUNNING && now - get_timer("countdown_to_exit") > 1000) {
		count--;
		if (!count) {
			terminate();
			Engine::quit();
		}
		set_timer("countdown_to_exit", now);
	}
}

/////////////////////////////////////////////////////////////////////////////////////

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
