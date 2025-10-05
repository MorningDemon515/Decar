#include "Main.h"

#include <memory>

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Renderer/stb_image.h"

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

unsigned int texture, texture1;

bool InitWorld()
{
	SDL_SetWindowTitle(window, "Decar");

	renderer = std::make_unique<Renderer>(window);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader = std::make_unique<Shader>("resources/shaders/vertex.txt", "resources/shaders/fragment.txt");
	Quad = std::make_unique<Mesh>(vertices, texCoords,indices);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load("resources/image.jpg", &width, &height, &nrChannels, 0);

	GLenum format;

	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	data = stbi_load("resources/image.png", &width, &height, &nrChannels, 0);

	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

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
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	Quad->Draw();

	renderer->Present();
}

void FreeWorld()
{

}