#include "Thing2D.h"

using namespace Thing2D;

class Spaceman : public Sprite {
public:
	Spaceman() : Sprite("spaceman", 200, 200, 8, 8, 4, 4), speed(1.0f) {
		add_animations("run", 12, true, 4, 1, 2, 3, 0);
		add_animations("idle", 0);
	}

	void update() override {
		velocity = Vector::zero();
		play("idle");

		if (input_manager->is_key_down(SDL_SCANCODE_RIGHT)) {
			play("run");
			velocity = Vector::right() * speed;
			flipped = false;
		}

		if (input_manager->is_key_down(SDL_SCANCODE_LEFT)) {
			play("run");
			velocity = Vector::left() * speed;
			flipped = true;
		}

		Sprite::update();
	}
protected:
	float speed;
};

class PlayState : public State {
public:
	PlayState() : spaceman(NULL) {}

	void init() override {
		spaceman = new Spaceman();
		add(spaceman);
	}

protected:
	Spaceman* spaceman;
};

class MyGame : public Game {
public:
	MyGame() : Game(640, 480) {}

	void init() override {
		Game::init();
		video_manager->load_texture("./assets/spaceman.png", "spaceman");
		add_state("play_state", new PlayState(), true);
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