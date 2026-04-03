#pragma once

#include <vector>
#include <stdio.h>
#include "Circle.h"
#include "Blade.h"
#include "Object.h"

#define M_PI 3.14159

class Rotor : public Object
{

public:
    Rotor(float radius, glm::vec3 position);

    void Update() override;

    void Rotate(float angle);

private:
    float m_radius;

    // center of the rotor.
    Circle* m_shaft;

    std::vector<Object*> m_blades;


};
