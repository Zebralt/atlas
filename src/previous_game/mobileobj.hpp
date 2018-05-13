#ifndef mobile_obj_hpp
#define mobile_obj_hpp

#include "../graphics/graphic_obj.hpp"
#include "../graphics/ui/picture.hpp"

class Trajectory;

class Hitbox {
	bool collides(Hitbox*);
};

////////////////////////////////////////////////////////////////////////////////////
/// MODELS ///
////////////////////////////////////////////////////////////////////////////////////

enum Phasing {
	ONSCREEN,
	OFFSCREEN
};

class MobileObj : public Temporary {
public:
	MobileObj();
	~MobileObj();
	Trajectory* trajectory = nullptr;
	sf::Vector2f position;
	sf::Vector2f getPosition() { return position; }
	
	// that or custom hitbox
	int width;
	int height;
	Hitbox hitbox;
	
	// en toute logique, on delete l'objet quand il sort de l'ecran, mais si on veut le voir rentrer a nouveau (obligatoire au moins une fois :
	Phasing phasing = OFFSCREEN;
	short phasing_counter = 1; // the number of times the object can go offscreen. when = 0 and the object goes offscreen, it gets deleted
	
	// movement
	float speed = 0.5f;
	float orientation = 225;
	
	void setPosition(sf::Vector2f);
	void setPhasing(Phasing i);
	void setTrajectory(Trajectory* t);
	void move(sf::Vector2f);
	virtual void update();
};

class MobileObjView : public Picture {
public:
	MobileObjView(MobileObj*);
	
	MobileObj* model;
	float rotation = 0;
	
	virtual void update();
	void setPosition(sf::Vector2f);
};

struct MobileObj_MVC {
	MobileObj* model;
	MobileObjView* view;
};

/*class PelletView : public MobileObjView {
};

class VesselView : public MobileObjView {
};*/

/*	//Foster
	class Pattern;

	class MobileObj : public sf::Drawable {
	public:
		MobileObj();
		~MobileObj() {}

		void setPattern(Pattern& p);
		Pattern& getPattern();

		void setPosition(sf::Vector2f v);
		void setPosition(float x, float y);
		sf::Vector2f getPosition();

		virtual void update();

		virtual bool colliding() = 0;

		virtual sf::VertexArray getHitBox() = 0;

		void setTexture(sf::Texture& tex);

		void setRotation(float f);

		void setRadius(float f);

		void setScale(float x, float y);

	protected:
		Pattern* pattern;

		sf::Vector2f position;

		short int width;
		short int height;

		sf::CircleShape shape;
		sf::RectangleShape hitbox;
		sf::Sprite sprite;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
			//states.transform *= getTransform();
			target.draw(hitbox);
			target.draw(sprite);
			target.draw(shape);
		}
	};

	
*/
#endif // MOBILE_OBJ_HPP
