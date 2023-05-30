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

class Model : IResource
{
	vector<Vertex> vertexBufferObj;
	vector<uint32_t> indexBuffer;

public:


	Model();
	void LoadResource(string const& filename) override;


};