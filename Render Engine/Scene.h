#pragma once

#include <memory>
#include <vector>

#include "RenderPipeline.h"
#include "Render Engine/Camera.h"
#include "Render Engine/Entity.h"

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
		mEntities.push_back(std::move(entity));
	}

	/// <summary>
	/// Returns the first entity found that has the set tag.
	/// </summary>
	/// <param name="tag"></param>
	/// <returns></returns>
	Entity* getEntityWithTag(const std::string& tag)
	{
		for (auto entity = mEntities.begin(); entity != mEntities.end(); ++entity)
		{
			if (entity->get()->getTag() == tag)
			{
				return entity->get();
			}
		}

		return nullptr;
	}

	virtual void init();
	virtual void render();
	virtual void update();

	virtual ~Scene() {}

	/// <summary>
	/// Returns the list of entities.
	/// </summary>
	/// <returns></returns>
	std::vector<std::unique_ptr<Entity>>::iterator getEntitiesIteratorStart()
	{
		return mEntities.begin();
	}

	/// <summary>
	/// Returns the end of the list of entities
	/// </summary>
	/// <returns></returns>
	std::vector<std::unique_ptr<Entity>>::iterator getEntitiesIteratorEnd()
	{
		return mEntities.end();
	}

protected:
	virtual void onInit() = 0;

	std::unique_ptr<RenderPipeline> mRenderPipeline;
	std::vector<std::unique_ptr<Entity>> mEntities;
};

