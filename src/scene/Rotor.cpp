#include "Rotor.h"


Rotor::Rotor(int radius, glm::vec2 position) 
{
    this->m_position = position;

    m_shaft = new Circle(30, radius, position);

    m_blade = new Blade(50, 0.0f, radius*2);

    // add the shaft to child objects
    ChildObjects[m_shaft->objectId] = m_shaft;
    ChildObjects[m_blade->objectId] = m_blade;
}
