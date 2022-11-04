#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"

struct Material {
	int m_shaderIndex;

	Vector3 m_ambient;
	Vector3 m_diffuse;
	Vector3 m_specular;

	float m_shininess;

	Material(int index, Vector3 ambient, Vector3 diffuse, Vector3 specular, float shininess) {
		m_shaderIndex = index;
		m_ambient = ambient;
		m_diffuse = diffuse;
		m_specular = specular;
		m_shininess = shininess;
	}
};

#endif