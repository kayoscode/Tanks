#include "Scene.h"

void Scene::render()
{
	mRenderPipeline->render();
}

void Scene::init()
{
	mRenderPipeline->init();
}
