#pragma once
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>

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

public:

    // creates the model from the position and the rotation
    void GenerateObjectModel();

    void RotateAroundPivot(const glm::vec3& pivot, const glm::vec3& rotationDelta);

    // transforms a given vertex relative to the objects origin to the worls space based on the objects model
    glm::vec3 GetWorldVertexLocation(const glm::vec3& localVertexLocation);

    virtual void Update(float dt)
    {
        // default implementation
    }

    // the 4 dimentional model of the object
    glm::mat4 model;

    unsigned int vao = 0;
    
    unsigned int vbo = 0;

    int VertexCount = 0;
    std::vector<float> Verticies;

    // 3d matricies for position rotation and scale
    glm::vec3 position{0.0f};
    glm::vec3 rotation{0.0f};
    glm::vec3 scale{1.0f};

    int objectId;

    std::unordered_map<int, Object*> ChildObjects;


};
