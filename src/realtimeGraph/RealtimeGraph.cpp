#include "RealtimeGraph.h"

RealtimeGraph::RealtimeGraph(int x, int y, int w, int h, std::size_t capacity)
{
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

}

void RealtimeGraph::AddDataPoint(float x, float y) {

    this->mData[this->mWritePosition] = DataPoint{x, y};
    
    // Update the buffer at this position
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferSubData(GL_ARRAY_BUFFER, 
                    mWritePosition * sizeof(DataPoint), 
                    sizeof(DataPoint),  
                    &mData[mWritePosition]);
    
    // Move to next position (circular)
    mWritePosition = (mWritePosition + 1) % mCapacity;
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
