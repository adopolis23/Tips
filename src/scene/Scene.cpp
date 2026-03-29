#include "Scene.h"

void Scene::AddObjectToScene(Object* object)
{
	int index = object->GetObjectId();
	objects[index] = object;
	objectCount++;
}
