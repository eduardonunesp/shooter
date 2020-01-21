#include "Thing2D.h"

using namespace Thing2D;

class Animate : public Sprite {
public:
	typedef enum {
		RUNNING_RIGHT,
		RUNNING_LEFT
	} AnimateStates;

	Animate() : Sprite("animate", 200, 200, 130, 82, 1, 6), speed(5.0f), curr_state(RUNNING_RIGHT) {
		add_animations("run", 12, true, 6, 0, 1, 2, 3, 4, 5);
	}

	void update() override {
		switch (curr_state) {
		case RUNNING_RIGHT:
			velocity = Vector::right() * speed;
			flipped = false;

			if (position.x + width >= game->get_screen_width()) {
				curr_state = RUNNING_LEFT;
			}

			break;
		case RUNNING_LEFT:
			velocity = Vector::left() * speed;
			flipped = true;

			if (position.x <= 0) {
				curr_state = RUNNING_RIGHT;
			}

			break;
		}

		Sprite::update();
	}
protected:
	float speed;
	AnimateStates curr_state;
	
};

class PlayState : public State {
public:
	PlayState() : animate(NULL) {}

	void init() override {
		animate = new Animate();
		add(animate);
	}

protected:
	Animate* animate;
};

class Sandbox : public Game {
public:
	Sandbox() : Game(640, 480) {}

	void init() override {
		Game::init();
		video_manager->load_texture("./assets/animate.png", "animate");
		add_state("play_state", new PlayState(), true);
	}

private:
	PlayState play_state;
};

int main() {
	Sandbox* sandbox = new Sandbox();
	sandbox->init();
	sandbox->run();
	delete sandbox;

	return 0;
}