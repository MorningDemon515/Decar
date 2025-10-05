#ifndef MAIN_H
#define MAIN_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <iostream>
#include <SDL3/SDL.h>

inline void ErrorMessage(std::string message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Engine Error!", message.c_str(), NULL);
}

#endif