#include "Main.h"

#include <memory>

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"

#include "Renderer/stb_image.h"
#include "Renderer/Texture.h"

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
     Vec3(-0.5f, -0.5f, 0.0f),
	 Vec3(-0.5f, 0.5f, 0.0f),
	 Vec3(0.5f, 0.5f, 0.0f),

	 Vec3(-0.5f, -0.5f, 0.0f),
	 Vec3(0.5f, 0.5f, 0.0f),
	 Vec3(0.5f, -0.5f, 0.0f)
};

std::vector<Vec2> texCoords = {
    Vec2(0.0f, 0.0f),
	Vec2(0.0f, 1.0f),
	Vec2(1.0f, 1.0f),

	Vec2(0.0f, 0.0f),
	Vec2(1.0f, 1.0f),
	Vec2(1.0f, 0.0f)
};

std::vector<unsigned int> indices = {
	2, 1, 0,
	5, 4, 3
};

std::unique_ptr<Mesh> Quad;

MATRIX model = Identity();
MATRIX view = ViewMatrixRH(
	Vec3(0.0f, 0.0f, 1.0f),
	Vec3(0.0f, 0.0f, 0.0f),
	Vec3(0.0f, 1.0f, 0.0f)
);
MATRIX projection = PerspectiveMatrixRH(
	ToRadian(90.0f),
	(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
	0.1f, 100.0f
);

std::unique_ptr<Texture> texture1;
std::unique_ptr<Texture> texture2;

bool InitWorld()
{
	SDL_SetWindowTitle(window, "Decar");

	renderer = std::make_unique<Renderer>(window);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader = std::make_unique<Shader>("resources/shaders/texture_vertex.txt", "resources/shaders/texture_fragment.txt");
	Quad = std::make_unique<Mesh>(vertices, texCoords,indices);

	stbi_set_flip_vertically_on_load(true);

	texture1 = std::make_unique<Texture>("resources/image.jpg");
	texture2 = std::make_unique<Texture>("resources/image.png");

	return true;
}

void RenderWorld(float timeDelta)
{
	renderer->Clear(0.1f, 0.1f, 0.1f);

	shader->Use();
	shader->SetMatrix("model", model);
    shader->SetMatrix("view", view);
	shader->SetMatrix("projection", projection);

	shader->SetInt("Texture", 0);
	shader->SetInt("Texture1", 1);
	texture1->Bind(0);
	texture2->Bind(1);
	Quad->Draw();

	renderer->Present();
}

void FreeWorld()
{

}