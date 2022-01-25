#pragma once

#include "Render Engine/RenderPipeline.h"
#include "Render Engine/Shader.h"
#include "Render Engine/Mesh.h"
#include "Render Engine/Texture.h"
#include "Render Engine/Camera.h"

#include "Tanks/Render/Shaders/ModelShader.h"

/// <summary>
/// Renders the main scene.
/// <author>Bryce Young 1/24/2022</author>
/// </summary>
class RenderMainScene : public RenderPipelineStage
{
public:
	void init();

protected:
	void prepare();
	void execute();

private:
	ModelShader* modelShader;
	Mesh* cubeMesh;
	Texture* brickTexture;
	Camera3D camera;
};

class RenderMainScenePipeline : public RenderPipeline
{
public:
	void init();
	void render();

private:
	RenderMainScene mMainSceneRender;
};
