#ifdef _MSC_VER
#include <windows.h>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

#include "Main.h"

SDL_Window* window = nullptr;
SDL_WindowFlags windowFlags = SDL_WINDOW_OPENGL;

bool run = true;

bool InitWorld();
void RenderWorld(float timeDelta);
void FreeWorld();

int main()
{
	
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL3 Error!", "Failed to initialize SDL3!", NULL);
		return -1;
	}

	window = SDL_CreateWindow(
		"",
		WINDOW_WIDTH, WINDOW_HEIGHT,
		windowFlags
	);

	if (!window)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL3 Error!", "Unable to create window!", NULL);
		SDL_Quit();
		return -1;
	}

	if (!InitWorld())
	{
		ErrorMessage("Unable to initialize the world!");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	static float lastTime = (float)SDL_GetTicks();
	while (run)
	{
		float currentTime = (float)SDL_GetTicks();
		float timeDelta = (currentTime - lastTime) * 0.001f;

		RenderWorld(timeDelta);

		lastTime = currentTime;
		SDL_Delay(1);
	}

	FreeWorld();
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}