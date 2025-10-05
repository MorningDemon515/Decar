#include "Main.h"

#include <memory>

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"

using namespace mdm;
using namespace Vector;
using namespace Matrix;
using namespace Transform;
using namespace Common;

extern SDL_Window* window;
extern SDL_Event event;
extern bool run;

std::unique_ptr<Renderer> renderer;
std::unique_ptr<Shader> shader;

std::vector<Vec3> vertices = {
     Vec3(-0.5f, 0.5f, 0.0f),
	 Vec3(-0.5f, -0.5f, 0.0f),
	 Vec3(0.5f, 0.5f, 0.0f),
	 Vec3(0.5f, -0.5f, 0.0f)
};

std::vector<unsigned int> indices = {
	1, 0, 2,
	1, 2, 3
};

std::unique_ptr<Mesh> Quad;

MATRIX model = Identity();
MATRIX view = ViewMatrixLH(
	Vec3(0.0f, 0.0f, -1.0f),
	Vec3(0.0f, 0.0f, 0.0f),
	Vec3(0.0f, 1.0f, 0.0f)
);
MATRIX projection = PerspectiveMatrixLH(
	ToRadian(90.0f),
	(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
	0.1f, 100.0f
);

bool InitWorld()
{
	SDL_SetWindowTitle(window, "Decar");

	renderer = std::make_unique<Renderer>(window);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	shader = std::make_unique<Shader>("resources/shaders/vertex.txt", "resources/shaders/fragment.txt");
	Quad = std::make_unique<Mesh>(vertices, indices);

	return true;
}

void RenderWorld(float timeDelta)
{
	renderer->Clear(0.1f, 0.1f, 0.1f);

	shader->Use();
	shader->SetMatrix("model", model);
    shader->SetMatrix("view", view);
	shader->SetMatrix("projection", projection);
	Quad->Draw();

	renderer->Present();
}

void FreeWorld()
{

}