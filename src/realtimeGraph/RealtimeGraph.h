#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <cstdint>
#include <cstdlib>
#include <vector>

struct DataPoint
{
    float x;
    float y;
};

class RealtimeGraph
{

public:
    RealtimeGraph(std::size_t capacity);
    void AddDataPoint(float x, float y);

private:
    std::size_t mNumDataPoints = 0;
    std::size_t mCapacity;

    std::vector<DataPoint> mData;

    GLuint mVbo;

    uint32_t mWritePosition;

};
