#include "Sprite.h"
#include "Logger.h"
#include "VideoManager.h"
#include <cstdarg>

namespace Thing2D {
	Sprite::Sprite(const std::string& texture_id, float x, float y, int width, int height) :
		GameObject(texture_id, x, y, width, height), curr_animation(NULL) {
		calculate_frames(0, 0);
	}

	Sprite::Sprite(const std::string& texture_id, float x, float y, int width, int height, int rows, int cols):
		GameObject(texture_id, x, y, width, height), curr_animation(NULL) {
		calculate_frames(rows, cols);
	}

	Sprite::~Sprite() {
		destroy();
	}

	void Sprite::add_animations(const std::string& name, int speed, int frames, ...) {
		Animation* new_animation = new Animation();
		new_animation->anim_speed = speed;

		va_list marker;
		va_start(marker, frames);

		for (int i = 0; i < frames; i++) {
			LOG("Add animation with frame: " + std::to_string(i));
			new_animation->frames.push_back(va_arg(marker, int));
		}

		va_end(marker);
		animations[name] = new_animation;
		curr_animation = new_animation;
	}

	void Sprite::play(const std::string& animation_name) {
		Animation* animation = animations[animation_name];
		if (animation) {
			curr_animation = animation;
		}
	}

	void Sprite::update() {
		if (curr_animation) {
			int curr_anim_speed = curr_animation->anim_speed;
			int curr_anim_frame_size = curr_animation->frames.size();
			curr_animation->curr_anim_frame = int(((SDL_GetTicks() / (1000 / curr_anim_speed)) % curr_anim_frame_size));
		}

		GameObject::update();
	}

	void Sprite::draw()	{
		if (!visible) {
			return;
		}

		int curr_row = 0;
		int curr_col = 0;

		if (curr_animation) {
			Animation* animation = curr_animation;
			AnimFrame* anim_frame = anim_frames[animation->curr_anim_frame];
			curr_row = anim_frame->row;
			curr_col = anim_frame->col;
		}

		VideoManager::get_instance()->draw(texture_id, (int)position.x, (int)position.y, width, height, curr_row, curr_col, angle, alpha, SDL_FLIP_NONE);
	}

	void Sprite::destroy() {
		for (AnimFrame* anim_frame : anim_frames) {
			delete anim_frame;
		}
	}

	void Sprite::calculate_frames(int rows, int cols)	{
		for (int x = 0; x < rows; x++) {
			for (int y = 0; y < cols; y++) {
				LOG("Parse sprite frame " << x << ":" << y);
				anim_frames.push_back(new AnimFrame(x, y));
			}
		}
	}
}