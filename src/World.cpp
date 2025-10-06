#include "Main.h"

#include <memory>

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"

#include "Renderer/stb_image.h"
#include "Renderer/Texture.h"
#include "Input.h"

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

Vec3 camPos(0.0f, 0.0f, 1.0f);
Vec3 camUp(0.0f, 1.0f, 0.0f);
Vec3 camFront(0.0f, 0.0f, -1.0f);

MATRIX model = Identity();
MATRIX view = ViewMatrixRH(
	camPos, camPos + camFront, camUp 
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

	return true;
}

float angleX = 0.0f, angleY = 0.0f;
Quaternion::QUATERNION quatX = Quaternion::FromAxisAngle(Vec3(0.0f, 1.0f, 0.0f), ToRadian(angleX));
Quaternion::QUATERNION quatY = Quaternion::FromAxisAngle(Vec3(1.0f, 0.0f, 0.0f), ToRadian(angleY));
Quaternion::QUATERNION quat = quatX * quatY;

void RenderWorld(float timeDelta)
{
	input->Update();

	float mouseSpeed = 100.0f * timeDelta;

	if (input->IsKeyDown(SDLK_UP))
		angleY += mouseSpeed;

	if (input->IsKeyDown(SDLK_DOWN))
		angleY -= mouseSpeed;

	if (input->IsKeyDown(SDLK_LEFT))
	    angleX += mouseSpeed;

	if (input->IsKeyDown(SDLK_RIGHT))
		angleX -= mouseSpeed;

	//FPS
	if (angleY > 89.0f)
		angleY = 89.0f;
	if (angleY < -89.0f)
		angleY = -89.0f;

	quatX = Quaternion::FromAxisAngle(Vec3(0.0f, 1.0f, 0.0f), ToRadian(angleX));
    quatY = Quaternion::FromAxisAngle(Vec3(1.0f, 0.0f, 0.0f), ToRadian(angleY));
	quat = quatX * quatY;

	camFront = Quaternion::RotateVector(quat, Vec3(0.0f, 0.0f, -1.0f));
	camFront = General::Normalize(camFront);

	float camSpeed = 2.0f * timeDelta;
	if (input->IsKeyDown(SDLK_W))
		camPos += camFront * camSpeed;

	if (input->IsKeyDown(SDLK_S))
		camPos -= camFront * camSpeed;

	if (input->IsKeyDown(SDLK_A))
		camPos -= General::Normalize(Cross(camFront, camUp)) * camSpeed;

	if (input->IsKeyDown(SDLK_D))
		camPos += General::Normalize(Cross(camFront, camUp)) * camSpeed;

	view = ViewMatrixRH(
		camPos, camPos + camFront, camUp
	);

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