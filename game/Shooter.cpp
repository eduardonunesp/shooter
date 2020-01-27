#include "Shooter.h"
#include "TiledMapLoader.h"
#include "PlayState.h"

namespace Shooter {
	ShooterGame::ShooterGame() :
		Game(800, 600) {}

	void ShooterGame::init() {
		Game::init();

		video_manager->load_texture("./assets/plane.png", "plane");
		video_manager->load_texture("./assets/shot.png", "shot");
		audio_manager->load_sound("./assets/boom.wav", "boom");

		tiled_map_loader = new Thing2D::TiledMapLoader(video_manager);
		tiled_map_loader->init();
		tiled_map_loader->load_tmx_map("./assets/map.tmx", "map");

		add_state("play_state", new PlayState(tiled_map_loader), true);
	}
}