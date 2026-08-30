#pragma once

#include "Globals.h"
#include "Transform.h"

#include <cstddef>
#include <vector>
#include <complex>

class FourierTransform : public Transform
{

    public:
        FourierTransform(float freq_step_size)
            :mFreqStepSize(freq_step_size)
        { }

        std::vector<DataPoint> Apply(const std::vector<DataPoint>& data)
        {
            mFreqRange = static_cast<float>(data.size());
            printf("Calculating Fourier Transform for frequencies %f - %f\n", 0.0f, mFreqRange);

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

                    sum += static_cast<double>(data[sample].y) * sample_contribution; 
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
