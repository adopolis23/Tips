#include "Renderer.h"


void Renderer::Render(Object* obj, Scene& scene)
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
        Render(child_obj, scene); 
    }
}

void Renderer::RenderScene(Scene& scene) {
    
    glViewport(scene.Viewport.x, scene.Viewport.y, scene.Viewport.w, scene.Viewport.h);

    glEnable(GL_SCISSOR_TEST);
    glScissor(scene.Viewport.x, scene.Viewport.y, scene.Viewport.w, scene.Viewport.h);

    // draw simulation
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto &[id, obj] : scene.objects) {
        Render(obj, scene);
    }

    glDisable(GL_SCISSOR_TEST);
    glViewport(0, 0, camera->window_width, camera->window_height);
}

Renderer::Renderer(const Camera *cam) : camera(cam) {
  view = glm::mat4(1.0f); // identity camera

  // set the default shader for now. This might be replaced per object in the
  // future
  defaultShader = new Shader("src/shaders/vertex/default_vertex.glsl",
                             "src/shaders/fragment/default_fragment.glsl");
}

void Renderer::RenderRealtimeGraph(RealtimeGraph& rtg)
{
    SDL_Rect viewport = rtg.GetViewport();
    glViewport(viewport.x, viewport.y, viewport.w, viewport.h);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewport.x, viewport.y, viewport.w, viewport.h);

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader* shader = rtg.GetShader();
    shader->bind();

    shader->setMat4("view", view);
    shader->setMat4("projection", camera->projection);

    // Bind the graph VAO (attribute state is kept isolated in its own VAO)
    glBindVertexArray(rtg.GetVao());
    glBindBuffer(GL_ARRAY_BUFFER, rtg.GetVbo());

    // Draw
    glDrawArrays(GL_LINE_STRIP, 0, (GLsizei)rtg.GetCapacity());
    
    // Unbind VAO
    glBindVertexArray(0);

    glDisable(GL_SCISSOR_TEST);
    glViewport(0, 0, camera->window_width, camera->window_height);
}

