#ifndef SHADER_H
#define SHADER_H

#include <mdm.h>

class Shader
{
public:
	Shader() { };
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	void Use();

	void SetInt(const char* name, int value);
	void SetFloat(const char* name, float value);

	void SetVec2(const char* name, mdm::Vector::Vec2 value);
	void SetVec3(const char* name, mdm::Vector::Vec3 value);
	void SetVec4(const char* name, mdm::Vector::Vec4 value);

	void SetMatrix(const char* name, mdm::Matrix::MATRIX value);

private:
	unsigned int vertexShader, fragmentShader, shaderProgram;
};

#endif // !SHADER_H
