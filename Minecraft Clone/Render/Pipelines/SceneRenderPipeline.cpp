
#include "Math/Math.h"

#include "SceneRenderPipeline.h"
#include "Engine/GameManager.h"
#include "Engine/GameWindow.h"

#include "Serializers/OBJ Serializer/ModelLoader.h"

void RenderMainScene::init()
{
    // Load the brick texture.
    std::unique_ptr<Texture> texture = std::make_unique<Texture>();
    texture->loadFromFile(GameManager::resPath() + "textures/Bricks.png");
    GameManager::Resources.TextureResources.addRegistry("Bricks", std::move(texture));

    // Load the model shader.
    std::unique_ptr<ShaderProgram> shader = std::make_unique<ModelShader>();
    GameManager::Resources.ShaderResources.addRegistry("Model", std::move(shader));

	// Load model.
    IndexedModel model;
    ModelLoader::loadOBJ(GameManager::resPath() + "models/cube.obj", model);
    std::unique_ptr<IndexedMesh> mesh = std::make_unique<IndexedMesh>();

	mesh->setIndices(model.indices, model.indexCount);
	mesh->addFloatData(model.positions, model.positionsCount, 3);
	mesh->addFloatData(model.uvs, model.uvsCount, 2);
	mesh->addFloatData(model.normals, model.normalsCount, 3);
	GameManager::Resources.MeshResources.addRegistry("Cube", std::move(mesh));

	// Load resources.
	modelShader = static_cast<ModelShader*>(GameManager::Resources.
		ShaderResources.getRegistry("Model"));

	cubeMesh = GameManager::Resources.MeshResources.getRegistry("Cube");

	brickTexture = GameManager::Resources.TextureResources.getRegistry("Bricks");

	camera.createProjectionMatrix(1.0f, GameManager::getGameWindow()->getAspectRatio(),
		.01, 1000);
	camera.getPosition() = Vector3f(0, 0, 5);
	camera.getRotation().lookRotation(Vector3f(0, 0, 1), Vector3f(0, 1, 0));
	camera.calculateViewMatrix();

	modelShader->bind();
	modelShader->loadCameraProjection(camera.getProjection());
	modelShader->loadCamera(camera.getViewMatrix());
	modelShader->loadDiffuseTexture(0);
}

void RenderMainScene::prepare()
{
	modelShader->bind();
}

float rot = 0;
void RenderMainScene::execute()
{
	rot += GameManager::getDeltaTime();

	Quaternionf rotation;
	rotation.rotate(Vector3f(0, 1, 0).normalize(), rot).normalize();

	Matrix44f transformationMatrix;
	Matrix44f translation;
	Matrix44f scale;

	translation.translate(Vector3f(0, 0, -3));
	scale.scale(Vector3f(1, 1, 1));

	transformationMatrix = translation * rotation.toMatrix() * scale;
	modelShader->loadLightPosition(Vector3f(0, 0, 5));
	modelShader->loadModelMatrix(transformationMatrix);

	cubeMesh->render();
}

void RenderMainScenePipeline::init()
{
	mMainSceneRender.init();
}

void RenderMainScenePipeline::render()
{
	mMainSceneRender.render();
}
