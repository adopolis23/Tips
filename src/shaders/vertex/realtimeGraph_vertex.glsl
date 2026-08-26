#version 330 core

layout (location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int startIndex;
uniform int totalPoints;


void main()
{
    float adjustedX = (gl_VertexID) % totalPoints;

    gl_Position = projection * view * model * vec4(adjustedX, aPos.y, 0.0, 1.0);
}
