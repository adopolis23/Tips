#include <SDL2/SDL_video.h>
#include <chrono>
#include <complex>
#include <memory>
#include "window/Window.h"
#include "scene/Scene.h"
#include "scene/Camera.h"
#include "engine/Engine.h"
#include "scene/Rotor.h"
#include "renderer/Renderer.h"
#include "realtimeGraph/RealtimeGraph.h"
#include "realtimeGraph/transform/BasicTransforms.h"
#include "realtimeGraph/transform/FourierTransform.h"
#include "realtimeGraph/transform/KernelTransforms.h"

#define SENSOR_Y_CORRECTION 30

void InitializeSimulation(Scene& scene, Engine& engine)
{
    
   // Rotor
   scene.AddObjectToScene(new Rotor(200, glm::vec3{0, 0, 0})); 

   // add the visual sensor objects to the scene
   scene.AddObjectToScene(new Blade(glm::vec3(200, 0 - SENSOR_Y_CORRECTION, 0), 10, 10));
   engine.AddSensor(glm::vec3(200, 0 - SENSOR_Y_CORRECTION, 0));

   //scene.AddObjectToScene(new Blade(glm::vec3(0, 200 - SENSOR_Y_CORRECTION, 0), 10, 10));
   //engine.AddSensor(glm::vec3(0, 200 - SENSOR_Y_CORRECTION, 0));

   //scene.AddObjectToScene(new Blade(glm::vec3(-200, 0 - SENSOR_Y_CORRECTION, 0), 10, 10));
   //engine.AddSensor(glm::vec3(-200, 0 - SENSOR_Y_CORRECTION, 0));

   //scene.AddObjectToScene(new Blade(glm::vec3(0, -200 - SENSOR_Y_CORRECTION, 0), 10, 10));
   //engine.AddSensor(glm::vec3(0, -200 - SENSOR_Y_CORRECTION, 0));

}



int main(int argc, char** argv)
{
    int width = 800;
    int height = 600;

    bool running = true;

    auto window = std::make_unique<Window>("Tips Blade Clearance Simulation", width, height, 0, SDL_WINDOWPOS_CENTERED); 
    Camera* camera = new Camera(width, height);
    auto renderer = std::make_unique<Renderer>(camera);

    Scene Simulation(10, 10, width/2 - 10, height/2 - 10);

    RealtimeGraph realtimeGraph(10, height/2 + 10, width - 20, height/2 - 20, 512, camera);
    // Add transforms to the data pipeline
    realtimeGraph.AddTransform<Gain>(350.0f);
    realtimeGraph.AddTransform<VerticalTranslate>(-200.0f);

    RealtimeGraph realtimeGraph2(width/2 + 10, 10, width/2 - 20, height/2 - 10, 512, camera);
    // Add transforms to the data pipeline
    realtimeGraph2.AddTransform<Gain>(8.0f);
    //realtimeGraph2.AddTransform<SmoothingKernel>(5);
    realtimeGraph2.AddTransform<FourierTransform>();
    realtimeGraph2.AddTransform<VerticalTranslate>(-250.0f);

    Engine engine(&Simulation);
    engine.AddDataListener([&realtimeGraph](DataPoint data) { realtimeGraph.AddDataPoint(data); });
    engine.AddDataListener([&realtimeGraph2](DataPoint data) { realtimeGraph2.AddDataPoint(data); });

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

        Simulation.Update(frametime);
        engine.Update();

        renderer->RenderScene(Simulation);
        renderer->RenderRealtimeGraph(realtimeGraph);
        renderer->RenderRealtimeGraph(realtimeGraph2);
        
        window->SwapBuffers();

        // // 
        
        //timing and fps check
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> iterationTime = endTime - startTime;
        std::chrono::duration<double, std::milli> timeInSeconds = iterationTime / 1000;

        frametime = iterationTime.count();
        float fps = 1 / timeInSeconds.count();

        if (iter % 200 == 0)
        {
            printf("%f fps\n", fps);
        }

    }


    return 0;
}
