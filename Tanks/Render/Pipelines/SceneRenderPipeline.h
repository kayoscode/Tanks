#pragma once

#include "Render Engine/RenderPipeline.h"
#include "Render Engine/Shader.h"
#include "Render Engine/Mesh.h"
#include "Render Engine/Texture.h"
#include "Render Engine/Camera.h"
#include "Render Engine/Scene.h"

#include "Tanks/Render/Shaders/ModelShader.h"

/// <summary>
/// Renders the main scene.
/// <author>Bryce Young 1/24/2022</author>
/// </summary>
class RenderMainScene : public RenderPipelineStage
{
public:
	void init(Scene& scene);

protected:
	void prepare(Scene& scene);
	void execute(Scene& scene);

private:
	ModelShader* mModelShader;
	std::unique_ptr<Camera3D> mCamera;
};

class RenderMainScenePipeline : public RenderPipeline
{
public:
	void init(Scene& scene);
	void render(Scene& scene);

private:
	RenderMainScene mMainSceneRender;
};
