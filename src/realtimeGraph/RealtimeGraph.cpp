#include "RealtimeGraph.h"
#include "Globals.h"
#include <cstring> // for std::memmove
#include <cstdio>

RealtimeGraph::RealtimeGraph(int x, int y, int w, int h, std::size_t capacity, Camera* camera)
    :mDataPipeline(capacity)
{
	this->mCamera = camera;

    //this->mData.resize(capacity);

    this->mWritePosition = 0;

    // Create VBO with dynamic draw hint
    glGenBuffers(1, &mVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, capacity * sizeof(DataPoint), nullptr, GL_DYNAMIC_DRAW);

    // Create VAO so we don't accidentally overwrite other VAOs' attribute state
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    // bind VBO and setup attribute layout for this VAO
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    // Position attribute (location 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DataPoint), (void*)0);

    // unbind VAO to keep state isolated
    glBindVertexArray(0);

    // create the default shader
    mDefaultShader = new Shader("src/shaders/vertex/realtimeGraph_vertex.glsl",
                         "src/shaders/fragment/default_fragment.glsl");


    // Upload all data initially
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, capacity * sizeof(DataPoint), mDataPipeline.GetData().data());


    this->mViewport.x = x;
    this->mViewport.y = y;
    this->mViewport.w = w;
    this->mViewport.h = h;

	GenerateModel();
}

void RealtimeGraph::AddDataPoint(DataPoint data) {

    //this->mData[this->mWritePosition] = DataPoint{(float)this->mWritePosition, y, (uint8_t)channel};
    mDataPipeline.AddDataPoint(DataPoint{data.x, data.y, data.channel});
    
    // Update the buffer at this position
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, mDataPipeline.GetCapacity() * sizeof(DataPoint), mDataPipeline.GetData().data());
    
    // Move to next position (circular)
    //mWritePosition = (mWritePosition + 1) % mCapacity;
    if (mWritePosition < mDataPipeline.GetCapacity()-1)
    {
        mWritePosition++;
    }
}


std::size_t RealtimeGraph::GetCapacity()
{
    return this->mDataPipeline.GetCapacity();
}


void RealtimeGraph::GenerateModel()
{
    float scaleX = static_cast<float>(mCamera->window_width) / 
                   static_cast<float>(mDataPipeline.GetCapacity()-1);
    
    this->mModel = glm::mat4(1.0f);
    
    // Translate to left edge
    this->mModel = glm::translate(this->mModel, 
                    glm::vec3(mCamera->left_window_bound, 0.0f, 0.0f));
    
    constexpr float gain = 200.0f;

    // Scale to fit width (x goes from 0 to N-1 mapped to window width)
    this->mModel = glm::scale(this->mModel, 
                    glm::vec3(scaleX, gain, 1.0f));
}


void RealtimeGraph::DataBufferLeftShift(uint8_t n)
{
}
