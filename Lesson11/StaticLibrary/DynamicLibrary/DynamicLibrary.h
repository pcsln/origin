#pragma once
#include <iostream>
#ifdef DYNAMICLIBRARY_EXPORTS
#define DYNAMICLIBRARY_API __declspec(dllexport)
#else
#define DYNAMICLIBRARY_API __declspec(dllimport)
#endif

class Leaver {
public:
	DYNAMICLIBRARY_API std::string leave(std::string str);
};