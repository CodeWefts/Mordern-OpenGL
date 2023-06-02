#pragma once
#include <filesystem>
#include <iresource.h>



using namespace std;

class Texture : public IResource
{
	
public:

	unsigned int       texture;
	int width, height, nrChannels;
	unsigned int       id;
	string             type; // can be "texture_diffuse" or "texture_specular" or "texture_normal" or "texture_height"
	string             path;

	void LoadResource(string const& filename);
	void UnloadResource();

	Texture();
};