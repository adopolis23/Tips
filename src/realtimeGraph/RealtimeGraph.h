#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <cstdint>
#include <cstdlib>
#include <iterator>
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

    [[ nodiscard ]]
    std::size_t GetCapacity();

    void GenerateModel() override;

    inline int GetStartingIndex() { return mDataPipeline[0].x; }

    template <typename TransformType, typename... Args>
    void AddTransform(Args&&... args)
    {
        mDataPipeline.AddTransform<TransformType>(std::forward<Args>(args)...);
    }

private:
    DataPipeline mDataPipeline;

};
