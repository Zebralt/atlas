#include "scene.hpp"
#include "engine.hpp"
#include "graphics/ui/picture.hpp"
#include "graphics/ui/label.hpp"
#include "graphics/ui/button.hpp"
#include "graphics/ui/panel.hpp"
#include "tools/strmanip.hpp"

// You should explore the principle of 'Scene's

// namespace atlas_engine {

Scene::Scene() {}

Scene::~Scene() {
//	for (auto ptr : sprites) {
//		_FREE(ptr);
//	}
}

void Scene::update() {
//	update_or_delete(sprites);
}

//////////////////////////////////////////////////////////////////////////////////

std::string default_message = "No scene found. Exit in $1.\nAs you can see text is wrapped ! Not sure about justification though";

void create_panel() {
	auto panel = new Panel();
	panel->setSize(200,300);
	panel->setLayout(new ColumnLayout());
	panel->setBorder(2, sf::Color::Black);
	panel->setPosition(Vec2f(200, 200));
	
	panel->add(new Label("hello there"));
	panel->add(new Label("hello there"));
	panel->add(new Label("hello there"));
	panel->add(new Label("hello there"));
	panel->add(new Label("hello there"));
	panel->add(new Label("hello there"));
	
	panel->get(0)->setMouseClickAction([panel](){
		panel->runAnimation(new FadeIn(4));
		panel->setStatus(TemporaryState::TERMINATED);
	});
	
	Engine::register_widget(panel);
}

EngineLogoScene::EngineLogoScene() {}

void EngineLogoScene::initialize() {
	// load sprite
	auto logo = Engine::create_sprite("resources/textures/logo.jpg");
	
	// if sprite loaded, center it on screen
	if (logo) {		
		logo->setPosition(sf::Vector2f(Engine::getIntegerSetting("video/resolution/width")/2 - logo->getSize().w/2, Engine::getIntegerSetting("video/resolution/height")/2 - logo->getSize().h/2));
//		sprites.push_back( (Blob*) logo);
		
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
	label = new Label(Engine::get()._get_global_font());
	label->setPadding(20);
	label->setBackgroundColor(sf::Color::Red);
	label->setText(insert_args(default_message, {std::to_string(count)}));
	label->setPosition(sf::Vector2f(Engine::getIntegerSetting("video/resolution/width")/2 - label->getSize().w/2, 5));
	label->setTextColor(sf::Color::Black);
	label->setTextSize(16);
	
	label->setMouseClickAction([](){
		LOG("LABEL CLICKED !");
	});
	
	auto btn = new Button(Engine::get_global_font());
	btn->setPadding(20);
	btn->setBackgroundColor(sf::Color::Red);
	btn->setText("Click here !");
	btn->setPosition(Vec2f(20, 20));
	btn->setTextColor(sf::Color::Black);
	
	btn->setMouseClickAction([](){
		LOG("Buttons are just labels in the end.");
	});
	
	auto name_label = new Label("Look at the code of EngineLogoScene to see how to do this.", Engine::get_global_font());
	name_label->setPadding(20);
	name_label->setBackgroundColor(sf::Color::Yellow);
	name_label->setPosition(Vec2f(10, 550));
	name_label->setTextColor(sf::Color::Black);
	
	name_label->setMouseClickAction([name_label](){
		name_label->runAnimation(new Sequence({ new Move(Vec2(100, 0), 3), new FadeIn(2) }));
//		name_label->setMouseClickAction([](){});
//		name_label->setMouseEnterAction([](){});
//		name_label->setMouseLeaveAction([](){});
		name_label->setStatus(TERMINATED);
	});
	
	Engine::register_widget("l1", label);
	Engine::register_widget("btn_1", btn);
	Engine::register_widget(name_label);
	
	auto a1 = new GoTo(Vec2(300,300), 10.5);	
	label->runAnimation(a1);
	
//	sprites.push_back(label);
//	sprites.push_back(btn);
//	sprites.push_back(name_label);
	
	create_panel();
	
	// initialize timer
	create_timer("countdown_to_exit");
}

void EngineLogoScene::terminate() {
	if (label) delete label;
}

void EngineLogoScene::update() {
	int now = timer.as_milliseconds();
	if (status == TemporaryState::RUNNING && now - past > 17) {
		Scene::update();
		label->setText(insert_args(default_message, {std::to_string(count)}));
				
		past = now;
	}
	
	if (status == TemporaryState::RUNNING && now - get_timer("countdown_to_exit") > 1000) {
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
		status = TemporaryState::TERMINATED;
	}
}

void SceneSequence::terminate() {
	if (scenes.size() && index < scenes.size()) {
		scenes[index]->terminate();
	}
	else {
		status = TemporaryState::TERMINATED;
	}
}

void SceneSequence::update() {
	if (!scenes.size() || index >= scenes.size()) {
		status = TemporaryState::TERMINATED;
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

// } // namespace atlas_engine
