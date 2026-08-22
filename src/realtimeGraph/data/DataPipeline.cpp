#include "DataPipeline.h"
#include <cstddef>
#include <memory>

DataPipeline::DataPipeline(size_t capacity) :mCapacity(capacity)
{
    mData.reserve(capacity);
}


void DataPipeline::AddDataPoint(DataPoint point)
{
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

