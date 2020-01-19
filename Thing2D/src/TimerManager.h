#pragma once

namespace Thing2D {
	class TimerManager {
	public: 
		static TimerManager* get_instance() {
			if (!instance) {
				instance = new TimerManager();
			}

			return instance;
		}

		int deltaTime;

	private:
		TimerManager() {}
		~TimerManager() {}

		static TimerManager* instance;
	};
}