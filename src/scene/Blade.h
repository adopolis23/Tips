#pragma once

#include "Object.h"
#include <glm/ext/vector_float3.hpp>

class Blade : public Object
{

public:
    Blade(glm::vec3 position, unsigned int length, float width);
    glm::vec3 GetBladeTip();

private:
    void GenerateVerticies();

    float m_length;
    float m_width;

    glm::vec3 m_bladeTip;

    // ratio of blades length to its width
    float m_ratio = 4;

};
