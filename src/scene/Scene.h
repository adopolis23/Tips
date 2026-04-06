#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <unordered_map>
#include "Object.h"

class Scene
{
    
public:
    Scene(int x, int y, int w, int h);

    std::unordered_map<int, Object*> objects;
    void AddObjectToScene(Object* object);

    int objectCount = 0;

    SDL_Rect Viewport;

    void Update();

private:
    

};
