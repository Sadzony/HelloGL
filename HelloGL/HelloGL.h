#pragma once
#include "MeshLoader.h"
#include "Cube.h"
#include "Pyramid.h"
#define REFRESH_RATE 16

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);
	~HelloGL(void);
	void InitObjects();
	void InitLight();
	void InitGL(int argc, char* argv[]);
	void Display();
	void Update();
	void Keyboard(unsigned char  key, int x, int y);
private:
	Camera* camera;
	SceneObject* objects [1000];
	Vector4* lightPosition;
	Lighting* lightData;
};

