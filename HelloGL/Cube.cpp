#include "Cube.h"



Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z, float p_rotationSpeed, float rx, float ry, float rz) : SceneObject(mesh, texture)
{
	rotationSpeed = p_rotationSpeed;
	position.x = x;
	position.y = y;
	position.z = z;
	rotation = 0.0f;
	rotationDirection.x = rx;
	rotationDirection.y = ry;
	rotationDirection.z = rz;
}

Cube::~Cube()
{
	
}

void Cube::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Colors != nullptr && _mesh->Indices != nullptr) {
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotation, rotationDirection.x, rotationDirection.y, rotationDirection.z);
		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
}


void Cube::Update()
{
	rotation += rotationSpeed;
	if (rotation >= 360.0f) {
		rotation = 0.0f;
	}
	position.z += 0.6f;
}
