#pragma once

#include <vector>
#include <stdio.h>
#include <glm/glm.hpp>
#include "scene/Scene.h"
#include "scene/Object.h"
#include "scene/Blade.h"
#include "scene/Rotor.h"
#include "Globals.h"

class Engine
{

public:
    Engine(Scene* scene);

    void Update();
    
    void AddSensor(glm::vec3 position);

    unsigned int GetNumSensors();

    float ReadSensorValue(int index);

private:
    std::vector<glm::vec3> mCapactiveSensorPostions;

    float CapacitySmoothingKernel(float radius, float dist);

    Scene* mScene;


};
