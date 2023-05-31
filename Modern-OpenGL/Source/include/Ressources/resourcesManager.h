#pragma once

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <log.h>


using namespace std;

class IResource
{

public:

	IResource();

	virtual void LoadResource(string const& filename);
	virtual void UnloadResource();

};

class ResourcesManager
{
	//dico
	unordered_map<string, IResource*> resources;


public:

	ResourcesManager();

	template <typename T>
	T* Create(string const& filename)
	{
		T* resource = new T;

		Delete(filename);

		resources.emplace(filename, resource);

		return resource;
	}
	template <typename T>
	T* Get(string const& filename)
	{

		// Range of "dictionary"
		for (auto it = resources.begin(); it != resources.end(); ++it)
		{
			if (it->first == filename)
			{
				return it->second;
			}
		}

		return nullptr;
	}

	void Delete(string const& filename);
};