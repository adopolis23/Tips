#include "Rotor.h"


Rotor::Rotor(int radius, glm::vec2 position) 
{
    this->m_position = position;

    m_shaft = new Circle(10, 30, position);
}
