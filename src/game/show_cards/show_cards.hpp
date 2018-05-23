#ifndef SHOW_CARDS_HPP_
#define SHOW_CARDS_HPP_

#include "../../engine/scene.hpp"

class Card {
public:
	Card(const std::string& name, const std::string& desc) : _name(name), _description(desc) {}
	
	std::string name() { return _name; }
	std::string desc() { return _description; }
	
private:
	std::string _name;
	std::string _description;
};

#include "../../graphics/ui/panel.hpp"
#include "../../graphics/ui/label.hpp"

class CardView : public Panel {
public:
	CardView(Card* v) : card(v), Panel() { init(); }
	
	void init() {
		setSize(450, 550);
		setBackgroundColor(sf::Color(30, 30, 80));
		setPosition(Vec2f(30, 30));
		clear_actions();
		
		/// elements
		auto name_label = new Label(card->name(), Engine::get_font("segoe_semi_light"));
		name_label->clear_actions();
		name_label->setTextSize(24);
		name_label->setTextColor(sf::Color::White);
		add(name_label);
		
		auto desc_label = new Label(card->desc(), Engine::get_font("segoe"));
		desc_label->clear_actions();
		desc_label->setPosition(Vec2f(0, 30));
		desc_label->setTextColor(sf::Color::White);
		desc_label->setTextSize(16);
		add(desc_label);
	}
	
	void update() {}
	
	~CardView() { if (card) delete card; }
	
private:
	Card* card;
};

class ShowCardsScene : public Scene {
public:
	ShowCardsScene();
	void load_from_file(const std::string& filepath);
	
	void initialize();
	void update();
	void terminate();
	void handle_events(sf::Event&);
	
private:
	std::vector<CardView*> cards;
};

#endif // SHOW_CARDS_HPP8