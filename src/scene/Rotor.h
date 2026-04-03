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
    Rotor(int radius, glm::vec3 position);

    void Update() override;

    void Rotate(float angle);

private:

    glm::vec3 m_position;

    // center of the rotor.
    Circle* m_shaft;

    std::vector<Object*> m_blades;


};
