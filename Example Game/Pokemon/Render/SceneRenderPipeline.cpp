
#include "Math/Math.h"

#include "Example Game/Pokemon/ResourceLoader.h"
#include "Example Game/Pokemon/Render/ModelShader.h"
#include "Example Game/Pokemon/Scene/GameScene.h"

#include "SceneRenderPipeline.h"
#include "Engine/GameManager.h"
#include "Engine/GameWindow.h"

#include "Serializers/OBJ Serializer/ModelLoader.h"

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

	const std::vector<std::unique_ptr<Entity>>& entities = scene.getEntities();

	// Render each entity.
	int entityCount = (int)entities.size();
	for (int i = 0; i < entityCount; i++)
	{
		entities[i]->getTransform()->calculateTransformationMatrix();
		mModelShader->loadModelMatrix(entities[i]->getTransform()->getTransformationMatrix());
		entities[i]->render();
	}
}

void RenderMainScenePipeline::init(Scene& scene)
{
	mMainSceneRender.init(scene);
}

void RenderMainScenePipeline::render(Scene& scene)
{
	mMainSceneRender.render(scene);
}

