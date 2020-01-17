#pragma once

#include <iostream>

#ifdef _DEBUG
#define LOG(msg) \
    std::cout << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl 
#else
#define LOG(msg)
#endif