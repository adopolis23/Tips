#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include "shaders/Shader.h"
#include "scene/Camera.h"
#include "RealtimeGraphRenderable.h"
#include "Globals.h"
#include <SDL2/SDL.h>
#include "realtimeGraph/data/DataPipeline.h"



class RealtimeGraph : public RealtimeGraphRenderable
{

public:
    RealtimeGraph(int x, int y, int w, int h, std::size_t capacity, Camera* camera);
    void AddDataPoint(DataPoint data);

    std::size_t GetCapacity();

    void GenerateModel();

private:
    void DataBufferLeftShift(uint8_t n);

    std::size_t mNumDataPoints = 0;
    std::size_t mCapacity;

    std::vector<DataPoint> mData;


    uint32_t mWritePosition;


};
