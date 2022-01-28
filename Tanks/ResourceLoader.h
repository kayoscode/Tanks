#pragma once

#include "Engine/GameManager.h"
#include "Tanks/Render/Shaders/ModelShader.h"
#include "TankTracksShader.h"

#include <string>

#define FRAMEBUFFER_TANK_TRACKS "TankTracks"
#define FRAMEBUFFER_BG "BgTexture"

#define TEXTURE_PLAYER "Player"
#define TEXTURE_BULLET "Bullet"
#define TEXTURE_BG "Bg"
#define TEXTURE_TANK_TRACKS "TankTracks"

#define SHADER_MODEL "Model"
#define SHADER_TEXTURE_COMBINE "TextureCombine"
#define SHADER_TANK_TRACKS "TankTracks"

#define MODEL_TANK "Tank"
#define MODEL_BULLET "Bullet"
#define MODEL_FLAT_SQUARE "FlatSquare"


/// <summary>
/// Loads global resources for the tank game.
/// </summary>
class ResourceLoader : public IGlobalResourceLoader
{
public:
	virtual void loadFramebuffers(ResourceManager<Framebuffer>& framebufferResources)
	{
		std::unique_ptr<Framebuffer> tracksRenderTexture =
			std::make_unique<Framebuffer>(1920, 1080);
		tracksRenderTexture->addColorAttachment();
		tracksRenderTexture->addDepthAttachment();
		framebufferResources.addRegistry(FRAMEBUFFER_TANK_TRACKS, std::move(tracksRenderTexture));

		std::unique_ptr<Framebuffer> tracksBgCombineTexture =
			std::make_unique<Framebuffer>(1920, 1080);
		tracksBgCombineTexture->addColorAttachment();
		tracksBgCombineTexture->addDepthAttachment();
		framebufferResources.addRegistry(FRAMEBUFFER_BG, std::move(tracksBgCombineTexture));
	}

	virtual void loadTextures(ResourceManager<Texture>& textureResources)
	{
		// Create global resources.
		// Load the textures.
		std::unique_ptr<Texture> playerTexture = std::make_unique<Texture>();
		playerTexture->loadFromFile(GameManager::resPath() + "textures/Player.png");
		textureResources.addRegistry(TEXTURE_PLAYER, std::move(playerTexture));

		std::unique_ptr<Texture> bulletTexture = std::make_unique<Texture>();
		bulletTexture->loadFromFile(GameManager::resPath() + "textures/Bullet.png");
		textureResources.addRegistry(TEXTURE_BULLET, std::move(bulletTexture));

		std::unique_ptr<Texture> backgroundTexture = std::make_unique<Texture>();
		backgroundTexture->loadFromFile(GameManager::resPath() + "textures/BackgroundTexture.png");
		textureResources.addRegistry(TEXTURE_BG, std::move(backgroundTexture));

		std::unique_ptr<Texture> tankTrackTexture = std::make_unique<Texture>();
		tankTrackTexture->loadFromFile(GameManager::resPath() + "textures/TankTracks.png");
		textureResources.addRegistry(TEXTURE_TANK_TRACKS, std::move(tankTrackTexture));
	}

	virtual void loadShaders(ResourceManager<ShaderProgram>& shaderResources)
	{
		// Load the model shader.
		std::unique_ptr<ShaderProgram> shader = std::make_unique<ModelShader>();
		shaderResources.addRegistry(SHADER_MODEL, std::move(shader));

		std::unique_ptr<ShaderProgram> tankTrackCombineShader =
			std::make_unique<TextureCombineShader>();
		shaderResources.addRegistry(SHADER_TEXTURE_COMBINE, std::move(tankTrackCombineShader));

		std::unique_ptr<ShaderProgram> tankTracks =
			std::make_unique<TireTracksShader>();
		shaderResources.addRegistry(SHADER_TANK_TRACKS, std::move(tankTracks));
	}

	virtual void loadMeshes(ResourceManager<Mesh>& meshResources)
	{
		// Load player.
		IndexedModel tankModel;
		ModelLoader::loadOBJ(GameManager::resPath() + "models/Tank.obj", tankModel);
		std::unique_ptr<IndexedMesh> tank = std::make_unique<IndexedMesh>();
		tank->setIndices(tankModel.indices, tankModel.indexCount);
		tank->addFloatData(tankModel.positions, tankModel.positionsCount, 3);
		tank->addFloatData(tankModel.uvs, tankModel.uvsCount, 2);
		tank->addFloatData(tankModel.normals, tankModel.normalsCount, 3);
		meshResources.addRegistry(MODEL_TANK, std::move(tank));

		// Load bullet.
		IndexedModel bulletModel;
		ModelLoader::loadOBJ(GameManager::resPath() + "models/Bullet.obj", bulletModel);
		std::unique_ptr<IndexedMesh> bullet = std::make_unique<IndexedMesh>();
		bullet->setIndices(bulletModel.indices, bulletModel.indexCount);
		bullet->addFloatData(bulletModel.positions, bulletModel.positionsCount, 3);
		bullet->addFloatData(bulletModel.uvs, bulletModel.uvsCount, 2);
		bullet->addFloatData(bulletModel.normals, bulletModel.normalsCount, 3);
		meshResources.addRegistry(MODEL_BULLET, std::move(bullet));

		// Load floor.
		IndexedModel backgroundModel;
		backgroundModel.positionsCount = 12;
		backgroundModel.positions = new float[12]
		{
			-1, 0, -1,
			-1, 0, 1,
			1, 0, 1,
			1, 0, -1
		};

		backgroundModel.uvsCount = 8;
		backgroundModel.uvs = new float[8]
		{
			0, 1,
			0, 0,
			1, 0,
			1, 1 
		};

		backgroundModel.normalsCount = 12;
		backgroundModel.normals = new float[12]
		{
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0
		};

		backgroundModel.indexCount = 6;
		backgroundModel.indices = new int[6]
		{
			0, 1, 2, 0, 2, 3
		};

		std::unique_ptr<IndexedMesh> floor = std::make_unique<IndexedMesh>();
		floor->setIndices(backgroundModel.indices, backgroundModel.indexCount);
		floor->addFloatData(backgroundModel.positions, backgroundModel.positionsCount, 3);
		floor->addFloatData(backgroundModel.uvs, backgroundModel.uvsCount, 2);
		floor->addFloatData(backgroundModel.normals, backgroundModel.normalsCount, 3);
		meshResources.addRegistry(MODEL_FLAT_SQUARE, std::move(floor));
	}
};
