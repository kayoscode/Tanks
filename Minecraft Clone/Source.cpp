#include <vector>
#include <string>

#include "../Engine/GameManager.h"
#include "../Logger/StaticLogger.h"
#include "../Serializers/OBJ Serializer/ModelLoader.h"
#include "Render/Shaders/ModelShader.h"

int main()
{
	GameManager::setResPath("res/");
	GameManager::createWindow(GameManager::resPath() + "settings.json");

    // Load the brick texture.
    std::unique_ptr<Texture> brickTexture = std::make_unique<Texture>();
    brickTexture->loadFromFile(GameManager::resPath() + "textures/Bricks.png");
    GameManager::Resources.TextureResources.addRegistry("Bricks", std::move(brickTexture));

    // Load the model shader.
    std::unique_ptr<ShaderProgram> modelShader = std::make_unique<ModelShader>();
    GameManager::Resources.ShaderResources.addRegistry("Model", std::move(modelShader));

	// Load model.
    IndexedModel cubeModel;
    ModelLoader::loadOBJ(GameManager::resPath() + "models/cube.obj", cubeModel);
    std::unique_ptr<IndexedMesh> cubeMesh = std::make_unique<IndexedMesh>();

	cubeMesh->setIndices(cubeModel.indices, cubeModel.indexCount);
	cubeMesh->addFloatData(cubeModel.positions, cubeModel.positionsCount, 3);
	cubeMesh->addFloatData(cubeModel.uvs, cubeModel.uvsCount, 2);
	cubeMesh->addFloatData(cubeModel.normals, cubeModel.normalsCount, 3);
	GameManager::Resources.MeshResources.addRegistry("Cube", std::move(cubeMesh));

	GameManager::executeGameLoop();

	StaticLogger::instance.trace("Total program runtime (seconds): [ts]");

	return 0;
}