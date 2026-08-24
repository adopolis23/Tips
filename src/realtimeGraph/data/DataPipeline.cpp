#include "DataPipeline.h"
#include <cstddef>
#include <memory>

DataPipeline::DataPipeline(size_t capacity) :mCapacity(capacity)
{
    mData.reserve(capacity);

    // Init to all zeros
    for (std::size_t i{0zu}; i < mCapacity; i++)
    {
        mData[i] = DataPoint(i, 0.0f, 0u);
    }
}


void DataPipeline::AddDataPoint(DataPoint point)
{
    //DebugPrintBuffer();
    if (mData.size() >= mCapacity)
    {
        mData.erase(mData.begin());
    }
    mData.push_back(point); 
}


std::vector<DataPoint> DataPipeline::GetData() const
{
    if (mTransformPipeline.size() == 0) return mData;

    std::vector<DataPoint> result = mData;

    for (const auto& transform : mTransformPipeline)
    {
        result = transform->Apply(result);
    }

    return result;
}

void DataPipeline::DebugPrintBuffer()
{
    for (std::size_t i{0zu}; i < mData.size(); i++)
    {
        printf("{%f, %f} ", mData[i].x, mData[i].y);
    }
    printf("\n");
}
