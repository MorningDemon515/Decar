#include "Shader.h"

#include "../Main.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

Shader::Shader(std::string vertexFile, std::string fragmentFile)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
 
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexFile);
        fShaderFile.open(fragmentFile);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
   
        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        if (!vShaderFile)
        {
            ErrorMessage("Failed to open Vertex Shader: " + vertexFile);
        }

        if (!fShaderFile)
        {
            ErrorMessage("Failed to open Fragment Shader: " + fragmentFile);
        }
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        ErrorMessage("Vertex Shader Compilation Failed:\n" + std::string(infoLog));
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        ErrorMessage("Fragment Shader Compilation Failed:\n" + std::string(infoLog));
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
}

Shader::~Shader()
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
}

void Shader::Use()
{
    glUseProgram(shaderProgram);
}

void Shader::SetInt(const char* name, int value)
{
    glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}

void Shader::SetFloat(const char* name, float value)
{
    glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}

void Shader::SetVec2(const char* name, mdm::Vector::Vec2 value)
{
    glUniform2f(glGetUniformLocation(shaderProgram, name), value.x, value.y);
}

void Shader::SetVec3(const char* name, mdm::Vector::Vec3 value)
{
    glUniform3f(glGetUniformLocation(shaderProgram, name), value.x, value.y, value.z);
}

void Shader::SetVec4(const char* name, mdm::Vector::Vec4 value)
{
    glUniform4f(glGetUniformLocation(shaderProgram, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix(const char* name, mdm::Matrix::MATRIX value)
{
    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram, name),
        1,
        GL_FALSE,
        mdm::Matrix::Transpose(value).coords);
}