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

void Object::RotateAroundPivot(const glm::vec3& pivot, const glm::vec3& rotationDelta)
{
    // Save current transformations
    glm::vec3 currentPosition = position;
    glm::vec3 currentRotation = rotation;
    glm::vec3 currentScale = scale;
    
    // Move object so pivot is at origin
    glm::vec3 offset = position - pivot;
    
    // Apply rotation delta to the offset
    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, rotationDelta.x, glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, rotationDelta.y, glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, rotationDelta.z, glm::vec3(0, 0, 1));
    
    // Apply rotation to the offset
    glm::vec4 rotatedOffset = rotationMatrix * glm::vec4(offset, 1.0f);
    
    // Calculate new position
    glm::vec3 newPosition = pivot + glm::vec3(rotatedOffset);
    
    // Update objects rotation (accumulate rotation)
    glm::vec3 newRotation = currentRotation + rotationDelta;
    
    // Apply the transformations
    position = newPosition;
    rotation = newRotation;
    
    // Regenerate the model matrix
    GenerateObjectModel();
}

glm::vec3 Object::GetWorldVertexLocation(const glm::vec3& localVertex)
{
    glm::vec4 worldVertex = this->model * glm::vec4(localVertex, 1.0f);
    return glm::vec3(worldVertex);
}
