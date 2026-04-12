#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include "shaders/Shader.h"
#include "scene/Camera.h"
#include "Globals.h"
#include <SDL2/SDL.h>


class RealtimeGraph
{

public:
    RealtimeGraph(int x, int y, int w, int h, std::size_t capacity, Camera* camera);
    void AddDataPoint(float y, int channel);

    GLuint GetVbo();
    GLuint GetVao();
    std::size_t GetCapacity();
    Shader* GetShader();
    SDL_Rect GetViewport();

    const glm::mat4& GetModel();

    void GenerateModel();

private:
    std::size_t mNumDataPoints = 0;
    std::size_t mCapacity;

    std::vector<DataPoint> mData;

    GLuint mVbo;
    GLuint mVao;

    uint32_t mWritePosition;

    Shader* mDefaultShader;

    // pointer to the global camera
    Camera* mCamera;

    SDL_Rect mViewport;

    glm::mat4 mModel;

};
