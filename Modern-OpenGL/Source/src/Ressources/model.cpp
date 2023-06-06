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
        vx1.textureUV == vx2.textureUV;
}

// ------------------ Function -----------------------------

void Model::BufferGL()
{
    verticesSize = vertexBufferObj.size();
    indexSize = indexBuffer.size();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Vertex
    glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(Vertex), &vertexBufferObj[0], GL_STATIC_DRAW);

    //Index
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(unsigned int), &indexBuffer[0], GL_STATIC_DRAW);


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
        DEBUG_LOG("FILE_OPEN\n");

        string c;

        while (file >> c)
        {
            cout << c << endl;
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
                file >> pos[0] >> pos[1];

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
                        if ( vertexBufferObj[i] ==  vrtx)
                        {
                            indexBuffer.push_back(i);
                            isNotRepete = false;
                            break;
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
    }
    else
    {
        DEBUG_LOG("ERROR::FILE_MODEL_LOAD_FAIL\n");
        return;
    }
    DEBUG_LOG("FILE_MODEL_LOAD_SUCCED");
    file.close();

    BufferGL();
}

void Model::UnloadResource()
{

}

// --------------------- Builder -------------------------

Model::Model()
{
}
