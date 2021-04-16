#pragma once
#include "SceneObject.h"
class Car :
    public SceneObject
{
private:
    Vector3 position;
    Material* mat;
    Vector3 rotationDirection;
    GLfloat rotation;
    float m_speed;
public:
    Car(Mesh* mesh, Texture2D* texture, float x, float y, float z, float rx, float ry, float rz, float rotationAngle, float speed);
    ~Car();
    void Draw() override;
    void Update() override;
    Vector3 GetPosition() { return position; };
    void SetPosition(Vector3 newPosition) { position = newPosition; };
    int moveDirection = 0;
};

