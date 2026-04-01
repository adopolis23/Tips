#include "scene.h"

void Scene::AddObjectToScene(Object* object)
{
	int index = object->objectId;
	objects[index] = object;
	objectCount++;
}
