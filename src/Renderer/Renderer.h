#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "std.h"

class RENDERER_API Renderer
{
public:
	Renderer() { };
	Renderer(SDL_Window* window);
	~Renderer();

	void Clear(float r, float g, float b);
	void Present();

private:
	SDL_Window* window;
	SDL_GLContext glContext;
};


#endif // !RENDERER_H
