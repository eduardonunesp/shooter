#define main SDL_main
#include <windows.h>
#include <Thing2D.h>

using namespace Thing2D;

class Animate : public Sprite {
public:
	enum class AnimateStates {
		RUNNING_RIGHT,
		RUNNING_LEFT
	};

	Animate() : Sprite("animate", 200, 200, 130, 82, 1, 6), speed(5.0f), curr_state(AnimateStates::RUNNING_RIGHT) {
		add_animations("run", 12, true, 6, 0, 1, 2, 3, 4, 5);
	}

	void update() override {
		switch (curr_state) {
		case AnimateStates::RUNNING_RIGHT:
			velocity = Vector::right() * speed;
			flipped = false;

			if (position.x + width >= game->get_screen_width()) {
				curr_state = AnimateStates::RUNNING_LEFT;
			}

			break;
		case AnimateStates::RUNNING_LEFT:
			velocity = Vector::left() * speed;
			flipped = true;

			if (position.x <= 0) {
				curr_state = AnimateStates::RUNNING_RIGHT;
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

		audio_manager->play_music("mode");
		playing = true;
	}

	void update() override {
		if (input_manager->is_key_up(SDL_SCANCODE_ESCAPE)) {
			if (playing) {
				audio_manager->stop_music("mode");
			} else {
				audio_manager->resume_music("mode");
			}

			playing = !playing;
		}

		State::update();
	}

protected:
	bool playing;
	Animate* animate;
};

class Sandbox : public Game {
public:
	Sandbox() : Game(640, 480) {}

	void init() override {
		Game::init();
		video_manager->load_texture("./assets/animate.png", "animate");
		audio_manager->load_music("./assets/mode.mp3", true, 60, "mode");
		add_state("play_state", new PlayState(), true);
	}

private:
	PlayState play_state;
};

int main(int argc, char* args[]) {
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
	printf("Debugging Window:\n");

	Sandbox* sandbox = new Sandbox();
	sandbox->init();
	sandbox->run();
	delete sandbox;

	return 0;
}