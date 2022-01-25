#pragma once

#include "Engine/GameManager.h"

/// <summary>
/// Loads global resources for the tank game.
/// </summary>
class ResourceLoader : public IGlobalResourceLoader
{
public:
	virtual void loadTextures(ResourceManager<Texture>& textureResources)
	{
		// Create global resources.
		// Load the textures.
		std::unique_ptr<Texture> playerTexture = std::make_unique<Texture>();
		playerTexture->loadFromFile(GameManager::resPath() + "textures/Player.png");
		GameManager::Resources.TextureResources.addRegistry("Player", std::move(playerTexture));
	}

	virtual void loadShaders(ResourceManager<ShaderProgram>& shaderResources)
	{
		// Load the model shader.
		std::unique_ptr<ShaderProgram> shader = std::make_unique<ModelShader>();
		GameManager::Resources.ShaderResources.addRegistry("Model", std::move(shader));
	}

	virtual void loadMeshes(ResourceManager<Mesh>& meshResources)
	{
		// Load model.
		IndexedModel model;
		ModelLoader::loadOBJ(GameManager::resPath() + "models/Tank.obj", model);
		std::unique_ptr<IndexedMesh> tank = std::make_unique<IndexedMesh>();
		tank->setIndices(model.indices, model.indexCount);
		tank->addFloatData(model.positions, model.positionsCount, 3);
		tank->addFloatData(model.uvs, model.uvsCount, 2);
		tank->addFloatData(model.normals, model.normalsCount, 3);
		GameManager::Resources.MeshResources.addRegistry("Tank", std::move(tank));
	}
};
