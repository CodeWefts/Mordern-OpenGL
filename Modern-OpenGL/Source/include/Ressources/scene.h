#pragma once

#include <Model.h>
#include <Mesh.h>
#include <Light.h>

#include <vector>
#include <vec3.h>




class Scene
{
private:
    Light m_Light;
    std::vector<Mesh> m_Meshes;

public:
    Scene();
    ~Scene();

    void CreateMesh(Model* model, Shader* lightingShader, Texture* textureDiffuse, Texture* textureSpecular = nullptr, Vector3 position = Vector3(0), Vector3 rotation = Vector3(0), Vector3 scale = Vector3(1));
    void UpdateImGui();
    void Update();
};