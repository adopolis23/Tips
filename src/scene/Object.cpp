#include "Object.h"

// Definition and initialization of static member
int Object::objectCount = 0;


int Object::GetObjectId()
{
    return this->objectId;
}

void Object::GenerateObjectModel()
{
    glm::mat4 model;

    model = glm::mat4(1.0f);

    model = glm::translate(model, position);

    model = glm::rotate(model, rotation.x, {1, 0, 0});
    model = glm::rotate(model, rotation.y, {0, 1, 0});
    model = glm::rotate(model, rotation.z, {0, 0, 1});
    
    model = glm::scale(model, scale);

    this->model = model;
}

