#pragma once

namespace Thing2D {
	enum class PlatformOS {
		UNKNOW     = 0x0,
		MACOS      = 0x1,
		IOS_SIM    = 0x2,
		IOS_IPHONE = 0x3,
		WIN_386    = 0x4,
		WIN_X64    = 0x5,
		LINUX      = 0x6
	};

	class PlatformInfo {
	public:
		PlatformInfo(): debug_mode(false) {
#if defined(_DEBUG) 
  		debug_mode = true;
#else
  		debug_mode = false;
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   //define something for Windows (32-bit and 64-bit, this part is common)
   #ifdef _WIN64
      curr_platform_os = PlatformOS::WIN_X64;
   #else
      curr_platform_os = PlatformOS::WIN_386;
   #endif
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
      curr_platform_os = PlatformOS::IOS_SIM;
    #elif TARGET_OS_IPHONE
      curr_platform_os = PlatformOS::IOS_IPHONE;
    #elif TARGET_OS_MAC
      curr_platform_os = PlatformOS::MACOS;
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    	curr_platform_os = PlatformOS::LINUX;
#else
		#error "Unknown compiler"
#endif
		}

		PlatformOS get_platform_os() {
			return curr_platform_os;
		}

		bool is_windows() {
			return curr_platform_os == PlatformOS::WIN_386 || curr_platform_os == PlatformOS::WIN_X64;
		}

	private:
		PlatformOS curr_platform_os;
		bool debug_mode;
	};
}