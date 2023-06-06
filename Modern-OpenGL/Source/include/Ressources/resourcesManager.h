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
	T* Get(const string& filename)
	{
		auto it = resources.find(filename);

		if (it == resources.end())
		{
			DEBUG_LOG("ERROR::GET_RESOURCE_FAIL\n");
			return nullptr;
		}
		return dynamic_cast<T*>(it->second);
	}

	void Delete(string const& filename);
};