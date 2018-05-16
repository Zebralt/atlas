
#include <iostream>

#include "picture.hpp"

//int random(int min, int max) {
//	return rand()%(max-min)+min;
//}

Sprite::Sprite() : Blob() {
    //m_sprite.setTexture(m_texture);
}

Sprite::Sprite(sf::Texture* t) : Blob() {
	importTexture(t);
}

Sprite::Sprite(std::string s) : Blob() {
	setOwnTexture(s);
}

bool Sprite::setOwnTexture(std::string s) {
    m_texture = new sf::Texture();
    if (!m_texture->loadFromFile(s)) {
        return false;
    }
    else {
        m_sprite.setTexture(*m_texture);
        width = m_texture->getSize().x;
        height = m_texture->getSize().y;
        background.setSize(sf::Vector2f(width,height));
        return true;
    }
}

void Sprite::importTexture(sf::Texture* t) {
       if (t) {
			srand(time(NULL));
			m_texture = t;
			m_sprite.setTexture(*m_texture);
			//m_sprite.setColor(sf::Color(random(10,255),random(10,255),random(10,255)));
			width = m_texture->getSize().x;
			height = m_texture->getSize().y;
			background.setSize(sf::Vector2f(width,height));
       }
}

void Sprite::setTexture(sf::Texture* t) {
	importTexture(t);
}

void Sprite::setTexture(sf::Texture* t, sf::IntRect texrec) {
	importTexture(t);
	setTextureRect(texrec);
}

void Sprite::setTextureRect(sf::IntRect texrec) {
	m_sprite.setTextureRect(texrec);
	setSize(texrec.width, texrec.height);
	LOG("texrect");
}

void Sprite::setPosition(sf::Vector2f v) {
    Blob::setPosition(v);
    m_sprite.setPosition(position);
}

void Sprite::setOrigin(sf::Vector2f v) {
//    position = position - origin + v;
//    origin = v;
//    background.setPosition(position);
	Blob::setOrigin(v);
    m_sprite.setPosition(position);
}

void Sprite::setOpacity(int r) {
    opacity = (r>255?255:r<0?0:r);
    background.setFillColor(sf::Color(background.getFillColor().r,background.getFillColor().g,background.getFillColor().b,opacity));
    m_sprite.setColor(sf::Color(m_sprite.getColor().r,m_sprite.getColor().g,m_sprite.getColor().b,opacity));
}

void Sprite::setSize(int w, int h) {
	if (width && height) m_sprite.setScale(float(w)/width,float(h)/height);
	else m_sprite.setScale(w/1,h/1);
	Blob::setSize(w,h);
//	LOG((m_texture?"notnull":"null"));
//	LOG("SCALE=" << m_sprite.getScale().x * width << ":" << m_sprite.getScale().y * height);
//	LOG("SIZE=" << width << ":" << height);
}

void Sprite::setSize(const sf::Vector2i& v) {
	setSize(v.x, v.y);
}

void Sprite::rotate(float angle, sf::Vector2f p) {
	transform.rotate(angle,p);
}

/// ANIMATED PICTURE

AnimatedPicture::AnimatedPicture(int interval, int wait) : Sprite() {
    framePosition = sf::Vector2f(0,0);
    iterators = sf::Vector3i(0,0,0);
    repeat = false;
    this->interval = interval;
}

AnimatedPicture::AnimatedPicture(sf::Texture* t, int interval, int wait) : Sprite(t) {
    framePosition = sf::Vector2f(0,0);
    iterators = sf::Vector3i(0,0,0);
    repeat = false;
    this->interval = interval;
}

AnimatedPicture::AnimatedPicture(std::string str, int interval, int wait) : Sprite(str) {
    framePosition = sf::Vector2f(0,0);
    iterators = sf::Vector3i(0,0,0);
    repeat = false;
    this->interval = interval;
}


void AnimatedPicture::setFrameCount(int q) {
    quantity = q;
}

void AnimatedPicture::setFrameSize(sf::Vector2f v) {
	v = sf::Vector2f(v.x/cycle.y,v.y/cycle.x);
    this->frameSize = Size(v.x,v.y);
    width = v.x;
    height = v.y;
    background.setSize(sf::Vector2f(width,height));
//    m_sprite.setTextureRect(sf::IntRect(framePosition.x+iterators.y*frameSize.w,framePosition.y+iterators.z*frameSize.h,frameSize.w,frameSize.h));

}

void AnimatedPicture::setCycle(sf::Vector2i v) {
    cycle = sf::Vector2i(v.y,v.x);
}

void AnimatedPicture::setRefreshInterval(int interval) {
    this->interval = interval;
}

void AnimatedPicture::update() {
	Sprite::update();
	if (status == RUNNING) {
		int now = timer.getTime().asMilliseconds();
		if (now - past >= interval) {
			iterators.x++;
			iterators.z++;
			if (iterators.z >= cycle.y) { // colonnes
				iterators.y++;
				iterators.z = 0;
			}
			if (iterators.y >= cycle.x) { // lignes
				if (repeat)
					iterators = sf::Vector3i(0,0,0);
				else {
					LOG("i'm dead now");
					status = TERMINATED;
					//std::cout << "AnimatedPicture ended" << std::endl;
				}
			}
			if (iterators.x > quantity) {
				if (repeat)
					iterators = sf::Vector3i(0,0,0);
				else {
					LOG("i'm dead now");
					status = TERMINATED;
					//std::cout << "AnimatedPicture ended" << std::endl;
				}
			}

//			std::cout << iterators.x << ";" << iterators.y << ";" << iterators.z << std::endl;
			m_sprite.setTextureRect(sf::IntRect(framePosition.x+iterators.z*frameSize.w,framePosition.y+iterators.y*frameSize.h,frameSize.w,frameSize.h));
			setSize(width,height);
			//m_sprite.setTextureRect(sf::IntRect(0,0,20,20));

			past = now;
		}
	}
}
//
//bool AnimatedPicture::setOwnTexture(std::string s) {
//    m_texture = new sf::Texture();
//    if (!m_texture->loadFromFile(s)) {
//        return false;
//    }
//    else {
//        m_sprite.setTexture(*m_texture);
//        return true;
//    }
//}
//
//void AnimatedPicture::importTexture(sf::Texture* t) {
//        m_texture = t;
//        m_sprite.setTexture(*t);
//}

void AnimatedPicture::setRepeat(bool b) {
    repeat = b;
}
    
/// APSTATE

//APState::APState(int interval) : Animation(interval) {
//
//}
//
//APState::APState() : Animation(20) {
//
//}
//
//void APState::update() {
//    /*int now = clock.getElapsedTime().asMilliseconds();
//    if (now - past >= interval && isRunning()) {
//        iterators.x++;
//        iterators.z++;
//        if (iterators.z >= cycle.y) { // colonnes
//            iterators.y++;
//            iterators.z = 0;
//        }
//        if (iterators.y >= cycle.x) { // lignes
//            if (repeat)
//                iterators = sf::Vector3i(0,0,0);
//            else {
//                status = TERMINATED;
//                //std::cout << "AnimatedPicture ended" << std::endl;
//            }
//        }
//        if (iterators.x > length) {
//            if (repeat)
//                iterators = sf::Vector3i(0,0,0);
//            else {
//                status = TERMINATED;
//                //std::cout << "AnimatedPicture ended" << std::endl;
//            }
//        }
//
//    //	std::cout << iterators.x << ";" << iterators.y << ";" << iterators.z << std::endl;
//        target->setTextureRect(sf::IntRect(framePosition.x+iterators.z*frameSize.w,framePosition.y+iterators.y*frameSize.h,frameSize.w,frameSize.h));
//        //target->setTextureRect(sf::IntRect(0,0,20,20));
//
//        past = now;
//    }*/
//}
//
//void APState::reset() {
//}
//
///// LINKED ANIMATED PICTURE
//
//LinkedAnimatedPicture::LinkedAnimatedPicture() : Picture() {
//    
//}
//
//void LinkedAnimatedPicture::setState(std::string name) {
//    if (states.find(name) != states.end()) {
//        current_state = &states[name];
//        current_state->reset();
//    }
//    else {
//        LOG("error : no LAP state named " << name);
//    }
//}
//
//void LinkedAnimatedPicture::setDefaultState(std::string name) {
//    if (states.find(name) != states.end()) {
//        default_state = &states[name];
//        default_state->reset();
//    }
//    else {
//        LOG("error : no LAP state named " << name);
//    }
//}
//
//void LinkedAnimatedPicture::addState(std::string name, APState aps) {
//    aps.target = &m_sprite;
//    if (!default_state) default_state = &aps;
//    if (!current_state) current_state = &aps;
//    states[name] = aps;
//}
//
//void LinkedAnimatedPicture::update() {
//    // update animations
//    Blob::update();
//    
//    // update animating state
//    if (current_state->getStatus() == RUNNING) {
//        current_state->update();
//    }
//    else {
//        if (current_state->next) current_state = current_state->next;
//        else current_state = default_state;
//        default_state->reset();
//    }
//}

