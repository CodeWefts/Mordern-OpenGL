#pragma once
#include <resourcesManager.h>
#include <vector>
#include <vec3.h>

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector3 textureUV;
};


class Model : IResource
{
	vector<Vertex> vertexBufferObj;
	vector<uint32_t> indexBuffer;

public:

	//void Reader();	


	Model();

};