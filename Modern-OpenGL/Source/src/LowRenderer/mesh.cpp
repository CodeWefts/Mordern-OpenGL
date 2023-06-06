#include <Mesh.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>




Mesh::Mesh(Model* model, Shader* lightingShader, Texture* textureDiffuse, Texture* textureSpecular, Vector3 position, Vector3 rotation, Vector3 scale)
{
    m_Model = model;
    m_LightingShader = lightingShader;
    m_TextureDiffuse = textureDiffuse;
    m_TextureSpecular = textureSpecular;

    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

Mesh::~Mesh()
{
}

void Mesh::Update()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureDiffuse->id);

    if (m_TextureSpecular != nullptr)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_TextureSpecular->id);
    }

    glBindVertexArray(m_Model->VAO);

    Matrix4x4 TRS;
    Vector3 axis(1,1,1);
    TRS.IdentityMatrix();
    TRS.TRS(rotation, position,scale,axis);
    m_LightingShader->setMat4("model", TRS);


    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_Model->indexSize), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
