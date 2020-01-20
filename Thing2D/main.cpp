#include "Thing2D.h"

using namespace Thing2D;

class PlayState : public State {
public:
	void init() {
		spaceman = new Sprite("spaceman", 200, 200, 8, 8, 4, 4);
		spaceman->add_animations("run", 12, false, 4, 1, 2, 3, 0);
		add(spaceman);
	}

	Sprite* spaceman;

	PlayState() : spaceman(NULL) {}
};

class MyGame : public Game {
public:
	MyGame() : Game(640, 480, 0) {
		add_state(&playState);
	}

	void init() {
		Game::init();
		load_texture("./assets/spaceman.png", "spaceman");
	}

	void load_texture(const std::string& path, const std::string& texture_id) {
		VideoManager::get_instance()->load_texture(path, texture_id);
	}

private:
	PlayState playState;
};

int main() {
	MyGame *game = new MyGame();
	game->init();
	game->run();
	game->destroy();

	return 0;
}