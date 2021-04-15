#pragma once

#include "SceneObject.h"

class Cube : public SceneObject
{
private:
	GLfloat rotation;
	Vector3 position;
	Vector3 rotationDirection;
	Material* mat;
	float rotationSpeed;
	
public:
	Cube(Mesh* mesh,Texture2D* texture, float x, float y, float z, float p_rotationSpeed, float rx, float ry, float rz);
	~Cube();
	void Draw() override;
	void Update() override;
};

