#pragma once

#include <iostream>
#include <string>
#include <unordered_map>


using namespace std;

class IResource
{


public:

	virtual void LoadResource();
	virtual void UnloadResource();


	IResource();
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