#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Object.h"

class PhysicsObject : public Object
{

public:
    
private:
    // the =0 makes this pure virtual so no implementation in the base class is expected
    virtual void GenerateVerticies() = 0;

protected:

    // the 4 dimentional model of the object
    glm::mat4 model;

    // vertex array object
    unsigned int vao = 0;
    
    unsigned int vbo = 0;

    int VertexCount = 0;
    std::vector<float> Verticies;

    glm::vec3 velocity; // world units per second
    
    float radius;

    virtual void GenerateObjectModel() = 0;

};
