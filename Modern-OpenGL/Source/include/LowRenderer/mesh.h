#pragma once

#include <Model.h>
#include <Shader.h>
#include <Texture.h>

#include <vec3.h>
#include <Mat4.h>




class Mesh
{
private:
    Model* m_Model = nullptr;
    Shader* m_LightingShader = nullptr;
    Texture* m_TextureDiffuse = nullptr;
    Texture* m_TextureSpecular = nullptr;

public:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;


    Mesh(Model* model, Shader* lightingShader, Texture* baseTexture, Texture* specularTexture = nullptr, Vector3 position = Vector3(0), Vector3 rotation = Vector3(0), Vector3 scale = Vector3(1));
    ~Mesh();

    void Update();
};