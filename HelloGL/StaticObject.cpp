#include "StaticObject.h"

StaticObject::StaticObject(Mesh* mesh, Texture2D* texture, float x, float y, float z, float rx, float ry, float rz, float rotationAngle) : SceneObject(mesh, texture)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotation = rotationAngle;
	rotationDirection.x = rx;
	rotationDirection.y = ry;
	rotationDirection.z = rz;
	mat = new Material();
	mat->ambient.x = 1.0f; mat->ambient.y = 1.0f; mat->ambient.z = 1.0f; mat->ambient.w = 1.0f;
	mat->diffuse.x = 0.5f; mat->diffuse.y = 0.5f; mat->diffuse.z = 0.5f; mat->diffuse.w = 1.0f;
	mat->specular.x = 1.0f; mat->specular.y = 1.0f; mat->specular.z = 1.0f; mat->specular.w = 1.0f;
	mat->shininess = 150.0f;
}

StaticObject::~StaticObject()
{
}

void StaticObject::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->TexCoords != nullptr) {
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
		glMaterialf(GL_FRONT, GL_SHININESS, mat->shininess);
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

void StaticObject::Update()
{
}
