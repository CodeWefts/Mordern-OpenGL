#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <filesystem>

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
	unordered_map<string, IResource*> resources;


public:

	ResourcesManager();

	template <typename T>
	T* Create(filesystem::path const& filename);
	template <typename T>
	T* Get(filesystem::path const& filename);

	void Delete(filesystem::path const& filename);
};