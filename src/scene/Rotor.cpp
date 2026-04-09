#include "Rotor.h"


Rotor::Rotor(float radius, glm::vec3 position) 
{
    this->position = position;
    this->m_radius = radius;

    m_shaft = new Circle(30, radius/6, position);

    // add the shaft to child objects
    ChildObjects[m_shaft->objectId] = m_shaft;

    int num_blades = 16;
    float angle_per_blade = 2 * M_PI / num_blades;

    printf("Angle per blade is: %f\n", angle_per_blade);

    for (int blade_idx = 0; blade_idx < num_blades; blade_idx++)
    {
        Blade* blade = new Blade(position, radius*5/6, 15);
        blade->RotateAroundPivot(position, glm::vec3(0, 0, blade_idx * angle_per_blade));

        ChildObjects[blade->GetObjectId()] = blade;
        m_blades.push_back(blade);
    }
}

void Rotor::Update()
{
    Rotate(0.01f);
}

void Rotor::Rotate(float angle)
{
    for (auto& blade : m_blades)
    {
        blade->RotateAroundPivot(this->position, glm::vec3(0, 0, angle));

        //glm::vec3 tip = ((Blade*)blade)->GetBladeTip();
        //printf("Blade tip: %f, %f, %f\n", tip.x, tip.y, tip.z);
    }
}

unsigned int Rotor::GetNumBlades()
{
    return this->m_blades.size();
}

Object* Rotor::GetBlade(unsigned int index)
{
    return m_blades[index]; 
}
