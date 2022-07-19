#pragma once

#include <memory>
#include <vector>
#include <mutex>

#include "Render Engine/RenderPipeline.h"
#include "Render Engine/Camera.h"
#include "Entity.h"

/// <summary>
/// Class representing a scene. Contains a render pipeline along with all entities 
/// which will be rendered to the scene. GUI elements included as well.
/// <author>Bryce Young 1/24/2022</author>
/// </summary>
class Scene
{
public:
	/// <summary>
	/// Standard constructor.
	/// </summary>
	Scene(std::unique_ptr<RenderPipeline> renderPipeline) 
	{
		this->mRenderPipeline = std::move(renderPipeline);
	}

	/// <summary>
	/// Add entity gives ownership of the entity to this class.
	/// </summary>
	/// <param name="entity"></param>
	void addEntity(std::unique_ptr<Entity> entity)
	{
		entity->init(this);
		EntitiesMutex.lock();
		mEntities.push_back(std::move(entity));
		EntitiesMutex.unlock();
	}

	/// <summary>
	/// Returns the first entity found that has the set tag.
	/// </summary>
	/// <param name="tag"></param>
	/// <returns></returns>
	Entity* getEntityWithTag(const std::string& tag)
	{
		Entity* foundEntity = nullptr;
		size_t entityCount = mEntities.size();

		EntitiesMutex.lock();

		for (int i = 0; i < entityCount; ++i)
		{
			if (mEntities[i]->getTag() == tag)
			{
				foundEntity = mEntities[i].get();
				break;
			}
		}

		EntitiesMutex.unlock();

		return foundEntity;
	}

	/// <summary>
	/// Returns all entities which have a specific tag.
	/// </summary>
	/// <param name="tag"></param>
	/// <returns></returns>
	std::vector<Entity*> getEntitiesWithTag(const std::string& tag)
	{
		std::vector<Entity*> entities;

		EntitiesMutex.lock();

		size_t entityCount = mEntities.size();
		for (int i = 0; i < entityCount; ++i)
		{
			if (mEntities[i]->getTag() == tag)
			{
				entities.push_back(mEntities[i].get());
			}
		}

		EntitiesMutex.unlock();
		return entities;
	}

	virtual void init();
	virtual void render();
	virtual void update();

	virtual ~Scene() {}

	const std::vector<std::unique_ptr<Entity>>& getEntities()
	{
		return mEntities;
	}

protected:
	virtual void onInit() = 0;

	std::unique_ptr<RenderPipeline> mRenderPipeline;
	std::vector<std::unique_ptr<Entity>> mEntities;

public:
	std::mutex EntitiesMutex;
};

