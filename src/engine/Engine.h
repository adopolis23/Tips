#pragma once

#include <vector>
#include <stdio.h>
#include <glm/glm.hpp>
#include <functional>
#include "scene/Scene.h"
#include "scene/Object.h"
#include "scene/Blade.h"
#include "scene/Rotor.h"
#include "Globals.h"
#include "realtimeGraph/data/DataPipeline.h"

class Engine
{
    using DataCallbackFn = std::function<void(::DataPoint)>;

public:
    Engine(Scene* scene);

    void Update();
    
    void AddSensor(glm::vec3 position);

    unsigned int GetNumSensors();

    float ReadSensorValue(int index);

    void AddDataListener(DataCallbackFn func);
    

private:
    std::vector<glm::vec3> mCapactiveSensorPostions;

    float CapacitySmoothingKernel(float radius, float dist);

    Scene* mScene;

    // data callback will add a datapoint with the value (float) and the channel (int)
    std::vector<DataCallbackFn> mDataListeners;
};
