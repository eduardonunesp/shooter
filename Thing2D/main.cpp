#include "Thing2D.h"

using namespace Thing2D;

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
	PlayState() : spaceman(NULL) {}

	void init() {
		spaceman = new Spaceman();
		spaceman->add_animations("run", 12, false, 4, 1, 2, 3, 0);
		add(spaceman);
	}

protected:
	Spaceman* spaceman;
};

class MyGame : public Game {
public:
	MyGame() : Game(640, 480) {}

	void init() {
		Game::init();
		video_manager->load_texture("./assets/spaceman.png", "spaceman");
		add_state("play_state", new PlayState());
	}

private:
	PlayState play_state;
};

int main() {
	MyGame* game = new MyGame();
	game->init();
	game->run();
	delete game;

	return 0;
}