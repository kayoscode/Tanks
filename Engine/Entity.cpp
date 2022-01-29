#include "Entity.h"
#include "Logger/StaticLogger.h"

void Entity::updateComponents(Scene* scene)
{
	for (auto i = mComponents.begin(); i != mComponents.end(); ++i)
	{
		i->second->update(this, scene);
	}
}

bool Entity::addComponent(const std::string& name, std::unique_ptr<IComponent> component)
{
	if (mComponents.find(name) == mComponents.end())
	{
		//component->init(this);
		mComponents[name] = std::move(component);
		return true;
	}

	StaticLogger::instance.error("Failed to add component: {string}", name.c_str());

	return false;
}

IComponent* ObjectWithComponents::getComponent(const std::string& name)
{
	std::map<std::string, std::unique_ptr<IComponent>>::iterator value =
		mComponents.find(name);

	if (value == mComponents.end())
	{
		StaticLogger::instance.error("Could not find component: {string}", name.c_str());
		return nullptr;
	}

	return value->second.get();
}

Entity::Entity(const std::string& tag)
	:mTag(tag),
	mTransform(std::make_unique<TransformComponent>())
{
}

Entity::~Entity()
{

}

void Entity::init(Scene* scene)
{
	mTransform->init(this, scene);

	for (auto component = mComponents.begin(); component != mComponents.end(); ++component)
	{
		component->second->init(this, scene);
	}
}

void Entity::update(Scene* scene)
{
	updateComponents(scene);
}

RenderableEntity::RenderableEntity(Mesh* mesh, 
	Texture* texture, 
	const std::string& tag)
	:Entity(tag),
	mMesh(mesh),
	mTexture(texture)
{
}

RenderableEntity::~RenderableEntity()
{
}

void RenderableEntity::render()
{
	// Bind the texture to slot 0.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture->getDiffuseID());

	// Render the mesth.
	mMesh->render();
}
