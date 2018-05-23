#include "show_cards.hpp"
#include "../../engine/engine.hpp"
#include "../../pugixml/pugixml.hpp"
#include "../../tools/strmanip.hpp"

ShowCardsScene::ShowCardsScene() : Scene() {}

void ShowCardsScene::initialize() {
	
	// load resources
	Engine::load(FONT, "inconsolata", "resources/fonts/Inconsolata.otf");
	
	// load content
	load_from_file("resources/show_cards/cards.xml");
	for (auto card : cards) {
		Engine::register_widget(card);
	}
}

void ShowCardsScene::terminate() {

}

void ShowCardsScene::update() {

}

void ShowCardsScene::handle_events(sf::Event& event) {

}

void ShowCardsScene::load_from_file(const std::string& filepath) {
	pugi::xml_document doc;
	// load it
	doc.load_file(filepath.c_str());
	
	pugi::xpath_node_set results = doc.select_nodes(("cards/card"));
	
	std::vector<Card*> card_models;
	
	for (auto& xpath_node : results) {
		auto card = new Card(
		xpath_node.node().child("name").child_value(), 
		wrap_text(xpath_node.node().child("desc").child_value(), 40)
		);
		
		LOG(card->name() << "\n" << card->desc() << "\n\n");
		
		card_models.push_back(card);
		break;
	}
	
	for (auto ptr : card_models) {
		cards.push_back(new CardView(ptr));
		break;
	}
}
