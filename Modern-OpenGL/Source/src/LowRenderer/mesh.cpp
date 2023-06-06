#include <mesh.h>
#include <log.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


Mesh::Mesh(Model* model)
{
    m_Model = model;

    m_Model->BufferGL();
}

Mesh::~Mesh()
{
}

void Mesh::Update()
{
    glBindVertexArray(m_Model->VAO);

    Vector3 axis(1.0f, 1.0f, 1.0f);

    Matrix4x4 TRS;
    TRS.IdentityMatrix();
    TRS.TRS(position, rotation, scale, axis);

    m_LightingShader->setMat4("model", TRS);

    glDrawArrays(GL_TRIANGLES, 0, m_Model->verticesSize);

    glBindVertexArray(m_Model->VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_Model->indexSize), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader)
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < m_Model->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding

        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = m_Model->textures[i].type;

        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string
        else
            DEBUG_LOG("ERROR::NAME_TEXTURE_DOESNT_EXIST \n");

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.id, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, m_Model->textures[i].id);
    }

    // draw mesh
    glBindVertexArray(m_Model->VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_Model->indexBuffer.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}