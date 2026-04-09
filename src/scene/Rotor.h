#pragma once

#include <vector>
#include <stdio.h>
#include "Circle.h"
#include "Globals.h"
#include "Blade.h"
#include "Object.h"

class Rotor : public Object
{

public:
    Rotor(float radius, glm::vec3 position);

    void Update() override;

    void Rotate(float angle);

    unsigned int GetNumBlades();

    Object* GetBlade(unsigned int index); 

private:
    float m_radius;

    // center of the rotor.
    Circle* m_shaft;

    std::vector<Object*> m_blades;


};
