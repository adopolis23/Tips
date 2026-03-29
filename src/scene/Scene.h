#pragma once

#include <vector>
#include <unordered_map>
#include "Object.h"

class Scene
{
    
public:
    std::unordered_map<int, Object*> objects;
    void AddObjectToScene(Object* object);

    int objectCount = 0;

private:

};
