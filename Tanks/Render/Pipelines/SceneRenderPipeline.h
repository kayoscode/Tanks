#pragma once

#include "Render Engine/RenderPipeline.h"
#include "Render Engine/Shader.h"
#include "Render Engine/Mesh.h"
#include "Render Engine/Texture.h"
#include "Render Engine/Camera.h"
#include "Engine/Scene.h"
#include "Render Engine/Framebuffer.h"
#include "Engine/Entity.h"

#include "Tanks/Render/Shaders/ModelShader.h"
#include "Tanks/TankTracksShader.h"

/// <summary>
/// Renders the main scene.
/// <author>Bryce Young 1/24/2022</author>
/// </summary>
class RenderMainScene : public RenderPipelineStage
{
public:
	RenderMainScene()
		:mModelShader(nullptr),
		mCamera(nullptr){ }

	void init(Scene& scene);

protected:
	void prepare(Scene& scene);
	void execute(Scene& scene);

private:
	ModelShader* mModelShader;
	Camera3D* mCamera;
};

class RenderTankTracks : public RenderPipelineStage
{
public:
	void init(Scene& scene);

protected:
	void prepare(Scene& scene);
	void execute(Scene& scene);

private:
	TextureCombineShader* mTextureCombineShader;
	TireTracksShader* mTireTracksShader;
	
	// Render tank tracks here.
	Framebuffer* mTankTracksFramebuffer;

	// Final background texture rendered to here.
	Framebuffer* mCombinedFramebuffer;

	// The unmodified background texture.
	Texture* mUnmodifiedBgTexture;
	Entity* mBackgroundEntity;
	std::unique_ptr<RenderableEntity> mTireTracksObj;

	std::unique_ptr<Mesh2D> mTextureCombineMesh;
};

class RenderMainScenePipeline : public RenderPipeline
{
public:
	void init(Scene& scene);
	void render(Scene& scene);

private:
	RenderTankTracks mRenderTankTracks;
	RenderMainScene mMainSceneRender;
};
