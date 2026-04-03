#include "Rotor.h"


Rotor::Rotor(int radius, glm::vec3 position) 
{
    this->m_position = position;

    m_shaft = new Circle(30, radius, position);

    // add the shaft to child objects
    ChildObjects[m_shaft->objectId] = m_shaft;

    int num_blades = 10;
    float angle_per_blade = 2 * M_PI / num_blades;

    printf("Angle per blade is: %f\n", angle_per_blade);

    for (int blade_idx = 0; blade_idx < num_blades; blade_idx++)
    {
        Blade* blade = new Blade(position, 100, blade_idx * angle_per_blade);
        blade->RotateAroundPivot(position, glm::vec3(0, 0, blade_idx * angle_per_blade));

        ChildObjects[blade->GetObjectId()] = blade;
        m_blades.push_back(blade);
    }
}

void Rotor::Update()
{
    Rotate(0.1f);
}

void Rotor::Rotate(float angle)
{
    for (auto& blade : m_blades)
    {
        blade->RotateAroundPivot(this->position, glm::vec3(0, 0, angle));
    }
}
