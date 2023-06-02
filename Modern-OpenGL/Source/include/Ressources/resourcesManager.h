#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <log.h>
#include <iresource.h>
#include <shader.h>
#include <model.h>


using namespace std;



class ResourcesManager
{
	//dico
	unordered_map<string, IResource*> resources;


public:

	ResourcesManager();

	template <class T>
	T* Create(const string& name, const string& path)
	{
		
		T* resource = new T;
		resource->LoadResource(path);
		

		Delete(name);

		resources.emplace(name, resource);
		
		return resource;
	}

	template <class T>
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