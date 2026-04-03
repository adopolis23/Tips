#include "Object.h"

class Blade : public Object
{

public:
    Blade(unsigned int length, float angle);

private:
    void GenerateVerticies();

    float m_length;
    float m_width;
    float m_angle;

    // ratio of blades length to its width
    float m_ratio = 4;

};
