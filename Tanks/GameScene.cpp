#include <memory>

#include "GameScene.h"
#include "Render/Pipelines/SceneRenderPipeline.h"
#include "Engine/GameManager.h"

GameScene::GameScene()
	:Scene(std::make_unique<RenderMainScenePipeline>())
{
    mCamera = std::make_unique<Camera3D>();
}

void GameScene::onInit()
{
	// Create global resources.
    // Load the textures.
    std::unique_ptr<Texture> playerTexture = std::make_unique<Texture>();
    playerTexture->loadFromFile(GameManager::resPath() + "textures/Player.png");
    GameManager::Resources.TextureResources.addRegistry("Player", std::move(playerTexture));

    // Load the model shader.
    std::unique_ptr<ShaderProgram> shader = std::make_unique<ModelShader>();
    GameManager::Resources.ShaderResources.addRegistry("Model", std::move(shader));

	// Load model.
    IndexedModel model;
    ModelLoader::loadOBJ(GameManager::resPath() + "models/Tank.obj", model);
    std::unique_ptr<IndexedMesh> tank = std::make_unique<IndexedMesh>();
	tank->setIndices(model.indices, model.indexCount);
	tank->addFloatData(model.positions, model.positionsCount, 3);
	tank->addFloatData(model.uvs, model.uvsCount, 2);
	tank->addFloatData(model.normals, model.normalsCount, 3);
    GameManager::Resources.MeshResources.addRegistry("Tank", std::move(tank));

    std::unique_ptr<RenderableEntity> playerEntity =
        std::make_unique<RenderableEntity>(GameManager::Resources.MeshResources.getRegistry("Tank"),
            GameManager::Resources.TextureResources.getRegistry("Player"),
            "Player");

    playerEntity->getTransform()->Position.z = -7;
    playerEntity->getTransform()->Position.y = -3;

    class PlayerSpin : public UpdateLoop
    {
    public:
        void init(Entity* object) 
        { 
        }

        void update(Entity* object)
        {
            object->getTransform()->Rotation.rotate(Vector3f(0, 1, 0), GameManager::getDeltaTime());
        }

    private:
    };

    playerEntity->addComponent("SpinPlayer", std::make_unique<PlayerSpin>());

    addRenderableEntity(std::move(playerEntity));
}