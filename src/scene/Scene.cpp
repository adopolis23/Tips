#include "Scene.h"

void Scene::AddObjectToScene(Object* object)
{
	int index = object->objectId;
	objects[index] = object;
	objectCount++;
}

void Scene::Update()
{
    for (auto& [id, obj] : objects)
    {
        obj->Update();
    }
}
