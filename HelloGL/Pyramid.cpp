#include "Pyramid.h"
Pyramid::Pyramid(Mesh* mesh, float x, float y, float z, float p_rotationSpeed, float rx, float ry, float rz) : SceneObject(mesh, nullptr)
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

Pyramid::~Pyramid()
{

}

void Pyramid::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Colors != nullptr && _mesh->Indices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);
		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotation, rotationDirection.x, rotationDirection.y, rotationDirection.z);
		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
}


void Pyramid::Update()
{

}
