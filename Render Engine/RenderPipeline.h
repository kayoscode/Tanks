#pragma once

class Scene;

/// <summary>
/// Represents a stage in the render pipeline.
/// Examples: render scene, post processing, render GUI.
/// Doesn't handle any kind of updating, only rendering.
/// <author>Bryce Young 1/24/2022</author>
/// </summary>
class RenderPipelineStage
{
public:
	RenderPipelineStage() {}
	virtual ~RenderPipelineStage() {} 

	/// <summary>
	/// Renders this stage.
	/// </summary>
	void render(Scene& scene)
	{
		prepare(scene);
		execute(scene);
	}

	/// <summary>
	/// Called to initialize any member variables or resources at load time.
	/// </summary>
	virtual void init(Scene& scene) = 0;

protected:

	/// <summary>
	/// Renders this stage of the pipeline. The output is a framebuffer (TODO).
	/// </summary>
	virtual void execute(Scene& scene) = 0;

	/// <summary>
	/// Prepares the pipeline stage for render.
	/// </summary>
	virtual void prepare(Scene& scene) = 0;

private:
};

/// <summary>
/// Framework for specifying a set of tasks which are performed during the render process.
/// </summary>
class RenderPipeline
{
public:
	RenderPipeline() {}
	virtual ~RenderPipeline() {} 

	/// <summary>
	/// Inits all render pipeline stages.
	/// </summary>
	virtual void init(Scene& scene) = 0;

	/// <summary>
	/// Renders the pipeline to the currently bound framebuffer.
	/// </summary>
	virtual void render(Scene& scene) = 0;

protected:
private:
};

