#include "Main.h"

#include <memory>

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"

#include "Renderer/stb_image.h"
#include "Renderer/Texture.h"
#include "Input.h"
#include "Renderer/Camera.h"
#include "Renderer/Light.h"

using namespace mdm;
using namespace Vector;
using namespace Matrix;
using namespace Transform;
using namespace Common;

extern SDL_Window* window;
extern bool run;

std::unique_ptr<Input> input;

std::unique_ptr<Renderer> renderer;

std::unique_ptr<Camera> camera;

MATRIX projection = PerspectiveMatrixRH(
	ToRadian(45.0f),
	(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
	0.1f, 100.0f
);

std::unique_ptr<Shader> shader;
std::unique_ptr<Cube> cube;

std::unique_ptr<Shader> l_shader;
std::unique_ptr<Cube> LightCube;

std::unique_ptr<Texture> container;
std::unique_ptr<Texture> container_s;
std::unique_ptr<Texture> container_n;

Light light = {
	Vec3(1.2f, 1.5f, 2.0f),
	Vec3(1.0f, 1.0f, 1.0f)
};

bool InitWorld()
{
	SDL_SetWindowTitle(window, "Decar");

	input = std::make_unique<Input>(window);

	renderer = std::make_unique<Renderer>(window);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	stbi_set_flip_vertically_on_load(true);

	camera = std::make_unique<Camera>(Vec3(0.0f, 0.0f, 3.0f));

	shader = std::make_unique<Shader>("resources/shaders/cube_vertex.txt", "resources/shaders/cube_fragment.txt");
	cube = std::make_unique<Cube>();

	l_shader = std::make_unique<Shader>("resources/shaders/light_vertex.txt", "resources/shaders/light_fragment.txt");
	LightCube = std::make_unique<Cube>();

	container = std::make_unique<Texture>("resources/container2.png");
	container_s = std::make_unique<Texture>("resources/container2_specular.png");
	container_n = std::make_unique<Texture>("resources/container2_normal.png");

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

	renderer->Clear(0.0f, 0.0f, 0.0f);

	shader->Use();
	shader->SetMatrix("model", ScaleMatrix(0.5f, 0.5f, 0.5f));
    shader->SetMatrix("view", camera->Matrix());
	shader->SetMatrix("projection", projection);
	shader->SetMatrix("normalMat", NormalMatrix(ScaleMatrix(0.5f, 0.5f, 0.5f)));
	shader->SetVec3("LightPos", light.pos);
	shader->SetVec3("LightColor", light.color);
	shader->SetVec3("camPos", camera->GetPos());
	shader->SetInt("container", 0);
	shader->SetInt("container_s", 1);
	shader->SetInt("container_n", 2);
	container->Bind(0);
	container_s->Bind(1);
	container_n->Bind(2);

	cube->Draw();

	l_shader->Use();
	l_shader->SetMatrix("model",TranslationMatrix(light.pos.x, light.pos.y, light.pos.z) * ScaleMatrix(0.2f, 0.2f, 0.2f));
	l_shader->SetMatrix("view", camera->Matrix());
	l_shader->SetMatrix("projection", projection);
	l_shader->SetVec3("LightColor", light.color);

	LightCube->Draw();

	renderer->Present();
}

void FreeWorld()
{

}