#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Object.h"

class PhysicsObject : public Object
{

public:
    
private:

protected:
    glm::vec3 velocity; // world units per second
    
    float radius;
};
