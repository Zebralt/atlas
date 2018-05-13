//#include "test_classes.hpp"
//
//////////////////////////////////////////////////////////////////////////////////////
///// ACTUAL GAME WHOLE CLASS
//////////////////////////////////////////////////////////////////////////////////////
//
///*Shmup::Shmup(sfml_app* app) : Game(app) {
//	level = new Level(this);
//	// create player vessels
//}
//
//void Shmup::load(std::string path) {
//	if (path == "custom_1") {
//		// write your customs here (?)
//	}
//	else if (path == "custom_2") {
//		
//	}
//	// etc
//	else
//	level->loadFromFile(path);
//}
//
//void Shmup::eventHandler(sf::Event& event) {
//	if (event.type == sf::Event::KeyPressed) {
//		switch (event.key.code) {
//			default:break;
//		}
//	}
//}
//
//void Shmup::update() {
//	
//	if (level->getStatus() == TERMINATED) {
//		/// show scoreboard
//		/// level clear ! pop-up
//	}
//	
//	{
//		for (int i=0;i<mobile_objs.size();i++) {
//			if (mobile_objs[i]->getStatus() == TERMINATED) {
//				// erase from list
//				// set view status to TERMINATED
//			}
//			mobile_objs[i]->update();
//		}
//		
//		check_collisions();
//	}
//	
//	/// update level
//	level->update();
//	
//	/// check keyboard input
//	
//	// player_vessel.move(sf::Vector2f(application.down - application.up, application.right - application.left))
//	// if (application.key_register.fire_command)
//	// player_vessel.fire()
//	
//}
//
//void Shmup::check_collisions() {
///// https://gamedev.stackexchange.com/questions/39931/fast-accurate-2d-collision
//	/// \foe side
//	/**
//		for each _v in enenmy vessels:
//			for each _p in non-ally projectile in a radius of X around _v:
//				if _v is colliding with _p:
//					erase(_p)
//					damage(_v, _p.damage)
//	*/
//	/// \player side
//	/**
//		for each _v in player vessels:
//			for each _p in non-ally projectile in a radius of X around _v:
//				if _v is colliding with _p:
//					erase(_p)
//					damage(_v, _p.damage)
//	*/
//}
//
//////////////////////////////////////////////////////////////////////////////////////
///// LEVELS
//////////////////////////////////////////////////////////////////////////////////////
//
//Level::Level() {
//
//}
//
//void Level::loadFromFile(std::string path) {
//	std::vector<std::string> content = parseFile(path);
//	// todo ? wip
//}
//
//void Level::addPhase(Phase* p, std::string name) {
//	phases.push_back(p);
//	p.name = name;
//}
//
//#define currentPhase phases[phase_counter]
//
//void Level::update() {
//	if (status == RUNNING) {
//		if (currentPhase->getStatus() == TERMINATED) {
//			phase_counter++;
//		}		
//		if (phase_counter >= phases.size()) {
//			status = TERMINATED;
//			return;
//		}
//		
//		currentPhase->update();
//	}
//}
//
//#define currentWave waves[wave_counter]
//
//void CombatPhase::update() {
//	if (status == RUNNING) {
//		if (currentWave->getStatus() == TERMINATED) {
//			wave_counter++;
//		}		
//		if (wave_counter >= waves.size()) {
//			status = TERMINATED;
//			return;
//		}
//		
//		currentWave->update();
//	}
//}
//
//void QuietPhase::update() {
//	if (status == RUNNING) {
//		if (isDone()) {
//			status = TERMINATED;
//		}
//	}
//}
//
//////////////////////////////////////////////////////////////////////////////////////
///// VIEWS ///
//////////////////////////////////////////////////////////////////////////////////////
//
//
//void MobileObjView::update() {
//	Blob::update();
//	// only update up to model state
//	/// pos = model->getPosition();
//	/// status = model->getStatus();
//	
//}