#include "RealtimeGraph.h"

RealtimeGraph::RealtimeGraph(std::size_t capacity)
{
    this->mCapacity = capacity;
    this->mData.resize(capacity * sizeof(DataPoint));

    this->mWritePosition = 0;

    // Create VBO with dynamic draw hint
    glGenBuffers(1, &mVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, capacity * sizeof(DataPoint), nullptr, GL_DYNAMIC_DRAW);
}

void RealtimeGraph::AddDataPoint(float x, float y) {

    this->mData[this->mWritePosition] = DataPoint{x, y};
    
    this->mWritePosition = (this->mWritePosition + 1) % this->mCapacity;
    
    // Update only the changed portion
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferSubData(GL_ARRAY_BUFFER, 
                    this->mWritePosition * sizeof(DataPoint), 
                    sizeof(float), 
                    &mData[this->mWritePosition]);
}
