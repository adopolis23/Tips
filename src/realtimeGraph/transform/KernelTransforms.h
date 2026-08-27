#pragma once

#include "Globals.h"
#include "Transform.h"

#include <vector>

class SmoothingKernel : public Transform
{

    public:
        SmoothingKernel(unsigned int kernelSize)
            :mKernelSize(kernelSize)
        { }

        std::vector<DataPoint> Apply(const std::vector<DataPoint>& data)
        {
            std::vector<DataPoint> result = data;

            for (int i{0}; i < result.size(); i++)
            {
                if (i >= mKernelSize && i <= result.size()-mKernelSize)
                {
                    float sum = 0;
                    for (int j{i-(int)mKernelSize}; j < i + mKernelSize + 1; j++)
                    {
                        sum = sum + data[j].y; 
                    }
                    result[i].y = sum / (static_cast<float>(mKernelSize) * 2 + 1);
                }
            }

            return result; 
        }

    private:
        unsigned int mKernelSize;
};
