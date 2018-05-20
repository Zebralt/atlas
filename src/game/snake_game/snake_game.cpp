#include "snake_game.hpp"
#include "../../engine/engine.hpp"
#include "../../graphics/ui/picture.hpp"
//#include "../tools/vector2_operators.hpp"

#include <ctime>

int randint(int a, int b) {
	return rand()%(b - a) + a;
}

SnakeGame::SnakeGame(const int& w, const int& h) : Temporary() {
	width = w;
	height = h;
	reset();
}

void SnakeGame::reset() {
	setStatus(IDLE);
	generate_snake();
	generate_snack();
}

void SnakeGame::generate_snake(const int& initial_len) {
	auto initial_pos = sf::Vector2i(randint(0, width - 1), randint(0, height - 1));
	snake.push_back(initial_pos);
	for (uint i=1; i<initial_len; i++) {
		snake.push_back(sf::Vector2i(initial_pos.x, initial_pos.y + i));
	}
}

void SnakeGame::generate_snack() {
	srand(time(NULL));
	do {
		snack = sf::Vector2i(randint(0, width - 1), randint(0, height - 1));
	} while (std::find(snake.begin(), snake.end(), snack) != snake.end());
}

bool SnakeGame::just_ate() {
	return ate_last_time;
}

Direction SnakeGame::get_direction() {
	return dir;
}

std::map<sf::Vector2i, std::pair<Direction, Direction>> SnakeGame::get_turn_stack() {
	return turn_stack;
}

void SnakeGame::update() {
	if (status) {
		// check for snake overlap
		if (std::find(snake.begin() + 1, snake.end(), head()) != snake.end()) {
			status = TERMINATED;
			return;
		}
		// update with current direction
		// move snake
//		for (uint i=0; i<snake.size(); i++) {
//			snake[i].x += (dir == RIGHT) - (dir == LEFT);
//			snake[i].y += (dir == DOWN) - (dir == UP);
//			if (snake[i].x < 0) { snake[i].x = width + snake[i].x;}
//			else if (snake[i].x >= width) { snake[i].x -= width;}
//			if (snake[i].y < 0) { snake[i].y = height + snake[i].y;}
//			else if (snake[i].y >= height) { snake[i].y -= height;}
//			
//			// check for overlap
//			if (i && snake[0] == snake[i]) {
//				status = TERMINATED;
//				return;
//			}
//		}

		auto new_head = sf::Vector2i(head());
		new_head.x += (dir == RIGHT) - (dir == LEFT);
		new_head.y += (dir == DOWN) - (dir == UP);
		if (new_head.x < 0) { new_head.x = width + new_head.x;}
		else if (new_head.x >= width) { new_head.x -= width;}
		if (new_head.y < 0) { new_head.y = height + new_head.y;}
		else if (new_head.y >= height) { new_head.y -= height;}
		snake.insert(snake.begin(), new_head);
		snake.pop_back();
		
		// if head on food : lengthen snake, generate new food
		if (snake[0] == snack) {
			sf::Vector2i tail = snake[snake.size() - 1];
			snake.push_back(sf::Vector2i(tail.x + (dir == LEFT) - (dir == RIGHT), tail.y + (dir == UP) - (dir == DOWN)));
			generate_snack();
			ate_last_time = true;
		}
		else {
			ate_last_time = false;
		}
	}
}

void SnakeGame::set_direction(Direction d) {
	if (d != dir) {
//		turn_stack[head()] = std::pair<Direction, Direction>(dir, d);
	}
	dir = d;
}

sf::Vector2i SnakeGame::head() {
	return snake[0];
}

sf::Vector2i SnakeGame::tail() {
	return snake[snake.size() - 1];
}
//enum SNAKE_SPRITE { 
//	HEAD_UP = 3,
//	HEAD_RIGHT = 4,
//	HEAD_LEFT = 8,
//	HEAD_DOWN = 9,
//	TAIL_UP = 13,
//	TAIL_RIGHT = 14,
//	TAIL_LEFT = 18,
//	TAIL_DOWN = 19,
//	UP_TO_RIGHT = 0,
//	HORIZONTAL = 1,
//	LEFT_TO_DOWN = 2,
//	VERTICAL = 7,
//	TOP_TO_RIGHT = 5,
//	TOP_TO_LEFT = 12,	
//	FOOD = 15
//};
//
//namespace SnakeSpriteValues {
//	namespace Head {
//		int up = 3;
//		int right = 4;
//		int left = 8;
//		int down = 9;
//	}
//	namespace Tail {
//		int up = 13;
//		int right = 14;
//		int left = 18;
//		int down = 19;
//	}
//	int vertical = 7;
//	int horizontal = 1;
//	namespace Turn {
//		namespace up {
//			int right = 5;
//			int left = 12;
//		}
//		namespace down {
//			int right = 0;
//			int left = 2;
//		}
//		namespace left {
//			int up = 12;
//			int down = 2;
//		}
//		namespace right {
//			int up = 5;
//			int down = 0;
//		}
//	}	
//}

std::map<int, int> get_sprite_values() {
	std::map<int, int> sss;
	
	sss[UP] = sss[DOWN] = 7;//VERTICAL;
	sss[LEFT] = sss[RIGHT] = 1;//HORIZONTAL;
	sss[UP|LEFT] = 12;//SnakeSpriteValues::Turn::up::left;
	sss[UP|RIGHT] = 5;//SnakeSpriteValues::Turn::up::right;
	sss[DOWN|LEFT] = 2;//SnakeSpriteValues::Turn::down::left;
	sss[DOWN|RIGHT] = 0;//SnakeSpriteValues::Turn::down::right;
	sss[TAIL|UP] = 19;//SnakeSpriteValues::Tail::up;
	sss[TAIL|DOWN] = 13;//SnakeSpriteValues::Tail::down;
	sss[TAIL|LEFT] = 14;//SnakeSpriteValues::Tail::left;
	sss[TAIL|RIGHT] = 18;//SnakeSpriteValues::Tail::right;
	sss[HEAD|UP] = 3;//SnakeSpriteValues::Head::up;
	sss[HEAD|DOWN] = 9;//SnakeSpriteValues::Head::down;
	sss[HEAD|LEFT] = 8;//SnakeSpriteValues::Head::left;
	sss[HEAD|RIGHT] =4;// SnakeSpriteValues::Head::right;
	return sss;
}

std::string dir_string(int val) {
	std::string str = ""; //std::to_string(val) + " = ";
	if (val & LEFT) str += "LEFT:";
	if (val & RIGHT) str += "RIGHT:";
	if (val & DOWN) str += "DOWN:";
	if (val & UP) str += "UP:";
	if (val & HEAD) str += "HEAD:";
	if (val & TAIL) str += "TAIL:";
	return str;
}

std::map<sf::Vector2i, int, cmpVec2i> get_snake_turns(const std::vector<sf::Vector2i>& snake) {
	
	auto values = get_sprite_values();
	
	
	std::map<sf::Vector2i, int, cmpVec2i> details;
	std::vector<int> directions;
	
	Direction adir;
	Direction new_dir;
	sf::Vector2i diff;
	for (uint i=0;i<snake.size();i++) {
		if (!i) {
			// head
			// look next
			diff = snake[i] - snake[i+1];
			new_dir = diff.x ? (diff.x < 0 ? LEFT : RIGHT) : (diff.y ? (diff.y < 0 ? UP : DOWN) : DOWN);
			details[snake[i]] = values[HEAD|new_dir];
			directions.push_back(HEAD|new_dir);
		}
		else {
			// look previous
			diff = snake[i-1] - snake[i];
			new_dir = diff.x ? (diff.x > 0 ? LEFT : RIGHT) : (diff.y ? (diff.y > 0 ? UP : DOWN) : DOWN);
			if (adir != new_dir && i > 1) {
				// the serpent turns here
				details[snake[i - 1]] = values[adir|new_dir];
				directions[directions.size() - 1] = adir|new_dir;
			}
			details[snake[i]] = values[i < snake.size() - 1 ? new_dir : TAIL|new_dir];
			directions.push_back(i < snake.size() - 1 ? new_dir : TAIL|new_dir);
		}
		
		adir = new_dir;

	}
	
	// display snake
	// display directions
//	for (auto dir : directions) {
//		LOG(dir_string(dir));
//	}
	// display turns
	int i = 0;
	for (auto it = details.begin(); it != details.end(); ++it, ++i) {
		LOG(it->first << " : " << it->second << " => " << dir_string(directions[i]));
	}
	
//	exit(0);
	
	return details;
}

std::map<sf::Vector2i, int, cmpVec2i> SnakeGame::get_snake_details() {
	auto details = get_snake_turns(snake);
	details[snack] = 15;
	return details;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

SnakeGameScene::SnakeGameScene(const int& w = 40, const int& h = 40) : Scene() {
	game = SnakeGame(w, h);
	tmap.init(w,h,sf::Vector2i(320/5, 256/4));
}

void SnakeGameScene::initialize() {
	// load resources
	Engine::load(TEXTURE, "snake_spritesheet", "resources/textures/snake_graphics/snake-graphics.png");
	tmap.set_texture(Engine::get().get_texture("snake_spritesheet"));
	Engine::load(SOUND, "snake_eating", "resources/sfx/munch.ogg");
	
	// load spritesheet settings
//	Settings sprite_settings("resources/textures/snake-graphics-settings.xml");
	// compute canvas and sizes
}

void SnakeGameScene::toggle_pause() {
	if (status == RUNNING) setStatus(IDLE), timer.pause();
	else if (status == IDLE) setStatus(RUNNING), timer.unpause();
	LOG("PAUSE");
}

void SnakeGameScene::handle_events(sf::Event& event) {
	// capture keyboard events for UP,LEFT,RIGHT,DOWN
	if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
			game.set_direction(UP);
        }
        else if (event.key.code == sf::Keyboard::Down) {
			game.set_direction(DOWN);
        }
        else if (event.key.code == sf::Keyboard::Left) {
        	game.set_direction(LEFT);
        }
        else if (event.key.code == sf::Keyboard::Right) {
            game.set_direction(RIGHT);
        }
        else if (event.key.code == sf::Keyboard::R) {
			game.reset();
        }
        else if (event.key.code == sf::Keyboard::Space) {
			toggle_pause();
        }
	}
}

void SnakeGameScene::update() {
	int now = timer.time().asMilliseconds();
	if (status == RUNNING && now - past > 1000) {
		game.update();
		auto details = game.get_snake_details();
		tmap.update(details);
		if (game.getStatus()) {
			if (game.just_ate()) {
				Engine::play("snake_eating");
			}
		}
		else {
			status = TERMINATED;
		}
		past = now;
	}
}

void SnakeGameScene::draw(sf::RenderTarget& target, sf::RenderStates stt) const {
	// call base class::draw
	// draw background
	// draw head
	// rotate head
	// draw tail
	// rotate tail
	// draw rest of the body
	
	// draw tmap
	target.draw(tmap, stt);
}

void SnakeGameScene::terminate() {
	for (auto ptr : vertices) {
		if (ptr) delete ptr;
	}
}

/*
class SnakeGameApplication(minapp.MiniApplication):
    def __init__(self, settings, w=40, h=40):
        self.w = w
        self.h = h
        super().__init__(settings)
    
    def init(self):

        self.snake_game = asnake.SnakeGame(self.w, self.h)        
        self.rect_size = min(self.settings.window_rect)/min(self.snake_game.grid.width, self.snake_game.grid.height)
        self.rect_size = int(self.rect_size/3)
        self.margin = 1
        self.main_grid_pos = (int(min(self.settings.window_rect)/3), int(min(self.settings.window_rect)/3))
        
        
        
    def close(self):
        print("What, you're leaving already ? how sad.")
        
    def update(self):
        # do something
        self.bg_rect = (self.main_grid_pos, ((self.rect_size + self.margin) * self.snake_game.grid.width, (self.rect_size + self.margin) * self.snake_game.grid.height))
        pygame.draw.rect(self.window, (40, 20, 30), scale_rect(self.bg_rect, 1.25))
        pygame.draw.rect(self.window, (20, 20, 30), self.bg_rect)
        self.grid = self.snake_game.run()
        
    def draw(self):
        # do smth
        if self.grid:
            for i in range(self.grid.width):
                for j in range(self.grid.height):
                    rect = ((self.main_grid_pos[0] + (self.rect_size + self.margin) * i, self.main_grid_pos[1] + (self.rect_size + self.margin) * j ),(self.rect_size, self.rect_size))
                    if (i, j) == self.snake_game.food:      
                        pygame.draw.rect(self.window, Color.orange, scale_rect(rect, 2))
                    elif (i ,j) == self.snake_game.snake[0]:      
                        pygame.draw.rect(self.window, Color.yellow,  scale_rect(rect, 1.5))
                    elif self.grid.get(i, j):
                        pygame.draw.rect(self.window, Color.white, rect)
                    elif self.snake_game.path and (i, j) in self.snake_game.path:                        
                        pygame.draw.rect(self.window, (100, 100, 100),  scale_rect(rect, 0.5))
        
    def handle_event(self, events):
        for event in events:
            if event.type == QUIT:
                self.state = 0
            if event.type == MOUSEBUTTONDOWN:
                if event.button == MouseButton.left:
                    self.snake_game.reset()
                    self.settings.mousepos = event.pos
            if event.type == MOUSEBUTTONUP:
                if event.button == MouseButton.right:
                    pass
            if event.type == MOUSEMOTION:
                self.settings.mousepos = event.pos
    
*/

//std::vector<Direction> figure_turns(const std::vector<sf::Vector2i>& poss) {
//	std::vector<Direction> directions;
//	Direction last_dir = UP;
//	const sf::Vector2i* current_dir = nullptr;
//
//	for (auto& pos : poss) {
//		if (current_dir) {
//			if (directions.size()) {
//				
//			}
//			else {
//				int dx = current_dir->x - pos.x;
//				int dy = current_dir->y - pos.y;
//				Direction new_dir = dx ? (dx > 0 ? LEFT : RIGHT) : (dy ? (dy > 0 ? UP : DOWN) : DOWN);
//				if (new_dir != last_dir) {
////					directions.push_back()
//				}
//				last_dir = new_dir;
//			}
//		}
//		current_dir = &pos;
//	}
//
//	return directions;
//}
