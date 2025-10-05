#include "Renderer.h"
#include "../Main.h"

Renderer::Renderer(SDL_Window* window)
{
	this->window = window;

	glContext = SDL_GL_CreateContext(window);
	if (!glContext)
	{
		ErrorMessage("Failed to create OpenGL Context!");
	}

	SDL_GL_MakeCurrent(window, glContext);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		ErrorMessage("Failed to Initialize OpenGL!");
	}
}

Renderer::~Renderer()
{
	SDL_GL_DestroyContext(glContext);
}

void Renderer::Clear(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Present()
{
	SDL_GL_SwapWindow(window);
}