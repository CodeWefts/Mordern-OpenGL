#pragma once
#include <shader.h>
#include <texture.h>


#include <vector>
#include <vec3.h>
#include <vec2.h>


struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 textureUV;
};


bool operator==(const Vertex& vx1 , const Vertex& vx2);


class Model : public IResource
{

public:
	Model();

	void LoadResource(string const& filename);
	void UnloadResource();

	unsigned int VBO, VAO, EBO;

	vector<Vertex>     vertexBufferObj;
	vector<uint32_t>   indexBuffer;
	vector<Texture>    textures;

	int verticesSize, indexSize;


	void BufferGL();

};
