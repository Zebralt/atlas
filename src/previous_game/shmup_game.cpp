#include "shmup_game.hpp"	
#include "phases.hpp"
#include "mobileobj.hpp"
#include "../engine/engine.hpp"
#include "../graphics/ui/picture.hpp"
#include "vessels.hpp"
#include "pellet.hpp"
#include "patterns.hpp"
#include "../graphics/ui/label.hpp"
#include "pellet_factory.hpp"
#include "../graphics/animations/fade_out.hpp"
#include "../tools/strmanip.hpp"

Shmup::Shmup(Engine* app) : EngineProgram(app) {
	level = new Level(this);
	sf::View* view = new sf::View();
	view->reset(sf::FloatRect(0, 0, 1024*0.75, 768)); // TODO
    //view->setCenter(sf::Vector2f(1024/2, 768/2));
    view->setViewport(sf::FloatRect(0.2f, 0.f, 0.75f, 1.f));
    canvas_width = 1024 * view->getViewport().width; // TODO
    canvas_height = 768 * view->getViewport().height; // TODO
    game_viewport = EngineViewport(view, 1); // TODO
	// create background
//	Picture* bgpic = new Picture(app->getTexture("stars"));
//	bgpic->setSize(app->settings.resolution.width, app->settings.resolution.height);
//	app->addBlob(appview, bgpic);
    
    // create vessels
    PlayerVessel* pv = new PlayerVessel();
    pv->setPosition(sf::Vector2f(canvas_width/2,canvas_height*0.9f));
    PlayerVesselView* pvv = new PlayerVesselView(pv);
    player_vessels.push_back(std::pair<PlayerVessel*,PlayerVesselView*>(pv,pvv));
    pvv->setTexture(app->get_texture("spritesheet_1"),sf::IntRect(244,525,64,64));
//	pvv->importTexture(app->getTexture("simple_ship"));
    pvv->setSize(50,50);
    engine->add_blob(game_viewport, pvv);
    
    addPattern("linear", new Pattern());
    
   

//	Vessel* v = new Vessel();
//	v->orientation = 180 - 90;
//	v->speed = 0.2f;
//	v->setPosition(sf::Vector2f(0,100));
//	v->setTrajectory(new Trajectory(getPattern("linear"), 2000));
//	VesselView* vv = new VesselView(v);
//	v->setShootWave(new ShootWave(v,new RawWave(pellet_factory::createInstantArc(-90,180,30,1,1,1,20,800,200)),this));
//	addObject(v,vv);
//    vv->importTexture(app->getTexture("simple_ship"));
//    
//    Vessel* w = new Vessel();
//	w->orientation = 180;
//	w->speed = 0.5f;
//	w->setPosition(sf::Vector2f(550,100));
//	w->setTrajectory(new Trajectory(getPattern("linear"), 2000));
//	VesselView* vw = new VesselView(w);
//	w->setShootWave(new ShootWave(w,new RawWave(pellet_factory::createInstantArc(-90,180,30,1,1,1,20,800,200)),this));
//	addObject(w,vw);
//    vw->importTexture(app->getTexture("simple_ship"));
	
//    app->addVertex(generateGrid(app));
    
}

void Shmup::start() {
    load("custom_1");
}

void Shmup::load(std::string path) {
	// etc
//	else
	level->loadFromFile(path);
}

void Shmup::eventHandler(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::W:
			{
//				LOG("eh");
//				AnimatedPicture* ap = new AnimatedPicture(engine->getTexture("blueish_explosion"),15,0);
//				ap->setFrameCount(64);
//				ap->setCycle(sf::Vector2i(8,8));
//				ap->setFrameSize(sf::Vector2f(1024/8,1024/8));
//				//ap->setFramePosition(sf::Vector2f(0,0));
//				ap->setPosition(player_vessels[0].first->position - sf::Vector2f(0,100));
//				engine->addBlob(appview,ap);

//				for (std::map<MobileObj*, MobileObjView*>::iterator it = mobile_objs.begin(); it != mobile_objs.end(); ++it) {
//					it->first->position = sf::Vector2f(sf::Mouse::getPosition(*engine->window));    
//
//				}
			procEvent("show_level_name","");
			}
			break;
			default:break;
		}
	}
}

void Shmup::update() {
	
	if (status == RUNNING && level->getStatus() == TERMINATED) {
		/// show scoreboard
		Label* label = new Label(engine->get_global_font());
		label->setText("GAME OVER");
		label->setPosition(sf::Vector2f(200,200));
		engine->add_widget("scoreboard",label);
		status = TERMINATED;
		/// level clear ! pop-up
	}
	else if (status != IDLE) {
		for (std::map<MobileObj*, MobileObjView*>::iterator it = mobile_objs.begin(); it != mobile_objs.end(); /*++it*/) {
			sf::Vector2f pos = it->first->position;
			{
				Phasing p = (pos.x + it->second->getSize().w/2 >= 0 && pos.x - it->second->getSize().w/2 <= canvas_width && pos.y + it->second->getSize().h/2 >= 0 && pos.y - it->second->getSize().h/2 <= canvas_height ?ONSCREEN:OFFSCREEN);
//				LOG("phasing is " << (p == ONSCREEN?"ONSCREEN":"OFFSCREEN") << "; canvas=" << canvas_width << ":" << canvas_height << "; pos=" << pos.x << ":" << pos.y);
				it->first->setPhasing(p);
			}
			if (it->first->getStatus() == TERMINATED) {
				// set view status to TERMINATED
				it->second->setStatus(TERMINATED);
				// free memory
				delete(it->first);
				// erase from list
				it = mobile_objs.erase(it++);
			}
			else {
				it->first->update();
				++it;
			}
		}
		
		//behold, c++ witchcraft !
		// std::remove_if (doesn't work for maps)
		
//		for (int i=0;i<toDelete[i];i++) {
			
//		}
		
		check_collisions();
		/// update level
		level->update();
		
		/// check keyboard input
		
		// player_vessel.move(sf::Vector2f(engine.down - engine.up, engine.right - engine.left))
		// if (engine.key_register.fire_command)
		// player_vessel.fire()
		
		bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
		bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		
		player_vessels[0].first->move(sf::Vector2f(right - left, down - up));
		
		player_vessels[0].first->update();
	}
}

void Shmup::addObject(MobileObj* mo, MobileObjView* mjv) {
	mobile_objs[mo] = mjv;
	engine->add_blob(game_viewport,mjv);
}

void Shmup::addPattern(std::string name, Pattern* p) {
	patterns[name] = p;
}

Pattern* Shmup::getPattern(std::string name) {
	if (patterns.find(name) != patterns.end()) {
        return patterns[name];
    }
    else {
		LOG("sfml_app message: couldn't find pattern " << name);
        return nullptr;
    }
}

void Shmup::pause() {

}

void Shmup::unpause() {

}

void Shmup::check_collisions() {
/// https://gamedev.stackexchange.com/questions/39931/fast-accurate-2d-collision
	/// \foe side
	/**
		for each _v in enenmy vessels:
			for each _p in non-ally projectile in a radius of X around _v:
				if _v is colliding with _p:
					erase(_p)
					damage(_v, _p.damage)
	*/
	/// \player side
	/**
		for each _v in player vessels:
			for each _p in non-ally projectile in a radius of X around _v:
				if _v is colliding with _p:
					erase(_p)
					damage(_v, _p.damage)
	*/
}



void Shmup::procVessel(MobileObj_MVC vessel) {
	addObject(vessel.model, vessel.view);
}

void Shmup::procProjectile(short type, std::string pattern_type, float speed, float angle, float p_x, float p_y) {
	Pellet* v = new Pellet();
	v->orientation = 180 + angle;
	v->speed = speed;
//	v->setPosition(sf::Vector2f(canvas_width/2,canvas_height/2-300));
	v->setPosition(sf::Vector2f(p_x, p_y));
	//    v->setStatus(IDLE);
	PelletView* vv = new PelletView(v);    
	vv->importTexture(engine->get_texture("simple_ship"));
	vv->setSize(25,25);
	vv->getTexture()->setSmooth(true);
//		vv->setBackgroundColor(sf::Color::Blue);
	addObject(v,vv);
	v->setTrajectory(new Trajectory(getPattern(pattern_type),2000));		
	//engine->playSound("laser1");
}

	
void Shmup::procEvent(std::string type, std::string data) {
	if (type == "show_level_name") {
		Label* lbl = new Label(engine->get_global_font());
		lbl->setText(level->name);
		lbl->setText("Level 01 : The Will of the Wisps");
		//lbl->setPosition(sf::Vector2f(100,100));
		lbl->setTextSize(20);
		lbl->setTextColor(sf::Color::White);
		lbl->setOpacity(50);
		lbl->setStatus(TERMINATED);
		lbl->animate(new FadeOut(lbl,10,255,0), AnimationType::Fading);
		engine->add_blob(game_viewport, lbl);
//		engine->addWidget("booyah_meh", lbl);
	}
	else if (type == "show_string") {
		
	}
}

sf::Vector2f toVector(std::string x2) {
	std::string x3 = "";
	for (int i=0;i<x2.length();i++) if (x2[i] != '(' && x2[i] != ')') x3 += x2[i];
	std::vector<std::string> booyah_x3 = split(x3,',');
	sf::Vector2f pos(std::stod(booyah_x3[0]), std::stod(booyah_x3[1]));
	return pos;
}

void Shmup::interprete(std::string str) {
//	LOG("interpreting:" << str << "...");
	std::vector<std::string> elems = split(str,':');
	
	/// 1 : type
	if (elems[0] == "event") {
		if (elems.size() > 1) {
			procEvent(elems[1],"");
		}
	}
	else if (elems[0] == "vessel") {
		LOG(str);
		int type = std::stoi(elems[1]);
		std::string pattern_type = elems[2];
		float  speed = std::stod(elems[3]);
		double angle = std::stod(elems[4]);
		std::string x2 = elems[5];
		
		// (x, y) to sf::vector2f
		sf::Vector2f pos = toVector(x2);
		
		MobileObj_MVC vessel = level->getVesselFromType(type);
		vessel.model->position = pos;
		vessel.model->speed = speed;
		vessel.model->orientation = 180 + angle;
		vessel.model->setTrajectory(new Trajectory(getPattern(pattern_type), 2000));
		procVessel(vessel);
	}
	else if (elems[0] == "projectile") {
		int type = std::stoi(elems[1]);
		std::string pattern_type = elems[2];
		float speed = std::stod(elems[3]);
		double angle = std::stod(elems[4]);		
		sf::Vector2f pos;
//		if (elems.size() > 5) pos = toVector2(elems[5]);
//		
		procProjectile(type, pattern_type, speed, angle, pos.x, pos.y);
	}
}

////////////////////// WIP CUSTOMS
/// Ultimately, those will be virtual methods of class Level::

MobileObj_MVC Level::getVesselFromType(int t) {

	switch(t) {
		case 1: {
			// put your customs here
			Vessel* v = new Vessel();
			v->orientation = 180 - 90;
			v->speed = 0.2f;
//			v->setTrajectory(new Trajectory(game->getPattern("linear"), 2000));
			VesselView* vv = new VesselView(v);
			v->setShootWave(new ShootWave(v,new RawWave(pellet_factory::createInstantArc(-45,90,2,1,1,1,20,800,200)),game));
			//addObject(v,vv);
			vv->importTexture(game->get_engine()->get_texture("ship_1"));
			vv->setSize(30,30);
			return {v,vv};
		} 
		break;
		case 2: {
			// or here
			Vessel* v = new Vessel();
			v->orientation = 180;
			v->speed = 0.2f;
//			v->setTrajectory(new Trajectory(game->getPattern("linear"), 2000));
			VesselView* vv = new VesselView(v);
			v->setShootWave(new ShootWave(v,new RawWave(pellet_factory::createInstantArc(-45,90,4,1,1,1,20,800,200)),game));
			//addObject(v,vv);
			vv->importTexture(game->get_engine()->get_texture("ship_2"));
			vv->setSize(40,40);
			return {v,vv};
		} 
		break;
		case 3: {
			// or here
		} 
		break;
		case 4: {
			// or here
		} 
		break;
		case 5: {
			// or here
		} 
		break;
		case 6: {
			// you know the drill
		} 
		break;
		default: {
		
		} break;
	}
	
	return {};
	
}