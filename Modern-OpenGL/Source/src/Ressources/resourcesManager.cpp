#include <resourcesManager.h>

// ------------------------- Function -----------------------------------

void ResourcesManager::Delete(string const& filename)
{
	//Function "find" exist, don't need to have a loop

	for (auto it = resources.begin(); it != resources.end(); ++it)
	{
		if (it->first == filename)
		{
			IResource* mem = it->second;

			// Delete it from resources
			resources.erase(it);

			// Delete memory location
			delete mem;
		}
	}
}


// -------------------------- Builder --------------------------------

IResource::IResource()
{

}

ResourcesManager::ResourcesManager()
{

}


