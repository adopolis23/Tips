#pragma once

#include <vector>
#include "Globals.h"

class Transform
{

    public:
        Transform () {};
        virtual ~Transform () = default;

        inline std::vector<DataPoint> GetData() const
        {
            return mData;
        }

        virtual std::vector<DataPoint> Apply(const std::vector<DataPoint>& data) = 0;

    private:
        std::vector<DataPoint> mData;

};
