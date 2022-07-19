#pragma once

#include "Engine/GameManager.h"
#include "Example Game/Pokemon/Render/ModelShader.h"

#include <string>

#define SHADER_MODEL "Model"

/// <summary>
/// Loads global resources for the tank game.
/// </summary>
class ResourceLoader : public IGlobalResourceLoader
{
public:
	virtual void loadFramebuffers(ResourceManager<Framebuffer>& framebufferResources)
	{
	}

	virtual void loadTextures(ResourceManager<Texture>& textureResources)
	{
	}

	virtual void loadShaders(ResourceManager<ShaderProgram>& shaderResources)
	{
		// Load the model shader.
		std::unique_ptr<ShaderProgram> shader = std::make_unique<ModelShader>();
		shaderResources.addRegistry(SHADER_MODEL, std::move(shader));
	}

	virtual void loadMeshes(ResourceManager<Mesh>& meshResources)
	{
	}
};
