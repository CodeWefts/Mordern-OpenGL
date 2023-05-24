#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <unordered_map>

using namespace std;

class IResource
{


public:

	IResource();
};

class ResourcesManager
{
	unordered_map<string, IResource*> resources;


public:

	ResourcesManager();

	template <typename T>
	T* Create(string const& filename);
	template <typename T>
	T* Get(string const& filename);

	void Delete(string const& filename);
};