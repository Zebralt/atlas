#ifndef picture_hpp__
#define picture_hpp__

#include <SFML/Graphics.hpp>

#include "global.hpp"
#include "graphics/graphic_obj.hpp"
#include "engine/timer.hpp"

// namespace atlas_engine {
//namespace Graphics {

int random(int,int);

class Sprite : public Blob {
public:
    Sprite();
    Sprite(sf::Texture*);
    Sprite(std::string);
    
    bool setOwnTexture(std::string path);

    void importTexture(sf::Texture* t);

    void setPosition(sf::Vector2f v);
    void setOrigin(sf::Vector2f v);
    void setOpacity(int r);
    void setSize(int w, int h);
    void setSize(const sf::Vector2i& v);
    
    void setTexture(sf::Texture*);
    void setTexture(sf::Texture* t, sf::IntRect);
    void setTextureRect(sf::IntRect);
    
    sf::Texture* getTexture() {
		return m_texture;
    }
    
    void rotate(float angle, sf::Vector2f);

protected:
	// rotate around point :
	// https://stackoverflow.com/questions/28521707/how-to-rotate-a-shape-around-a-point
	sf::Transform transform;
    sf::Sprite m_sprite;
    sf::Texture* m_texture;

    virtual void draw(sf::RenderTarget& tar,sf::RenderStates states) const {
//        states.transform *= getTransform();
        //tar.draw(background);
        Blob::draw(tar,states);
//        LOG("SCALE=" << m_sprite.getScale().x * width << ":" << m_sprite.getScale().y * height);
//		LOG("SIZE=" << width << ":" << height);
        tar.draw(m_sprite,transform);
    }
};

//////////////////////////////////////////////////////////////

class AnimatedPicture : public Sprite, public TimeEnabled {
public:
    AnimatedPicture(int interval, int wait = 0);
    AnimatedPicture(std::string, int interval, int wait = 0);
    AnimatedPicture(sf::Texture*, int interval, int wait = 0);
    void setFrameCount(int q);
    
    // the size of the whole sprite sheet where the tiles are
    void setFrameSize(sf::Vector2f s);
    //void setFramePosition(sf::Vector2f v);
    
    // will be used if the sprite sheet isn't adjusted with the tiles
    void setOffset(sf::Vector2f);
    
    // col then line
    void setCycle(sf::Vector2i cycle);
    void setRefreshInterval(int interval);
    void setRepeat(bool b);
    void update();
private:
    bool repeat = false;
    sf::Vector2f offset;
    sf::Vector2i cycle;
    sf::Vector3i iterators;
    Size frameSize;
    sf::Vector2f framePosition;
    int quantity = 0;
    int interval = 0;
	int past = 0;

};

// exemple :

//zegui::AnimatedPicture apa(gui,60);
//	apa.setPicture("lvxdmali.png");
//	apa.setPosition(sf::Vector2f(20,150));
//	apa.setFrameCount(20);
//	apa.setFrameSize(sf::Vector2f(96,96));
//	apa.setCycle(sf::Vector2i(4,5));
//	//apa.setRefreshInterval(60);

// A linkedAnimatedPicture state
//class APState : public Animation {
//public:
//    APState();
//    APState(int);
//    
//    int length;
//    sf::Vector2i cycle;
//    sf::Vector3i iterators;
//    Size frameSize;
//    sf::Vector2f framePosition;
//    bool repeat;
//    bool inverse;
//    APState* next;
//    std::map<int,int> frame_delays;
//    void update();
//    void reset();
//    sf::Sprite* target;
//};
//
//class LinkedAnimatedPicture : public virtual Picture {
//    std::map<std::string, APState> states;
//    APState* current_state;
//    APState* default_state;
//public:
//    LinkedAnimatedPicture();
//    
//    void update();
//    void setState(std::string name);
//    void setDefaultState(std::string name);
//    void addState(std::string name, APState);
//    
//};

//}
// } // namespace

#endif
