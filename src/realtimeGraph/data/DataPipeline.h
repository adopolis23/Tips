#pragma once
#include <cstddef>
#include <memory>
#include <vector>
#include <cstdint>

#include "Globals.h"
#include "realtimeGraph/transform/Transform.h"

class DataPipeline
{


    public:
        DataPipeline(size_t capacity);
        ~DataPipeline() = default;

        void AddDataPoint(DataPoint point);

        inline const std::vector<DataPoint> GetOriginalData() const { return mData; }

        template <typename TransformType, typename... Args>
        void AddTransform(Args&&... args)
        {
            mTransformPipeline.push_back(
                std::make_unique<TransformType>(std::forward<Args>(args)...)
            );
        }

        std::vector<DataPoint> GetData() const;

    private:
        size_t mCapacity{0};
        std::vector<DataPoint> mData; 
        std::vector<std::unique_ptr<Transform>> mTransformPipeline; 

};
