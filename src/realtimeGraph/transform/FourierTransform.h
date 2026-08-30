#pragma once

#include "Globals.h"
#include "Transform.h"

#include <cstddef>
#include <vector>
#include <complex>

class FourierTransform : public Transform
{

    public:
        // The default freq step is 0.5 becuase the pos frequencies are 1/2the range of outputs
        // therefor by having half step frequencies the output of this transform is the same size as the input
        FourierTransform(float freq_step_size = 0.5f)
            :mFreqStepSize(freq_step_size)
        { }

        std::vector<DataPoint> Apply(const std::vector<DataPoint>& data)
        {
            mFreqRange = static_cast<float>(data.size()) / 2;

            // Result will hold the magnitude of the computer fourier transoform
            size_t total_output_points = static_cast<int>(std::ceil(mFreqRange / mFreqStepSize));

            std::vector<DataPoint> result;
            //result.reserve(total_output_points);

            std::complex<double> sum; // For each frequency this will store the sum of the complex exponential and the signal
            for (float freq{0.0f}; freq < mFreqRange; freq += mFreqStepSize)
            {
                sum = std::complex<double>(0.0f, 0.0f);
                
                // Loop over all samples and multiply them by their corresponding value in the complex exponential
                for (size_t sample{0zu}; sample < data.size(); sample++)
                {
                    double real = cos(((2 * M_PI) / data.size()) * freq * sample);
                    double imag = sin(((2 * M_PI) / data.size()) * freq * sample);
                    std::complex<double> sample_contribution(real, -imag);

                    std::complex<double> signal(static_cast<double>(data[sample].y), 0.0f);
                    sum += (signal * sample_contribution); 
                }

                float mag = abs(sum);
                result.push_back(DataPoint(freq, mag, 0));
            }


            return result;
        }

    private:
        // Range of frequencies to consider in the Fourier transform.
        // Will compute the FT for 0 - mFreqRange. 
        // For now will come from the number of samples
        float mFreqRange;

        // Step fize of frequencies to compute.
        float mFreqStepSize;
};
