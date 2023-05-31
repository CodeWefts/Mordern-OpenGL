#pragma once
#include <resourcesManager.h>
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

class Buffer
{

public:
	unsigned int VBO, VAO, EBO;

	Buffer();

	void BufferGL(float* vertices, unsigned int* indices);


};


class Model : IResource
{
	vector<Vertex> vertexBufferObj;
	vector<uint32_t> indexBuffer;

public:

	Buffer modelBuffer;



	Model();

	void LoadResource(string const& filename) override;




};

