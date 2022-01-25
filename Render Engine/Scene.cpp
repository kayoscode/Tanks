#include "Scene.h"

void Scene::render()
{
	mRenderPipeline->render(*this);
}

void Scene::init()
{
	this->onInit();
	mRenderPipeline->init(*this);
}

void Scene::update()
{
}
