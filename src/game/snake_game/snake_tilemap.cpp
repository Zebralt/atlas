#include "snake_tilemap.hpp"

TileMap::TileMap(unsigned int w, unsigned int h, sf::Vector2i ts) {
	
	init(width, height, tile_size);
}

void TileMap::init(unsigned int w, unsigned int h, sf::Vector2i ts) {

	width = w;
	height = h;
	tile_size = ts;
	
	vertices.clear();
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(width * height * 4);
	
	for (unsigned int i = 0; i<width; i++) {
		for (unsigned int j = 0; j<height; ++j) {
			
			sf::Vertex* quad = &vertices[(i + j * width) * 4];
			quad[0].position = sf::Vector2f(i * tile_size.x, j * tile_size.y);
			quad[1].position = sf::Vector2f((i + 1) * tile_size.x, j * tile_size.y);
			quad[2].position = sf::Vector2f((i + 1) * tile_size.x, (j + 1) * tile_size.y);
			quad[3].position = sf::Vector2f(i * tile_size.x, (j + 1) * tile_size.y);
			
		}
	}
}

void TileMap::update(const std::map<sf::Vector2i, int, cmpVec2i>& tiles) {
	clear_textures();
	for (auto it = tiles.begin(); it != tiles.end(); ++it) {
			
			int tile_number = it->second;
			int i = it->first.x;
			int j = it->first.y;
			
			sf::Vertex* quad = &vertices[(i + j * width) * 4];
			
//			for (int i=0; i<20; i++) {
//				tile_number = i;
//				
//				int tu = tile_number % (tex->getSize().x / tile_size.x);
//				int tv = tile_number / (tex->getSize().x / tile_size.x);
//			
//				LOG	(tile_number << "= " << tu << ", " << tv);
//			}
//			
//			exit(0);
				
			int tu = tile_number % (tex->getSize().x / tile_size.x);
			int tv = tile_number / (tex->getSize().x / tile_size.x);
			
			quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
			quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
			
	}
}

void TileMap::update(int** grid) {
	if (!grid) return;
	for (unsigned int i = 0; i<width; i++) {
		for (unsigned int j = 0; j<height; ++j) {
				
			int tile_number = grid[i][j];
			
			sf::Vertex* quad = &vertices[(i + j * width) * 4];
			
			int tu = tile_number % (tex->getSize().x / tile_size.x);
			int tv = tile_number / (tex->getSize().y / tile_size.y);
			
			quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
			quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
			
		}
	}
}

void TileMap::clear_textures() {
	
	for (unsigned int i = 0; i<width; i++) {
		for (unsigned int j = 0; j<height; ++j) {
			
			sf::Vertex* quad = &vertices[(i + j * width) * 4];
			
			for (int k=0; k<4; k++) {
				quad[k].texCoords = sf::Vector2f(0, 0);
			}
		}
	}
	
}

void TileMap::set_texture(sf::Texture* t) {
	tex = t;
}