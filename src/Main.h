#ifndef MAIN_H
#define MAIN_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <SDL3/SDL.h>

inline void ErrorMessage(const char* message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Engine Error!", message, NULL);
}

#endif