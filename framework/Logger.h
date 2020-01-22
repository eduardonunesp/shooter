#pragma once

#include <iostream>

#ifdef _DEBUG
#define LOG(msg) \
	std::cout << "INFO:" << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl

#define ERR(msg) \
	std::cout << "ERR:" << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl
#else
#define LOG(msg)
#define ERR(msg)
#endif
