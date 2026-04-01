#include <SDL2/SDL_video.h>
#include <iostream>
#include <chrono>
#include "window/Window.h"
#include "scene/Scene.h"
#include "scene/Camera.h"
#include "scene/Rotor.h"
#include "renderer/Renderer.h"


void InitializeSimulation(Scene& scene)
{
    
   // Rotor
   scene.AddObjectToScene(new Rotor(30, glm::vec2{0, 0})); 

}



int main(int argc, char** argv)
{
    int width = 800;
    int height = 600;

    bool running = true;

    Window* window = new Window("Tips Blade Clearance Simulation", width, height, 0, SDL_WINDOWPOS_CENTERED); 
    Camera* camera = new Camera(width, height);
    Renderer* renderer = new Renderer(camera);

    Scene Simulation;
    InitializeSimulation(Simulation);



    // main render loop
    
    int iter = 0;
    double dt = 0.0f;
    while (running)
    {
        iter++;
        auto startTime = std::chrono::high_resolution_clock::now();
        
        // handle close event
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        // rendering scene here
        
        renderer->RenderScene(Simulation);
        window->SwapBuffers();

        // // 


        //timing and fps check
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> iterationTime = endTime - startTime;
        std::chrono::duration<double, std::milli> timeInSeconds = iterationTime / 1000;

        dt = iterationTime.count();
        float fps = 1 / timeInSeconds.count();

        if (iter % 200 == 0)
        {
            printf("%f fps\n", fps);
        }

    }


    return 0;
}
