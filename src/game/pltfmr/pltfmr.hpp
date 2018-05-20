#ifndef PLTFMR_HPP_
#define PLTFMR_HPP_

class LevelItem {
public:
	LevelItem() {}
	
private:
	Rect rect;
};

class Goon : public LevelItem {};
class DirtQuad : public LevelItem {};
class QuestionMarkBox : public LevelItem {};

class Level {
public:
	Level();
	
	void load_from_file(const std::string& filepath);
	
private:
	std::vector<sf::VertexArray> forms;
	ptr_vector<LevelItem> items;
	Vec2 player_start;
	Vec2 goal;
};

class Platformer : public Temporary {
public:
	Platformer();
	
	void update();
	
private:
	Level* level;
	Vec2 player_position;
	Sprite* player_sprite;
};

class PlatformerScene : public Scene {
public:
	PlatformerScene();
	
	void initialize();
	void terminate();
	void update();
	
private:
	Platformer pltfmr;
};

#endif // PLTFMR_HPP_