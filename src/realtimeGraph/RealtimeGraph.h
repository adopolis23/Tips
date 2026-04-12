#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include "shaders/Shader.h"
#include <SDL2/SDL.h>

struct DataPoint
{
    float x;
    float y;
};

class RealtimeGraph
{

public:
    RealtimeGraph(int x, int y, int w, int h, std::size_t capacity);
    void AddDataPoint(float x, float y);

    GLuint GetVbo();
    GLuint GetVao();
    std::size_t GetCapacity();
    Shader* GetShader();
    SDL_Rect GetViewport();

private:
    std::size_t mNumDataPoints = 0;
    std::size_t mCapacity;

    std::vector<DataPoint> mData;

    GLuint mVbo;
    GLuint mVao;

    uint32_t mWritePosition;

    Shader* mDefaultShader;

    SDL_Rect mViewport;

};
