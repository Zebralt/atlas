/// Since the SHMUP game doesn't work, I thought I would build a mock-up game
/// to help see how to use the 'engine'.

#ifndef SNAKE_GAME_HPP_
#define SNAKE_GAME_HPP_

#include "../../global.hpp"
#include "../../engine/time/timer.hpp"
#include "../../engine/scene.hpp"
#include "../../graphics/tilemap.hpp"

class Sprite;

enum Direction {
	UP = 0b1, DOWN = 0b10, LEFT = 0b100, RIGHT = 0b1000, TAIL = 0b10000, HEAD = 0b100000
};

/**
	\author Zebralt
	\brief This class implements the logic of a snake game.
*/
class SnakeGame : public Temporary {
public:
	SnakeGame() {}
	SnakeGame(const int& width, const int& height);
	
	/// \brief Resets the game.
	void reset();
	
	/// \brief Updates the game. Moves the snake, checks for loss condition,
	/// checks for snack and head collision, elongates the snake.
	void update();
	
	/// \brief Returns snake head position.
	sf::Vector2i head();
	std::vector<sf::Vector2i>& get_snake() { return snake; }
	
	/// \brief Returns snake tail end position.
	sf::Vector2i tail();
	
	/// \brief Tells if the snake sate at last update.
	/// Of use for the scene, as to know when to play the sound.
	bool just_ate();
	
	Direction get_direction();
	void set_direction(Direction);
	
	std::map<sf::Vector2i, int, cmpVec2i> get_snake_details();
private:
	
	/// \brief Generates a new snack for the snake.
	void generate_snake(const int& i = 5);
	
	/// \brief Generates the snake at the start of the game.
	void generate_snack();
	
	int width = 0;
	int height = 0;
	
	std::vector<sf::Vector2i> snake;
	sf::Vector2i snack;
	
	/// \brief The current direction to follow. It should be set
	/// when the player presses a key.
	Direction dir = UP;
	
	/// \brief Parameter used by method 'just_ate'.
	bool ate_last_time;
};

/// \brief As to know which sprite frame to use, we need to know
/// the orientation of each point of the snake. This method computes
/// the direction of each point of a list of points.
std::map<sf::Vector2i, int, cmpVec2i> get_snake_turns(const std::vector<sf::Vector2i>& snake);

/**
	\author Zebralt	
	\brief The scene/'view' counterpart of the snake game.
*/
class SnakeGameScene : public Scene, public TimeEnabled {
public:
	SnakeGameScene(const int& width, const int& height);
	
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