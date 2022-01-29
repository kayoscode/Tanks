#include "Scene.h"

void Scene::render()
{
	mRenderPipeline->render(*this);
}

void Scene::init()
{
	this->onInit();

	// Init each added entity.
	for (int i = 0; i < mEntities.size(); ++i)
	{
		mEntities[i]->init(this);
	}

	mRenderPipeline->init(*this);
}

void Scene::update()
{
}
