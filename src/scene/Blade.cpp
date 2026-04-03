#include "Blade.h"


Blade::Blade(unsigned int length, float angle)
{
    this->m_length = length;
    this->m_angle = angle;

    //this->m_width = this->m_length / this->m_ratio;
    this->m_width = 15;

    this->position.y += length/2 + 25;

    GenerateVerticies();

    // asks opengl to create vao
    glGenVertexArrays(1, &vao);
    // Creates vertex buffer object
    glGenBuffers(1, &vbo);


    // use vertex array provided
    glBindVertexArray(vao);
    // binds vbo and fills it will data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    
    // static draw tells gpu the data wont change much. 
    glBufferData(GL_ARRAY_BUFFER, (Verticies.size() * sizeof(float)), Verticies.data(), GL_STATIC_DRAW);

    // turn on vert slot zero, usually used for positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                  // attribute index (matches layout(location = 0) in shader)
        3,                  // number of components per vertex (x, y, z)
        GL_FLOAT,           // type
        GL_FALSE,           // normalize or not
        3 * sizeof(float),  // stride (distance between vertices)
        (void*)0            // offset into the VBO
    );

}

void Blade::GenerateVerticies()
{
    // bottom right triangle
    Verticies.push_back((-1 * this->m_width / 2));
    Verticies.push_back((-1 * this->m_length / 2));
    Verticies.push_back(0.0f);

    Verticies.push_back(this->m_width / 2);
    Verticies.push_back((-1 * this->m_length / 2));
    Verticies.push_back(0.0f);

    Verticies.push_back(this->m_width / 2);
    Verticies.push_back(this->m_length / 2);
    Verticies.push_back(0.0f);

    // top left triangle
    Verticies.push_back((-1 * this->m_width / 2));
    Verticies.push_back(this->m_length / 2);
    Verticies.push_back(0.0f);

    Verticies.push_back(this->m_width / 2);
    Verticies.push_back(this->m_length / 2);
    Verticies.push_back(0.0f);

    Verticies.push_back(-1 * this->m_width / 2);
    Verticies.push_back(-1 * this->m_length / 2);
    Verticies.push_back(0.0f);

    VertexCount += 6;
}
