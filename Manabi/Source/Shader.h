#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Mtx44.h"

class Shader {
public:
	unsigned int ID;

	Shader();

	void Initialize(const char* vertexPath, const char* fragmentPath);
	void Use();
	void Delete();
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetMat4(const std::string& name, const Mtx44& mat) const;
};

#endif