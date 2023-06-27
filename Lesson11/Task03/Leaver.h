#pragma once
#include <iostream>
#ifdef LEAVERLIBRARYDYNAMIC_EXPORTS
#define LEAVERLIBRARY_API __declspec(dllexport)
#else
#define LEAVERLIBRARY_API __declspec(dllimport)
#endif

class Leaver {
public:
	LEAVERLIBRARY_API std::string leave(std::string str);
};