#ifndef MESH_H
#define MESH_H

#include "std.h"
#include "Shader.h"
#include <memory>
#include <vector>

struct Vertex
{
	mdm::Vector::Vec3 position;
	mdm::Vector::Vec2 texCoord;
	mdm::Vector::Vec3 normal;
	mdm::Vector::Vec3 tangent;
	mdm::Vector::Vec3 bitangent;
};

class RENDERER_API Mesh
{
public:

	Mesh() { };
	Mesh( 
		std::vector<mdm::Vector::Vec3> pos,
		std::vector<mdm::Vector::Vec2> tex,
		std::vector<mdm::Vector::Vec3> normals,
		std::vector<unsigned int> indice
	);
	~Mesh();

	void Draw();

private:
	std::vector<Vertex> vertices;
	unsigned int indicesCount;

	unsigned int VAO, VBO, EBO;

	void ComputeTangents(std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices);
};

class Cube
{
public:
	Cube();
	~Cube() { };

	void Draw();

private:
	std::unique_ptr<Mesh> mesh;
};

class Plane
{
public:
	Plane();
	~Plane() { };

	void Draw();

private:
	std::unique_ptr<Mesh> mesh;
};

#endif // !MESH_H
