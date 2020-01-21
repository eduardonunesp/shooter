#include "Thing2D.h"

using namespace Thing2D;

class MyGame;

static MyGame* current_game = NULL;

class Spaceman : public Sprite {
public:
	Spaceman() : Sprite("spaceman", 200, 200, 8, 8, 4, 4) {}

	void update() {
		if (curr_animation->ended) {
			dead = true;
			visible = false;
			return;
		}

		Sprite::update();
	}
};

class PlayState : public State {
public:
	void init() {
		spaceman = new Spaceman();
		spaceman->add_animations("run", 12, false, 4, 1, 2, 3, 0);
		add(spaceman);
	}

	const std::string& state_id() override { return "play_state"; }

	void update() {
		State::update();
	}

	Spaceman* spaceman;

	PlayState() : spaceman(NULL) {}
};

class MyGame : public Game {
public:
	MyGame() : Game(640, 480, &play_state) {}

	void init() {
		Game::init();
		video_manager->load_texture("./assets/spaceman.png", "spaceman");
	}

private:
	PlayState play_state;
};

int main() {
	MyGame *game = new MyGame();
	current_game = game;
	game->init();
	game->run();
	game->destroy();

	return 0;
}