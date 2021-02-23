#pragma once
#include "Structures.h"
class Texture2D
{
private: 
	GLuint _ID;
	int _width, _height;
public:
	Texture2D();
	~Texture2D();
	bool Load(char* path, int width, int height);
	bool LoadTGA(char* path);
	bool LoadBMP(char* path);
	int GetWidth() const {
		return _width;
	}
	int GetHeight() const {
		return _height;
	}
	GLuint GetID() const {
		return _ID;
	}
};

