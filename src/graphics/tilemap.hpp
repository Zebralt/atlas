#ifndef SNAKE_TILEMAP_HPP_
#define SNAKE_TILEMAP_HPP_

#include "global.hpp"

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable {
public:
	TileMap() {}
	TileMap(unsigned int width, unsigned int height, sf::Vector2i tile_size);
	
	void set_texture(sf::Texture*);
	void update(int** grid);
	void update(const std::map<sf::Vector2i, int, cmpVec2i>&);
	void init(unsigned int width, unsigned int height, sf::Vector2i tile_size);
//	void init(const std::map<sf::Vector2i, int>& tiles, uint w, uint h, sf::Vector2i tile_size);
	
	void add_tileset(Rect r, unsigned int ind);
	void clear_textures();
	void set_margin(int i) {margin = i;}
	
	void draw(sf::RenderTarget& tar, sf::RenderStates st) const {
		st.texture = tex;
		tar.draw(vertices, st);
//		PRINTLN("everything hurts");
	}
	
private:
	unsigned int width;
	unsigned int height;
	sf::Vector2i tile_size;
	int margin = 0;

	sf::VertexArray vertices;
	sf::Texture* tex;
};


#endif // SNAKE_TILEMAP_HPP_