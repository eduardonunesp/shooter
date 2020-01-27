#include "Shooter.h"
#include "PlayState.h"
#include <Thing2D/Tiled/Tiled.h>

using namespace Thing2D;

namespace Shooter {
	ShooterGame::ShooterGame() :
		Game(800, 600) {}

	void ShooterGame::init() {
		Game::init();

		video_manager->load_texture("./Assets/plane.png", "plane");
		video_manager->load_texture("./Assets/shot.png", "shot");
		audio_manager->load_sound("./Assets/boom.wav", "boom");

		Tiled::MapLoader* map_loader = new Tiled::MapLoader(video_manager);
		map_loader->load_tmx_map("./Assets/map.tmx", "map");
		
		PlayState* ps = new PlayState();
		ps->map = map_loader->get_map("map");
		add_state("play_state", ps, true);
	}
}