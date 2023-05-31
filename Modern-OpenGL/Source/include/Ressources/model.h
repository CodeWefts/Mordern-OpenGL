#pragma once
#include <shader.h>
#include <vector>
#include <vec3.h>
#include <vec2.h>



struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 textureUV;
};

struct Texture {
	unsigned int       id;
	string             type; // can be "texture_diffuse" or "texture_specular" or "texture_normal" or "texture_height"
	string             path;
};

bool operator==(const Vertex& vx1 , const Vertex& vx2);


class Model : IResource
{
	void LoadResource(string const& filename) override;

public:
	unsigned int VBO, VAO, EBO;

	vector<Vertex>     vertexBufferObj;
	vector<uint32_t>   indexBuffer;
	vector<Texture>    textures;


	void BufferGL(vector<Vertex> vertices, vector<uint32_t> indices);


	Model(string const& path);

	void Draw(Shader& shader);

};
