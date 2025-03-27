// CurrentMonitor.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Implement a simple Run Length Encoder, shortening sequences of the same characters. For example, ten As would be encoded as A10.

#include <iostream>
using namespace std;

class CurrentMonitor 
{
public:
    CurrentMonitor(const double& sampleRate, const double& sampleTimeWindow) :
        timeWindow(sampleTimeWindow),
        SampleRateHZ(1/sampleRate), 
        BufferSize(round(timeWindow /sampleRate)),
        samples(new float[BufferSize])
    {}
    CurrentMonitor() : CurrentMonitor(0.002, 2.0) {} // our default
    ~CurrentMonitor() 
    {
        if (samples)
        {
            delete[] samples;
            samples = nullptr;
        }
    }

    void register_sample_from_isr(const float& cur)
    {
        // input validation here
        if (cur < -1000.00f || cur > 1000.00f) return;

        auto old_cur = 0.00f;
        if (IsFull)
            old_cur = samples[head];

        samples[head] = cur;

        // if buffer is full, we should subtract the old value that is overwritten from 
        // the running sum
        running_sum = running_sum + cur - old_cur;

        head = (head + 1) % BufferSize;

        if (!IsFull && head == 0)
        {
            IsFull = true;
        }
    }

    float average_over_last(float t)
    {
        if (t <= 0.0f) return 0.0f;
        if (t > timeWindow) t = timeWindow;

        // Calaculate how many samples we need to consider
        uint32_t required_samples = t * SampleRateHZ;
        uint32_t available_samples = IsFull ? BufferSize : head;
        uint32_t sample_to_get = min(required_samples, available_samples);

        // if we have no data in the buffer
        if (sample_to_get == 0) return 0.0f;

        // if we are using what is available
        if (sample_to_get == available_samples)
            return running_sum / sample_to_get;

        // otherwise, calculate the average for a specific window
        float sum = 0.00f;
        
        uint32_t index = (head - sample_to_get + BufferSize) % BufferSize;

        for (uint32_t i = 0; i < sample_to_get; ++i)
        {
            sum += samples[index];
            index = (index + 1) % BufferSize;
        }
        return sum / (float)sample_to_get;
    }



private:
    float timeWindow;
    float SampleRateHZ;
    int BufferSize;
    float* samples = nullptr;
    bool IsFull = false;
    uint32_t head = 0;
    double running_sum = 0.0f;

};

int main()
{
    CurrentMonitor cm(0.002, 0.01); // creating for 5 buffer size
    cm.register_sample_from_isr(2.00);
    cm.register_sample_from_isr(1.00); 
    cm.register_sample_from_isr(1.00);
    cm.register_sample_from_isr(1.00);
    cm.register_sample_from_isr(1.00);
    cout << "average sum: " << cm.average_over_last(0.005) << endl;

    cm.register_sample_from_isr(3.00);
    cout << "average sum: " << cm.average_over_last(0.005) << endl;

}
