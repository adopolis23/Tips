#include "Scene.h"

Scene::Scene(int x, int y, int w, int h)
{
    this->Viewport.x = x;
    this->Viewport.y = y;
    this->Viewport.w = w;
    this->Viewport.h = h;
}

void Scene::AddObjectToScene(Object* object)
{
	int index = object->objectId;
	objects[index] = object;
	objectCount++;
}

void Scene::Update(float dt)
{
    for (auto& [id, obj] : objects)
    {
        obj->Update(dt);
    }
}
