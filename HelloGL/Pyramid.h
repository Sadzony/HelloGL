#pragma once
#include "SceneObject.h"
class Pyramid :
    public SceneObject
{
private:
	GLfloat rotation;
	Vector3 position;
	Vector3 rotationDirection;
	float rotationSpeed;
public:
	Pyramid(Mesh* mesh, float x, float y, float z, float p_rotationSpeed, float rx, float ry, float rz);
	~Pyramid();
	void Draw() override;
	void Update() override;
};

