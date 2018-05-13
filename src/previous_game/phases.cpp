#include "phases.hpp"
#include "pellet_factory.hpp"
#include "shmup_game.hpp"
#include "../global.hpp"
#include "vessels.hpp"

#include "../tools/strmanip.hpp"

////!\\\\\



////!\\\\\

Level::Level(Shmup* s) {
	game = s;
}

void Level::terminate() {

}

void Level::loadFromFile(std::string path) {
	//std::vector<std::string> content = parseFile(path);
	// todo ? wip
	if (path == "custom_1") {
		// write your customs here (?)
		CombatPhase* cb1 = new CombatPhase();
		RawWave* rw = new RawWave();
		rw->merge(pellet_factory::createInstantArc(-90,180,30,1,1,1,2,800,200));
//		rw->merge(pellet_factory::createSprinkleArc(-90, 180, 30, 5, 1, 1, 3, 200, true, 100));
		cb1->addWave(new Wave(rw,game));
		addPhase(cb1);
		
		CombatPhase* cb2 = new CombatPhase();
		RawWave* re = new RawWave(pellet_factory::createSprinkleArc(-90, 180, 30, 5, 1, 1, 3, 100, true, 2000));
		cb2->addWave(new Wave(re,game));
//		ShootPattern* sp = new ShootPattern(rw);
		
		addPhase(cb2);

//		CombatPhase* cp1 = new CombatPhase();
//		
//		RawWave* rw = new RawWave(vessel_factory::createLine(sf::Vector2f(-20,100), -90, 5, 1, 2, 1.f, 1000, 100));
//			
//		cp1->addWave(new Wave(rw,game));
//		
//		RawWave* re = new RawWave(vessel_factory::createLine(sf::Vector2f(600,-20), 0, 5, 1, 1, 0.5f, 1000, 100));
//		
//		cp1->addWave(new Wave(re, game));
//		
//		addPhase(cp1);
	}
	else if (path == "custom_2") {
		
	}
}

void Level::addPhase(Phase* p) {
	phases.push_back(p);
//	p.name = name;
}

#define currentPhase phases[phase_counter]

void Level::update() {
	if (phases.size() && status == RUNNING) {
		if (currentPhase->getStatus() == TERMINATED) {
			phase_counter++;
//			currentPhase->start();
			LOG("next phase");
		}		
		if (phase_counter >= phases.size()) {
			status = TERMINATED;
			return;
		}
		
		currentPhase->update();
	}
}

#define currentWave waves[wave_counter]

void CombatPhase::addWave(Wave* w) {
	waves.push_back(w);
}

void CombatPhase::update() {
	if (waves.size() && status == RUNNING) {
		if (currentWave->getStatus() == TERMINATED) {
			wave_counter++;		
			if (wave_counter >= waves.size()) {
				status = TERMINATED;
				return;
			}
			else currentWave->start();
			LOG("next wave");
		}
		
		currentWave->update();
	}
}

void QuietPhase::update() {
	if (status == RUNNING) {
		if (1) {
			status = TERMINATED;
		}
	}
}

///////////// WAVE

Wave::Wave(Shmup* g) : game(g) {

}

Wave::Wave(RawWave* w, Shmup* g) : game(g) {
	raw = w;
}

void Wave::extend(RawWave* rw) {
	if (raw) raw->merge(*rw);
	else raw = rw;
}

void Wave::start() {
	timer.reset();
	next_moment = raw->getNextTime();
}

// you should delay same-time objects : one per iteration
void Wave::update() {
	if (status == RUNNING && raw->eow()) {
		status = TERMINATED;
		LOG("wave terminated");
		return;
	}
	if (status == RUNNING) {
		if (timer.getTime().asMilliseconds() >= next_moment) {
			std::vector<std::string> elements = raw->getByTime(next_moment);
			for (int i=0;i<elements.size();i++) {
				// interprete element
				game->interprete(elements[i]);
			}
			next_moment = raw->getNextTime();
		}
	}
}

void Wave::pause() {
	if (status == RUNNING) {
		setStatus(IDLE);
		timer.pause();
	}
}

void Wave::unpause() {
	if (status == IDLE) {		
		setStatus(RUNNING);
		timer.unpause();
	}
}

//*/////////

ShootWave::ShootWave(Vessel* v, Shmup* s) : Wave(s) {
	master = v;
}

ShootWave::ShootWave(Vessel* v, RawWave* raw, Shmup* s) : Wave(raw,s) {
	master = v;
}

void ShootWave::update() {
	if (raw->eow()) {
		status == TERMINATED;
		return;
	}
	if (status == RUNNING) {
		if (timer.getTime().asMilliseconds() >= next_moment) {
			std::vector<std::string> elements = raw->getByTime(next_moment);
			for (int i=0;i<elements.size();i++) {
				// interprete element
				if (master) {
//					std::cout << "eh" << std::endl;
					std::vector<std::string> elems = split(elements[i], ':');
					if (elems.size() && elems[0] == "projectile") {
						int type = std::stoi(elems[1]);
						std::string pattern_type = elems[2];
						int speed = std::stoi(elems[3]);
						double angle = std::stod(elems[4]);						
						game->procProjectile(type, pattern_type, speed, angle, master->position.x + offset.x, master->position.y + offset.y);
					}
				}
				else
				game->interprete(elements[i]);
			}
			next_moment = raw->getNextTime();
		}
	}
}
