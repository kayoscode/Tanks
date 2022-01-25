#pragma once

#include "RenderPipeline.h"
#include <memory>

class RenderPipeline;

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

	virtual void init();
	virtual void render();

	virtual ~Scene() {}

protected:
private:
	std::unique_ptr<RenderPipeline> mRenderPipeline;
};

