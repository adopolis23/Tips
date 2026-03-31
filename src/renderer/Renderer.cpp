#include "Renderer.h"


void Renderer::Render(Object* obj)
{
    if (obj->vao != 0 && obj->VertexCount != 0)
    {
        // bind the default shader for now every time
        defaultShader->bind();

        // need to do this before the render loop
        obj->GenerateObjectModel();

        // set things in the shader program
        // model comes from the object and has all of the transformation data
        defaultShader->setMat4("model", obj->model);
        // view and projection come from the renderer and have all of the aspect
        // information
        defaultShader->setMat4("view", view);
        defaultShader->setMat4("projection", camera->projection);

        glBindVertexArray(obj->vao);
        glDrawArrays(GL_TRIANGLES, 0, obj->VertexCount);
    }

    // call render for each of this objects children.
    // base case is when child object has no children and then this recursion will not be called
    for (auto &[child_id, child_obj] : obj->ChildObjects)
    {
        Render(child_obj); 
    }
}

void Renderer::RenderScene(Scene& scene) {
  glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (auto &[id, obj] : scene.objects) {
    Render(obj);
  }
}

Renderer::Renderer(const Camera *cam) : camera(cam) {
  view = glm::mat4(1.0f); // identity camera

  // set the default shader for now. This might be replaced per object in the
  // future
  defaultShader = new Shader("src/shaders/vertex/default_vertex.glsl",
                             "src/shaders/fragment/default_fragment.glsl");
}

