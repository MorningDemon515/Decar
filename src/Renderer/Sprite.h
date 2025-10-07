#ifndef SPRITE_H
#define SPRITE_H

#include "../Main.h"
#include "Shader.h"
#include "Texture.h"
#include <vector>
#include <memory>

struct rect_t
{
	int x, y, w, h;
};

class Sprite
{
public:
	Sprite() { };
	Sprite(
		std::vector<mdm::Vector::Vec4> vertices,
		std::vector<unsigned int> indices);
	Sprite(
		std::vector<mdm::Vector::Vec4> vertices,
		std::vector<unsigned int> indices,
		const char* file);
	~Sprite();

	void SetTexture();
	void SetColor(int r,int g, int b);
	void Draw(int x,int y, int scale);

private:
	unsigned int VAO, VBO, EBO;
	unsigned int indicesCount;

	std::unique_ptr<Shader> shader;
	mdm::Matrix::MATRIX projection = mdm::Transform::OrthoMatrixRH(
		0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, -1.0f, 1.0f
	);

	std::unique_ptr<Texture> texture;
};

class Rect
{
public:
	Rect() { };
	Rect(rect_t rect);
	Rect(rect_t rect, const char* file);
	~Rect();

	void SetTexture();
	void SetColor(int r, int g, int b);
	void Draw(int x, int y, int scale);
private:
	std::unique_ptr<Sprite> sprite;
	int x, y;
};

#endif