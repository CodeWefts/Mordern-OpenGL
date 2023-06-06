#pragma once

#include <Model.h>
#include <Shader.h>

#include <vec3.h>
#include <mat4.h>


class Mesh
{

private:
    Model* m_Model;
    Shader* m_LightingShader;

public:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;


    Mesh(Model* model);
    ~Mesh();

    void Update();
    void Draw(Shader& shader);
};