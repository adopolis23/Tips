#pragma once
#include "PhysicsObject.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#define M_PI 3.14159265358979323846

class Circle : public PhysicsObject {

public:
    Circle(int sections, float radius, glm::vec2 pos);
    void GenerateObjectModel();

private:
    int SectorCount;

    void GenerateVerticies();

};
