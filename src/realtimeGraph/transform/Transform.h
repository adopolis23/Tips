#pragma once

#include <vector>

template <typename T>
class Transform
{

    public:
        Transform () {};
        virtual ~Transform () = default;

        inline std::vector<T> GetData() const
        {
            return mData;
        }

    private:
        std::vector<T> mData;

};
