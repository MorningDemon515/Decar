#include "Main.h"

#include <memory>

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"

#include "Renderer/stb_image.h"
#include "Renderer/Texture.h"
#include "Input.h"
#include "Renderer/Camera.h"

using namespace mdm;
using namespace Vector;
using namespace Matrix;
using namespace Transform;
using namespace Common;

extern SDL_Window* window;
extern bool run;

std::unique_ptr<Input> input;

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

std::unique_ptr<Camera> camera;

MATRIX model = Identity();
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

	input = std::make_unique<Input>(window);

	renderer = std::make_unique<Renderer>(window);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader = std::make_unique<Shader>("resources/shaders/texture_vertex.txt", "resources/shaders/texture_fragment.txt");
	Quad = std::make_unique<Mesh>(vertices, texCoords,indices);

	stbi_set_flip_vertically_on_load(true);

	texture1 = std::make_unique<Texture>("resources/image.jpg");
	texture2 = std::make_unique<Texture>("resources/image.png");

	camera = std::make_unique<Camera>(Vec3(0.0f, 0.0f, 1.0f));

	return true;
}

void RenderWorld(float timeDelta)
{
	input->Update();

	float mouseSpeed = 100.0f * timeDelta;
	float moveSpeed = 2.0f * timeDelta;

	if (input->IsKeyDown(SDLK_UP))
		camera->Pitch(mouseSpeed);

	if (input->IsKeyDown(SDLK_DOWN))
		camera->Pitch(-mouseSpeed);

	if (input->IsKeyDown(SDLK_LEFT))
		camera->Yaw(mouseSpeed);

	if (input->IsKeyDown(SDLK_RIGHT))
		camera->Yaw(-mouseSpeed);

	if (input->IsKeyDown(SDLK_W))
		camera->Forward(moveSpeed);

	if (input->IsKeyDown(SDLK_S))
		camera->Back(moveSpeed);

	if (input->IsKeyDown(SDLK_A))
		camera->Left(moveSpeed);

	if (input->IsKeyDown(SDLK_D))
		camera->Right(moveSpeed);

	renderer->Clear(0.1f, 0.1f, 0.1f);

	shader->Use();
	shader->SetMatrix("model", model);
    shader->SetMatrix("view", camera->Matrix());
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