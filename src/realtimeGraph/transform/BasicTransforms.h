#pragma once

#include "Globals.h"
#include "Transform.h"

#include <vector>

class Gain : public Transform
{

    public:
        Gain(float gain)
            :mGain(gain)
        { }

        std::vector<DataPoint> Apply(const std::vector<DataPoint>& data)
        {
            std::vector<DataPoint> result = data;

            for (auto& val : result)
            {
                val.y = val.y * mGain;
            }

            return result; 
        }

    private:
        float mGain;
};

class VerticalTranslate : public Transform
{

    public:
        VerticalTranslate(float displacement)
            :mDisplacement(displacement)
        { }

        std::vector<DataPoint> Apply(const std::vector<DataPoint>& data)
        {
            std::vector<DataPoint> result = data;

            for (auto& val : result)
            {
                val.y = val.y + mDisplacement;
            }

            return result; 
        }

    private:
        float mDisplacement;
};
