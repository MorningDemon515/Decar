#include "Main.h"

#include <memory>

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

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

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

unsigned int indices[] = {

	0, 1, 2
};

unsigned int VBO, VAO, EBO;

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
	shader = std::make_unique<Shader>("resources/shaders/vertex.txt", "resources/shaders/fragment.txt");

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return true;
}

void RenderWorld(float timeDelta)
{
	renderer->Clear(0.1f, 0.1f, 0.1f);

	shader->Use();
	shader->SetMatrix("model", model);
    shader->SetMatrix("view", view);
	shader->SetMatrix("projection", projection);
	glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	renderer->Present();
}

void FreeWorld()
{

}