#pragma once
#include "MeshLoader.h"
#include "StaticObject.h"
#include "Car.h"
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
	StaticObject* roadObject;
	StaticObject* roadObject2;
	StaticObject* roadObject3;
	StaticObject* lampObject;
	StaticObject* lampObject2;
	Car* carObject;
	Vector4* lightPosition;
	Lighting* lightData;
	float sphereRotation = 0;

};

