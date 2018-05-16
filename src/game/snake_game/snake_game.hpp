/// Since the SHMUP game doesn't work, I thought I would build a mock-up game
/// to help see how to use the 'engine'.

#ifndef SNAKE_GAME_HPP_
#define SNAKE_GAME_HPP_

#include "../../global.hpp"
#include "../../engine/time/timer.hpp"
#include "../../engine/scene.hpp"
#include "snake_tilemap.hpp"

class Sprite;

enum Direction {
	UP = 0b1, DOWN = 0b10, LEFT = 0b100, RIGHT = 0b1000, TAIL = 0b10000, HEAD = 0b100000
};

class SnakeGame : public Temporary {
public:
	SnakeGame() {}
	SnakeGame(const int& width, const int& height);
	
	void reset();
	void update();
	void handle_events(sf::Event&);
	
	sf::Vector2i head();
	std::vector<sf::Vector2i>& get_snake() { return snake; }
	sf::Vector2i tail();
	bool just_ate();
	
	Direction get_direction();
	void set_direction(Direction);
	std::map<sf::Vector2i, std::pair<Direction, Direction>> get_turn_stack();
	std::map<sf::Vector2i, int, cmpVec2i> get_snake_details();
private:
	void generate_snake(const int& i = 5);
	void generate_snack();
	
	int width = 0;
	int height = 0;
	
	std::vector<sf::Vector2i> snake;
	sf::Vector2i snack;
	Direction dir = UP;
	bool ate_last_time;
	
	// Register every turn, from and to
	std::map<sf::Vector2i, std::pair<Direction, Direction>> turn_stack;
};

std::map<sf::Vector2i, int, cmpVec2i> get_snake_turns(const std::vector<sf::Vector2i>& snake);

class SnakeGameScene : public Scene, public TimeEnabled {
public:
	SnakeGameScene(const int& width, const int& height);
//	~SnakeGameScene() { Scene::~Scene(); }
	
	void initialize();
	void terminate();
	void update();
	void toggle_pause();
	
	void handle_events(sf::Event& event);
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;
	
private:
	SnakeGame game;
	ptr_vector<sf::VertexArray> vertices;
	TileMap tmap;
};

#endif // SNAKE_GAME_HPP_