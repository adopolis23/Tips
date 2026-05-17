#include "RealtimeGraph.h"
#include <cstring> // for std::memmove
#include <cstdio>

RealtimeGraph::RealtimeGraph(int x, int y, int w, int h, std::size_t capacity, Camera* camera)
{
	this->mCamera = camera;

    this->mCapacity = capacity;
    this->mData.resize(capacity);

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


    // Initialize with zeros
    for (std::size_t i = 0; i < mCapacity; i++)
    {
        mData[i] = DataPoint{static_cast<float>(i), 0.0f};
    }

    // Upload all data initially
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, capacity * sizeof(DataPoint), mData.data());


    this->mViewport.x = x;
    this->mViewport.y = y;
    this->mViewport.w = w;
    this->mViewport.h = h;

	GenerateModel();
}

void RealtimeGraph::AddDataPoint(float y, int channel) {

    //printf("Adding datapoint: %zu, %f, %d\n", this->mWritePosition, y, channel);

    if (mWritePosition == mCapacity - 1 && mNumDataPoints == mCapacity)
    {
        // shift left one so the oldest sample is dropped and the last slot becomes free for the new point
        DataBufferLeftShift(1);
    }

    this->mData[this->mWritePosition] = DataPoint{(float)this->mWritePosition, y, (uint8_t)channel};
    
    if (mNumDataPoints < mCapacity)
    {
        mNumDataPoints++;
    }
    
    // Update the buffer at this position
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferSubData(GL_ARRAY_BUFFER, mWritePosition * sizeof(DataPoint), sizeof(DataPoint),  &mData[mWritePosition]);
    
    // Move to next position (circular)
    //mWritePosition = (mWritePosition + 1) % mCapacity;
    if (mWritePosition < mCapacity-1)
    {
        mWritePosition++;
    }
}

GLuint RealtimeGraph::GetVbo()
{
    return this->mVbo;
}

GLuint RealtimeGraph::GetVao()
{
    return this->mVao;
}

std::size_t RealtimeGraph::GetCapacity()
{
    return this->mCapacity;
}


Shader* RealtimeGraph::GetShader()
{
    return this->mDefaultShader;
}

SDL_Rect RealtimeGraph::GetViewport()
{
    return this->mViewport;
}

const glm::mat4& RealtimeGraph::GetModel()
{
    return this->mModel;
}

void RealtimeGraph::GenerateModel()
{
    float scaleX = static_cast<float>(mCamera->window_width) / static_cast<float>(mCapacity);
    this->mModel = glm::mat4(1.0f);

    // translate first to left_window_bound, then scale X so each unit of x maps into the viewport width
    this->mModel = glm::translate(this->mModel, glm::vec3(mCamera->left_window_bound, 0.0f, 0.0f));
    this->mModel = glm::scale(this->mModel, glm::vec3(scaleX, 1.0f, 1.0f));


    // create the scaling for the Y axis, TODO: this needs to be done automatically in the future
    //float scaleY = static_cast<float>(mCamera->top_window_bound) / 0.10;
    float gain = 200;
    this->mModel = glm::scale(this->mModel, glm::vec3(1.0f, gain, 1.0f));
}


void RealtimeGraph::DataBufferLeftShift(uint8_t n)
{
    if (n == 0 || mNumDataPoints == 0) return;

    // If shifting more than we have, just clear the buffer region (no valid points)
    if (n >= mNumDataPoints)
    {
        mNumDataPoints = 0;
        return;
    }

    std::memmove(&mData[0], &mData[n], (mNumDataPoints - n) * sizeof(DataPoint));

    // TODO: Find a better way to do this every data point should not have to get its x value decremented every time we shift.
    for (int i = 0; i < mNumDataPoints - n - 1; i++)
    {
        this->mData[i].x--;
    }

    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, (mNumDataPoints - n) * sizeof(DataPoint), &mData[0]);
}
