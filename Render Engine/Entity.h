#pragma once

#include <map>
#include <string>

#include "Component.h"
#include "Mesh.h"
#include "Texture.h"
#include "Serializers/OBJ Serializer/ModelLoader.h"

/// <summary>
/// Class to 
/// <author>Bryce Young 1/25/2022</author>
/// </summary>
class ObjectWithComponents
{
public:
	IComponent* getComponent(const std::string& name);

protected:
	std::map<std::string, std::unique_ptr<IComponent>> mComponents;
};

/// <summary>
/// Class to represent an entity.
/// </summary>
class Entity : public ObjectWithComponents
{
public:
	/// <summary>
	/// Standard constructor.
	/// </summary>
	/// <param name="tag"></param>
	Entity(const std::string& tag = "untagged");
	virtual ~Entity();

	std::string getTag() { return mTag; }
	void setTag(const std::string& tag) { this->mTag = tag; }

	TransformComponent* getTransform() { return mTransform.get(); }

	bool addComponent(const std::string& name, std::unique_ptr<IComponent> component);
	void updateComponents();

	virtual void init();
	virtual void update();
	virtual void render() {} 

protected:
	std::string mTag;
	std::unique_ptr<TransformComponent> mTransform;
};

/// <summary>
/// Represents an entity which can be rendered onto the screen.
/// The renderable entity does not own the mesh.
/// </summary>
class RenderableEntity : public Entity
{
public:
	/// <summary>
	/// Standard constructor.
	/// </summary>
	/// <param name="mesh"></param>
	/// <param name="tag"></param>
	RenderableEntity(Mesh* mesh, 
		Texture* texture, 
		const std::string& tag = "untagged");
	virtual ~RenderableEntity();

	/// <summary>
	/// Renders the renderable entity.
	/// </summary>
	virtual void render()
	{
		mMesh->render();
	}

	Mesh* getMesh() { return mMesh; }
	void setMesh(Mesh* mesh) { this->mMesh = mesh; }

	Texture* getTexture() { return mTexture; }
	void setTexture(Texture* texture) { this->mTexture = texture; }

protected:
	Mesh* mMesh;
	Texture* mTexture;
private:
};
