#include <model.h>
#include <log.h>

#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ------------------ Operator -----------------------------

bool operator==(const Vertex& vx1, const Vertex& vx2)
{
    return vx1.position == vx2.position &&
        vx1.normal == vx2.normal &&
        vx1.textureUV.value == vx2.textureUV.value;

}

// ------------------ Function -----------------------------

void Model::BufferGL(vector<Vertex> vertices, vector<uint32_t> indices)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Vertex
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    //Index
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


    // ------ set the vertex attribute pointers ------
    
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureUV));

    glBindVertexArray(0);
}


void Model::LoadResource(string const& filename)
{
	ifstream file;

    //ephemeral vectors
    vector<Vector3> positions;
    vector<Vector3> normals;
    vector<Vector2> textureUVs;

    //open ModelFile
	file.open(filename);

    if (file)
    {
        string c;

        while (file >> c)
        {
            if (c == "v")//positions vertex
            {
                Vector3 pos;
                file >> pos[0] >> pos[1] >> pos[2];

                positions.push_back(pos);
            }
            else if (c == "vn")//normals vertex
            {
                Vector3 pos;
                file >> pos[0] >> pos[1] >> pos[2];

                normals.push_back(pos);
            }
            else if (c == "vt")//textures coords vertex
            {
                Vector2 pos;
                file >> pos.value[0] >> pos.value[1];

                textureUVs.push_back(pos);

            }
            else if (c == "f")//informations of each vertex
            {
                for (int i = 0; i < 3; i++)
                {
                    int indexV, indexVN, indexVT;

                    file >> indexV;
                    file.ignore();
                    file >> indexVT;
                    file.ignore(); 
                    file >> indexVN;
                    file.ignore();

                    Vertex vrtx = { positions[indexV-1],normals[indexVN - 1],textureUVs[indexVT - 1] };

                    //duplicate informations doesn't matter
                    bool isNotRepete = true;
                    for (int i = 0; i < vertexBufferObj.size(); i++)
                    {
                        if (vrtx == vertexBufferObj[i])
                        {
                            indexBuffer.push_back(i);
                            isNotRepete = false;
                            break;
                        }
                    }

                    //new informations are push back in vertexBufferObj
                    if (isNotRepete)
                    {
                        vertexBufferObj.push_back(vrtx);
                        indexBuffer.push_back(vertexBufferObj.size() - 1);
                    }
                }
            }
        }
    }
    else
    {
        DEBUG_LOG("FILE_MODEL_LOAD_FAIL");
    }
}

void Model::UnloadResource()
{

}


void Model::Draw(Shader& shader)
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding

        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = textures[i].type;

        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string
        else
            DEBUG_LOG("NAME_TEXTURE_DOESNT_EXIST");

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.id, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indexBuffer.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

// --------------------- Builder -------------------------

Model::Model()
{
}
