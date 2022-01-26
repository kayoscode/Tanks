
#include "Math/Math.h"

#include "SceneRenderPipeline.h"
#include "Engine/GameManager.h"
#include "Engine/GameWindow.h"

#include "Serializers/OBJ Serializer/ModelLoader.h"

void RenderMainScene::init(Scene& scene)
{
	mCamera = static_cast<Camera3D*>(scene.getEntityWithTag("Camera"));

	// Load resources.
	mModelShader = static_cast<ModelShader*>(GameManager::Resources.
		ShaderResources.getRegistry("Model"));

	mModelShader->bind();
	mModelShader->loadDiffuseTexture(0);
	mModelShader->loadCameraProjection(mCamera->getProjection());
}

void RenderMainScene::prepare(Scene& scene)
{
	mModelShader->bind();
}

void RenderMainScene::execute(Scene& scene)
{
	mModelShader->loadLightPosition(Vector3f(0, 5, 0));

	mCamera->calculateViewMatrix();
	mModelShader->loadCameraViewMatrix(mCamera->getViewMatrix());

	// Render each entity.
	for (auto entity = scene.getEntitiesIteratorStart(); entity != scene.getEntitiesIteratorEnd(); ++entity)
	{
		entity->get()->getTransform()->calculateTransformationMatrix();
		mModelShader->loadModelMatrix(entity->get()->getTransform()->getTransformationMatrix());
		entity->get()->render();
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
