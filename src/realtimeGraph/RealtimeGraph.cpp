#include "RealtimeGraph.h"
#include "Globals.h"
#include <cstring> // for std::memmove
#include <cstdio>
#include "transform/BasicTransforms.h"
#include "transform/KernelTransforms.h"
#include "transform/FourierTransform.h"

RealtimeGraph::RealtimeGraph(int x, int y, int w, int h, std::size_t capacity, Camera* camera)
    :mDataPipeline(capacity)
{
	this->mCamera = camera;

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


    // Add members to the data pipeline
    //mDataPipeline.AddTransform<Gain>(200.0f);
    //mDataPipeline.AddTransform<FourierTransform>();
    //mDataPipeline.AddTransform<VerticalTranslate>(-200.0f);
}

void RealtimeGraph::AddDataPoint(DataPoint data) {

    mDataPipeline.AddDataPoint(DataPoint{data.x, data.y, data.channel});
    
    // Update the buffer at this position
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, mDataPipeline.GetCapacity() * sizeof(DataPoint), mDataPipeline.GetData().data());
}


std::size_t RealtimeGraph::GetCapacity()
{
    return this->mDataPipeline.GetCapacity();
}


void RealtimeGraph::GenerateModel()
{
    this->mModel = glm::mat4(1.0f);
    
    // Translate to left edge
    this->mModel = glm::translate(this->mModel, 
                    glm::vec3(mCamera->left_window_bound, 0.0f, 0.0f));
}

