#include <SDL2/SDL_video.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "window/Window.h"
#include "scene/Scene.h"
#include "scene/Camera.h"
#include "scene/Rotor.h"
#include "renderer/Renderer.h"


void InitializeSimulation(Scene& scene)
{
    
   // Rotor
   scene.AddObjectToScene(new Rotor(200, glm::vec3{0, 0, 0})); 

}



int main(int argc, char** argv)
{
    int width = 800;
    int height = 600;

    int target_fps = 15;
    float target_frametime_milli = 1000 / (float) target_fps;

    bool running = true;

    Window* window = new Window("Tips Blade Clearance Simulation", width, height, 0, SDL_WINDOWPOS_CENTERED); 
    Camera* camera = new Camera(width, height);
    Renderer* renderer = new Renderer(camera);

    Scene Simulation;
    InitializeSimulation(Simulation);



    // main render loop
    
    int iter = 0;
    double frametime = 0.0f;
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

        Simulation.Update();
        renderer->RenderScene(Simulation);
        window->SwapBuffers();

        // // 
        
        //timing and fps check
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> iterationTime = endTime - startTime;
        std::chrono::duration<double, std::milli> timeInSeconds = iterationTime / 1000;

        frametime = iterationTime.count();
        float fps = 1 / timeInSeconds.count();

        // if the frametime is less than the target frametime for our target fps
        // this means that the simulation is running too fast so we need to sleep for the difference
        if (frametime < target_frametime_milli)
        {
            float frametime_dt = target_frametime_milli - frametime;
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(frametime_dt)));            
        }

        if (iter % 200 == 0)
        {
            printf("%f fps\n", fps);
        }

    }


    return 0;
}
