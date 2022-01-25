#pragma once

#include <map>
#include <string>
#include <vector>

#include "../Logger/StaticLogger.h"

#define RESOURCE_ALREADY_REGISTERED_WARNING "{string}: Resource already registered {string}"
#define RESOURCE_NOT_REGISTERED_ERROR "{string}: Resource not registered {string}"

/// <summary>
/// Class responsible for managing global resources.
/// This class assumes ownership of all resources passed to it.
/// Textures, Meshes, ShaderPrograms
/// <author>Bryce Young 1/24/2022</author>
/// </summary>
template<class T>
class ResourceManager
{
public:
	ResourceManager(const std::string& resourceTypeName) 
		:mRegistries(),
		mResourceTypeName(resourceTypeName)
	{}

	~ResourceManager() {}

	void addRegistry(const std::string& name, std::unique_ptr<T> registry)
	{
		if (mRegistries.find(name) == mRegistries.end())
		{
			mRegistries[name] = std::move(registry);
		}
		else 
		{
			StaticLogger::instance.warning(RESOURCE_ALREADY_REGISTERED_WARNING,
				mResourceTypeName.c_str(), name.c_str());
		}
	}

	T* getRegistry(const std::string& name)
	{
		std::map<std::string, std::unique_ptr<T>>::iterator value = mRegistries.find(name);

		if (value == mRegistries.end())
		{
			StaticLogger::instance.error(RESOURCE_NOT_REGISTERED_ERROR,
				mResourceTypeName.c_str(), name.c_str());
		}
		else 
		{
			return value->second.get();
		}

		return nullptr;
	}

private:
	std::map<std::string, std::unique_ptr<T>> mRegistries;
	std::string mResourceTypeName;
};

