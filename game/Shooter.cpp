#include "Shooter.h"
#include "PlayState.h"

using namespace Thing2D;

namespace Shooter {
	ShooterGame::ShooterGame() :
		Game(800, 600) {}

	void ShooterGame::init() {
		Game::init();
		video_manager->load_texture("./assets/plane.png", "plane");
		video_manager->load_texture("./assets/shot.png", "shot");
		audio_manager->load_sound("./assets/boom.wav", "boom");
		add_state("play_state", new PlayState(), true);
	}
}