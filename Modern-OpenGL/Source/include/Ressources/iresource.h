#pragma once
#include <iostream>

using namespace std;

class IResource
{

public:


	IResource();

	virtual void LoadResource(string const& filename) = 0;
	virtual void UnloadResource() = 0;

};