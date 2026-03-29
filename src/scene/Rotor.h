#pragma once

#include <vector>
#include "Circle.h"
#include "Object.h"


class Rotor : public Object
{

public:
    Rotor(int radius, glm::vec2 position);


private:

    glm::vec2 m_position;

    // center of the rotor.
    Circle* m_shaft;


};
