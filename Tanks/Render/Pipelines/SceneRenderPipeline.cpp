
#include "Math/Math.h"

#include "Tanks/ResourceLoader.h"
#include "SceneRenderPipeline.h"
#include "Engine/GameManager.h"
#include "Engine/GameWindow.h"

#include "Serializers/OBJ Serializer/ModelLoader.h"
#include "Tanks/Render/Scenes/TankGameScene.h"

void RenderMainScene::init(Scene& scene)
{
	mCamera = static_cast<Camera3D*>(scene.getEntityWithTag("Camera"));

	mModelShader = static_cast<ModelShader*>(GameManager::Resources.
		ShaderResources.getRegistry(SHADER_MODEL));

	mModelShader->bind();
	mModelShader->loadDiffuseTexture(0);
	mModelShader->loadCameraProjection(mCamera->getProjection());
}

void RenderMainScene::prepare(Scene& scene)
{
	mModelShader->bind();

	mModelShader->loadLightPosition(Vector3f(0, 50, 0));
}

void RenderMainScene::execute(Scene& scene)
{
	mCamera->calculateViewMatrix();
	mModelShader->loadCameraViewMatrix(mCamera->getViewMatrix());

	std::vector<std::unique_ptr<Entity>>& entities = scene.getEntities();

	// Render each entity.
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->getTransform()->calculateTransformationMatrix();
		mModelShader->loadModelMatrix(entities[i]->getTransform()->getTransformationMatrix());
		entities[i]->render();
	}
}

void RenderMainScenePipeline::init(Scene& scene)
{
	mRenderTankTracks.init(scene);
	mMainSceneRender.init(scene);
}

void RenderMainScenePipeline::render(Scene& scene)
{
	mRenderTankTracks.render(scene);
	mMainSceneRender.render(scene);
}

////////////////////////////Tank Tracks Render Stage.

void RenderTankTracks::init(Scene& scene)
{
	mBackgroundEntity = scene.getEntityWithTag("Floor");

	mTextureCombineShader = static_cast<TextureCombineShader*>(GameManager::Resources.
		ShaderResources.getRegistry(SHADER_TEXTURE_COMBINE));
	mTextureCombineShader->bind();
	mTextureCombineShader->loadTextureLocations(0, 1);

	mTireTracksShader = static_cast<TireTracksShader*>(GameManager::Resources.ShaderResources.getRegistry(SHADER_TANK_TRACKS));
	mTireTracksShader->bind();
	mTireTracksShader->loadTextureTankTracks(0);

	mTankTracksFramebuffer = GameManager::Resources.FramebufferResources.getRegistry(FRAMEBUFFER_TANK_TRACKS);
	mCombinedFramebuffer = GameManager::Resources.FramebufferResources.getRegistry(FRAMEBUFFER_BG);
	mUnmodifiedBgTexture = GameManager::Resources.TextureResources.getRegistry(TEXTURE_BG);

	mTireTracksObj = std::make_unique<RenderableEntity>(
		GameManager::Resources.MeshResources.getRegistry(MODEL_FLAT_SQUARE),
		GameManager::Resources.TextureResources.getRegistry(TEXTURE_TANK_TRACKS),
		"TankTrackObject");
	mTireTracksObj->getTransform()->Scale = Vector3f(1.7f, 1, 0.15f);

	mTextureCombineMesh = std::make_unique<Mesh2D>();
	float positions[12]
	{
		-1, -1,
		-1, 1,
		1, -1,
		-1, 1,
		1, 1,
		1, -1
	};

	mTextureCombineMesh->addFloatData(positions, sizeof(positions) / sizeof(positions[0]), 2);
	mTextureCombineMesh->setDrawCount(6);

	glClearColor(256, 256, 256, 256);
	mTankTracksFramebuffer->bind();
	Framebuffer::clearDepthAndColor();
}

void RenderTankTracks::prepare(Scene& scene)
{
	mTireTracksShader->bind();
	mTankTracksFramebuffer->bind();

	mBackgroundEntity->getTransform()->calculateTransformationMatrix();
}

void RenderTankTracks::execute(Scene& scene)
{
	// Render the tank tracks.
	glDisable(GL_DEPTH_TEST);
	std::vector<Entity*> tanks = scene.getEntitiesWithTag("Tank");
	for (auto currentTank : tanks)
	{
		TankControlBase* tankControlScript = static_cast<TankControlBase*>(currentTank->getComponent("Movement"));
		std::vector<TransformComponent>& tireTracks = tankControlScript->getTireTracks();

		for (int i = 0; i < tireTracks.size(); i++)
		{
			tireTracks[i].Scale = mTireTracksObj->getTransform()->Scale;
			tireTracks[i].calculateTransformationMatrix();

			Matrix44f newTransform =
				mBackgroundEntity->getTransform()->getTransformationMatrix().inverse() *
				tireTracks[i].getTransformationMatrix();
			
			mTireTracksShader->loadModelMatrix(newTransform);
			mTireTracksObj->render();
		}

		tireTracks.clear();
	}

	glEnable(GL_DEPTH_TEST);

	// Combine the textures.
	mTextureCombineShader->bind();
	mCombinedFramebuffer->bind();

	// Bind the background texture, and the tracks texture to their correct positions.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mUnmodifiedBgTexture->getDiffuseID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mTankTracksFramebuffer->getDepthTexture()->getDiffuseID());

	Framebuffer::clearDepthAndColor();

	mTextureCombineMesh->render();

	Framebuffer::unBind(GameManager::getGameWindow()->getWidth(), 
		GameManager::getGameWindow()->getHeight());
}
