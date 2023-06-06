#include <Scene.h>

#include <log.h>




Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::CreateMesh(Model* model, Shader* lightingShader, Texture* textureDiffuse, Texture* texureSpecular, Vector3 position, Vector3 rotation, Vector3 scale)
{
    //DEBUG_LOG("Create Mesh");

    Mesh newMesh(model, lightingShader, textureDiffuse, texureSpecular, position, rotation, scale);

    m_Meshes.push_back(newMesh);
}

void Scene::UpdateImGui()
{
}

void Scene::Update()
{
    // Update all meshes
    for (unsigned int i = 0; i < m_Meshes.size(); i++)
    {
        m_Meshes[i].Update();
    }
}