#ifndef MESH_H
#define MESH_H

#include "std.h"
#include "Shader.h"
#include <memory>
#include <vector>

struct Vertex
{
	mdm::Vector::Vec3 position;
};

class RENDERER_API Mesh
{
public:

	Mesh() { };
	Mesh( 
		std::vector<mdm::Vector::Vec3> pos,
		std::vector<unsigned int> indice
	);
	~Mesh();

	void Draw();

private:
	std::vector<Vertex> vertices;
	unsigned int indicesCount;

	unsigned int VAO, VBO, EBO;
};

#endif // !MESH_H
