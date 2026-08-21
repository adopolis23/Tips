#include "Engine.h"
#include <cstdint>
#include <glm/geometric.hpp>


Engine::Engine(Scene* scene)
{
    this->mScene = scene;
}

void Engine::AddSensor(glm::vec3 position)
{
    this->mCapactiveSensorPostions.push_back(position);
}

unsigned int Engine::GetNumSensors()
{
    return this->mCapactiveSensorPostions.size();
}

float Engine::ReadSensorValue(int index)
{
    float sensorValue = 0.0f;
    glm::vec3 thisPosition = mCapactiveSensorPostions[index];

    for (auto& [id, obj] : this->mScene->objects)
    {
       if (dynamic_cast<Rotor*>(obj)) 
       {
           float distToTip;
           glm::vec3 tipPosition; 
           for (auto& blade : ((Rotor*)obj)->m_blades)
           {
                tipPosition = ((Blade*)blade)->GetBladeTip(); 

                distToTip = glm::distance(thisPosition, tipPosition);
                sensorValue += CapacitySmoothingKernel(G_CapacitiveKernelSize, distToTip);

           }
       }
    }

    return sensorValue;
}

void Engine::Update()
{
    for (size_t sensorIndex{0zu}; sensorIndex < mCapactiveSensorPostions.size(); sensorIndex++)
    {
        if (this->mDataListeners.size() == 0)
            break;

        float sensorValue = this->ReadSensorValue(sensorIndex);
        
        // Distribute the data to all listeners
        DataPoint data{0, sensorValue, (uint8_t)sensorIndex};
        for (DataCallbackFn fn : mDataListeners)
        {
            fn(data);
        }
    }
}

float Engine::CapacitySmoothingKernel(float radius, float dist)
{
    return radius * (1 / (dist * dist));
}

void Engine::AddDataListener(DataCallbackFn func)
{
    this->mDataListeners.push_back(func);
}
