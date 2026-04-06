#pragma once

#include "scene/Scene.h"
#include "shader/Shader.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "scene/Camera.h"

class Renderer
{

public:
    Renderer(const Camera* cam);
    void Render(Object* obj, Scene& scene);
    void RenderScene(Scene& scene);
private:

    glm::mat4 view;
    glm::mat4 projection;

    // pointer to external camera object that stores the projetion used for rendering
    const Camera* camera;

    Shader* defaultShader;
};
