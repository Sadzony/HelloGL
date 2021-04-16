#pragma once
#include "SceneObject.h"
class StaticObject :
    public SceneObject
{
private:
    Vector3 position;
    Material* mat;
    Vector3 rotationDirection;
    GLfloat rotation;
public:
    StaticObject(Mesh* mesh, Texture2D* texture, float x, float y, float z, float rx, float ry, float rz, float rotationAngle);
    ~StaticObject();
    void Draw() override;
    void Update() override;
};

