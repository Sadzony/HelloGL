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
	mat = new Material();
	mat->ambient.x = 0.8f; mat->ambient.y = 0.05f; mat->ambient.z = 0.05f; mat->ambient.w = 1.0f;
	mat->diffuse.x = 0.8f; mat->diffuse.y = 0.05f; mat->diffuse.z = 0.05f; mat->diffuse.w = 1.0f;
	mat->specular.x = 1.0f; mat->specular.y = 1.0f; mat->specular.z = 1.0f; mat->specular.w = 1.0f;
	mat->shininess = 100.0f;
}

Cube::~Cube()
{
	
}

void Cube::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr) {
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(mat->ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(mat->diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(mat->specular.x));
		glMaterialf(GL_FRONT, GL_SHININESS,mat->shininess);
		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotation, rotationDirection.x, rotationDirection.y, rotationDirection.z);
		glDrawArrays(GL_TRIANGLES, 0, _mesh->VertexCount);
		glPopMatrix();
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
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
