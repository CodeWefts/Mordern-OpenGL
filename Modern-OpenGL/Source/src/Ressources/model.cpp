#include <model.h>
#include <fstream>

// ------------------ Operator -----------------------------

bool operator==(const Vertex& vx1, const Vertex& vx2)
{
    return vx1.position.value == vx2.position.value &&
        vx1.normal.value == vx2.normal.value &&
        vx1.textureUV.value == vx2.textureUV.value;

}

// ------------------ Function -----------------------------

void Model::LoadResource(string const& filename)
{
	ResourcesManager resource;
	IResource* a = resource.Get<IResource>(filename);
	ifstream file;

    vector<Vector3> positions;
    vector<Vector3> normals;
    vector<Vector2> textureUVs;

	file.open(filename);

    if (file)
    {
        string c;

        while (file >> c)
        {
            if (c == "v")
            {
                Vector3 pos;
                file >> pos.value[0] >> pos.value[1] >> pos.value[2];

                positions.push_back(pos);
            }

            if (c == "vn")
            {
                Vector3 pos;
                file >> pos.value[0] >> pos.value[1] >> pos.value[2];

                normals.push_back(pos);
            }

            if (c == "vt")
            {

                Vector2 pos;
                file >> pos.value[0] >> pos.value[1];

                textureUVs.push_back(pos);

            }

            if (c == "f")
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

                    if (isNotRepete)
                    {
                        vertexBufferObj.push_back(vrtx);
                        indexBuffer.push_back(vertexBufferObj.size() - 1);
                    }


                }
            }
        }

        for (auto i = 0; i < indexBuffer.size(); i++)
        {
            cout << indexBuffer[i] << endl;
        }
    }
    else
    {
        cout << "Object not load" << endl;
    }


}



// --------------------- Builder -------------------------
Model::Model()
{

}
