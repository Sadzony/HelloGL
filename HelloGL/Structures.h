#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Texture2D.h"
struct Vector3 {
	float x;
	float y;
	float z;
};
struct Vector4 {
	float x, y, z, w;
};


struct Camera {
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};


struct Color {
	GLfloat r, g, b;
};
struct Vertex {
	GLfloat x, y, z;
};
struct TexCoord {
	GLfloat u, v;
};
struct Mesh {
	TexCoord* TexCoords;
	Vertex* Vertices;
	Vector3* Normals;
	int VertexCount, NormalCount, TexCoordCount;
};

struct Lighting {
	Vector4 ambient, diffuse, specular;
};
struct Material {
	Vector4 ambient, diffuse, specular;
	GLfloat shininess;
};
struct ListNode {
	ListNode* next;
};