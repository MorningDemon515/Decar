#include "Sprite.h"

#include <glad/glad.h>

Sprite::Sprite(std::vector<mdm::Vector::Vec4> vertices, std::vector<unsigned int> indices)
{

	indicesCount = indices.size();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(mdm::Vector::Vec4), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(mdm::Vector::Vec4), (void*)0);
	glEnableVertexAttribArray(0);

	shader = std::make_unique<Shader>("resources/shaders/sprite_vertex.txt", "resources/shaders/sprite_fragment.txt");

}

Sprite::Sprite(std::vector<mdm::Vector::Vec4> vertices, std::vector<unsigned int> indices, const char* file)
{

	indicesCount = indices.size();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(mdm::Vector::Vec4), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(mdm::Vector::Vec4), (void*)0);
	glEnableVertexAttribArray(0);

	shader = std::make_unique<Shader>("resources/shaders/sprite_vertex.txt", "resources/shaders/sprite_fragment.txt");

	texture = std::make_unique<Texture>(std::string(file));
}

Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Sprite::SetColor(int r, int g, int b)
{
	shader->Use();
	shader->SetVec3("fragColor", mdm::Vector::Vec3((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f));
}

void Sprite::SetTexture()
{
	shader->Use();
	shader->SetInt("image", true);
	shader->SetInt("imageTex", 0);
	texture->Bind(0);
}

void Sprite::Draw(int x,int y, int scale)
{
	shader->Use();
	shader->SetMatrix("projection", projection);
	shader->SetMatrix("model", mdm::Transform::TranslationMatrix((float)x, (float)y, 0.0f) *
		                     mdm::Transform::ScaleMatrix((float)scale, (float)scale, (float)scale));
	glDisable(GL_DEPTH_TEST);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
}

Rect::Rect(rect_t rect)
{
	x = rect.x; y = rect.y;
	std::vector<mdm::Vector::Vec4> vertices = {
		mdm::Vector::Vec4(0.0f, 0.0f,					0.0f, 1.0f),
		mdm::Vector::Vec4((float)rect.w, 0.0f,			1.0f ,1.0f),
		mdm::Vector::Vec4((float)rect.w, (float)rect.h,	1.0f, 0.0f),

		mdm::Vector::Vec4(0.0f, 0.0f,					0.0f, 1.0f),
		mdm::Vector::Vec4(0.0f, (float)rect.h,			0.0f, 0.0f),
		mdm::Vector::Vec4((float)rect.w, (float)rect.h,	1.0f ,0.0f)
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		3, 4, 5
	};

	sprite = std::make_unique<Sprite>(vertices, indices);
}

Rect::Rect(rect_t rect, const char* file)
{
	x = rect.x; y = rect.y;
	std::vector<mdm::Vector::Vec4> vertices = {
		mdm::Vector::Vec4(0.0f, 0.0f,					0.0f, 1.0f),
		mdm::Vector::Vec4((float)rect.w, 0.0f,			1.0f ,1.0f),
		mdm::Vector::Vec4((float)rect.w, (float)rect.h,	1.0f, 0.0f),

		mdm::Vector::Vec4(0.0f, 0.0f,					0.0f, 1.0f),
		mdm::Vector::Vec4(0.0f, (float)rect.h,			0.0f, 0.0f),
		mdm::Vector::Vec4((float)rect.w, (float)rect.h,	1.0f ,0.0f)
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		3, 4, 5
	};

	sprite = std::make_unique<Sprite>(vertices, indices, file);
}

Rect::~Rect()
{

}

void Rect::SetTexture()
{
	sprite->SetTexture();
}

void Rect::SetColor(int r, int g, int b)
{
	sprite->SetColor(r, g, b);
}

void Rect::Draw(int x, int y, int scale)
{
	sprite->Draw(this->x + x, this->y + y, scale);
}