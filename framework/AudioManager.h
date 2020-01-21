#pragma once

#include <string>
#include <map>
#include <SDL_mixer.h>

namespace Thing2D {
	class AudioManager {
	public:
		~AudioManager();

		void init();
		void load_music(const std::string& file_path, bool loop, int volume, const std::string& music_id);
		void play_music(const std::string& music_id);
		void stop_music(const std::string& music_id);
		void resume_music(const std::string& music_id);

	private:
		struct Sound {
			~Sound() {
				Mix_FreeChunk(mix_chunk);
			}

			void play();
			Mix_Chunk* mix_chunk;
		};

		struct Music {
			~Music() {
				Mix_FreeMusic(mix_music);
			}

			void play();
			void halt();
			void stop();
			void resume();

			bool loop;
			int volume;
			Mix_Music* mix_music;
		};

		std::map<std::string, Sound*> sounds;
		std::map<std::string, Music*> musics;
	};
}
