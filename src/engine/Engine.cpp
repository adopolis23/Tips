#include "Engine.h"
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
;
                //printf("Blade tip: %f, %f, %f\n", tip.x, tip.y, tip.z);
           }
       }
    }

    return sensorValue;
}

void Engine::Update()
{
    for (int sensorIndex = 0; sensorIndex < mCapactiveSensorPostions.size(); sensorIndex++)
    {
        float sensorValue = this->ReadSensorValue(sensorIndex);
        //printf("Sensor value is: %f\n", sensorValue);
        break;
    }
}

float Engine::CapacitySmoothingKernel(float radius, float dist)
{
    return radius * (1 / (dist * dist));
}

