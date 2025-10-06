#include "Mesh.h"

#include <glad/glad.h>

Mesh::Mesh(
	std::vector<mdm::Vector::Vec3> pos,
	std::vector<mdm::Vector::Vec2> tex,
	std::vector<mdm::Vector::Vec3> normals,
	std::vector<unsigned int> indices
)
{

	Vertex temp;
	for (int i = 0; i < pos.size(); i++)
	{
		temp.position = pos[i];
		temp.texCoord = tex[i];
		temp.normal = normals[i];
		vertices.push_back(temp);
	}

	indicesCount = indices.size();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Cube::Cube()
{
	std::vector<mdm::Vector::Vec3> positions = {
		//Front face
		{-1.0f, -1.0f,  1.0f},
		{ 1.0f, -1.0f,  1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{-1.0f,  1.0f,  1.0f},
		{-1.0f, -1.0f,  1.0f},

		//Back face
		{-1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{ 1.0f,  1.0f, -1.0f},
		{ 1.0f,  1.0f, -1.0f},
		{-1.0f,  1.0f, -1.0f},
		{-1.0f, -1.0f, -1.0f},

		//Left face
		{-1.0f,  1.0f,  1.0f},
		{-1.0f,  1.0f, -1.0f},
		{-1.0f, -1.0f, -1.0f},
		{-1.0f, -1.0f, -1.0f},
		{-1.0f, -1.0f,  1.0f},
		{-1.0f,  1.0f,  1.0f},

		//Right face
		{ 1.0f,  1.0f,  1.0f},
		{ 1.0f,  1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f,  1.0f},
		{ 1.0f,  1.0f,  1.0f},

		//Top face
		{-1.0f,  1.0f, -1.0f},
		{ 1.0f,  1.0f, -1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{ 1.0f,  1.0f,  1.0f},
		{-1.0f,  1.0f,  1.0f},
		{-1.0f,  1.0f, -1.0f},

		//Bottom face
		{-1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f,  1.0f},
		{ 1.0f, -1.0f,  1.0f},
		{-1.0f, -1.0f,  1.0f},
		{-1.0f, -1.0f, -1.0f}
	};

	std::vector<mdm::Vector::Vec2> texCoords = {
		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
		{1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},

		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
		{1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},

		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
		{1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},

		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
		{1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},

		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
		{1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f},

		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
		{1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}
	};

	std::vector<mdm::Vector::Vec3> normals = {
		{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f},

		{0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},
		{0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},

		{-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
		{-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},

		{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f},

		{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f},

		{0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,

		18, 19, 20,
		21, 22, 23,
		24, 25, 26,
		27, 28, 29,
		30, 31, 32,
		33, 34, 35
	};

	mesh = std::make_unique<Mesh>(positions, texCoords, normals, indices);
}

void Cube::Draw()
{
	mesh->Draw();
}