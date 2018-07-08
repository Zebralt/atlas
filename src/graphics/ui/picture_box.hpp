#ifndef PICTURE_BOX_HPP_
#define PICTURE_BOX_HPP_

#include "widget.hpp"
#include "picture.hpp"

// namespace atlas_engine {
//namespace Graphics {
//namespace gui {

class PictureBox : public Widget {
public:
	PictureBox();
	PictureBox(std::string s);
	PictureBox(sf::Texture* t);
	PictureBox(Sprite*);
	PictureBox(sf::Color);
	
	void setPosition(sf::Vector2f);
	void setSize(int,int);
	void setOpacity(int);
	void setOrigin(sf::Vector2f);
	void update();
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	
	Sprite* picture = nullptr;
	
	virtual ~PictureBox();
};

//}
//}
// } // namespace

#endif // PICTURE_BOX_HPP_