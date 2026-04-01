#include "Rotor.h"


Rotor::Rotor(int radius, glm::vec2 position) 
{
    this->m_position = position;

    m_shaft = new Circle(30, radius, position);

    // add the shaft to child objects
    ChildObjects[m_shaft->objectId] = m_shaft;
}
