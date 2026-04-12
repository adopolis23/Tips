#include <SDL2/SDL_video.h>
#include <chrono>
#include "window/Window.h"
#include "scene/Scene.h"
#include "scene/Camera.h"
#include "engine/Engine.h"
#include "scene/Rotor.h"
#include "renderer/Renderer.h"
#include "realtimeGraph/RealtimeGraph.h"

#define SENSOR_Y_CORRECTION 30

void InitializeSimulation(Scene& scene, Engine& engine)
{
    
   // Rotor
   scene.AddObjectToScene(new Rotor(200, glm::vec3{0, 0, 0})); 

   // add the visual sensor objects to the scene
   scene.AddObjectToScene(new Blade(glm::vec3(200, 0 - SENSOR_Y_CORRECTION, 0), 10, 10));
   engine.AddSensor(glm::vec3(200, 0 - SENSOR_Y_CORRECTION, 0));

   scene.AddObjectToScene(new Blade(glm::vec3(0, 200 - SENSOR_Y_CORRECTION, 0), 10, 10));
   engine.AddSensor(glm::vec3(0, 200 - SENSOR_Y_CORRECTION, 0));

   scene.AddObjectToScene(new Blade(glm::vec3(-200, 0 - SENSOR_Y_CORRECTION, 0), 10, 10));
   engine.AddSensor(glm::vec3(-200, 0 - SENSOR_Y_CORRECTION, 0));

   scene.AddObjectToScene(new Blade(glm::vec3(0, -200 - SENSOR_Y_CORRECTION, 0), 10, 10));
   engine.AddSensor(glm::vec3(0, -200 - SENSOR_Y_CORRECTION, 0));

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

    Scene Simulation(10, 10, width/2 - 10, height/2 - 10);

    Engine engine(&Simulation);
    RealtimeGraph realtimeGraph(10, height/2 + 10, width - 20, height/2 - 20, 4096);

    InitializeSimulation(Simulation, engine);



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
        engine.Update();

        renderer->RenderScene(Simulation);
        //renderer->RenderRealtimeGraph(realtimeGraph);
        
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
            // std::this_thread::sleep_for(std::chrono::milliseconds((int)(frametime_dt)));            
        }

        if (iter % 200 == 0)
        {
            printf("%f fps\n", fps);
        }

    }


    return 0;
}
