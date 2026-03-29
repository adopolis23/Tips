#pragma once
#include <glm/glm.hpp>

class Object 
{

public:
    Object()
    {
        // set this objects unique ID
        objectId = objectCount;
        objectCount++;
    }

    ~Object()
    {
        objectCount--;
    }

    int GetObjectId();

private:
    static int objectCount;

protected:
    // 3d matricies for position rotation and scale
    glm::vec3 position{0.0f};
    glm::vec3 rotation{0.0f};
    glm::vec3 scale{1.0f};

    int objectId;


};
