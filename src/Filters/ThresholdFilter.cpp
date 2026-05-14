#include "ThresholdFilter.h"

ThresholdFilter::ThresholdFilter(double threshold) : threshold(threshold) {}

void ThresholdFilter::apply(Image &image) const
{
    int width = image.getWidth();
    int height = image.getHeight();
    int maxVal = image.getMaxVal();

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Pixel p = image.getPixel(x, y);

            double avg = (p.r + p.g + p.b) / 3;

            if (avg < threshold)
            {
                image.setPixel(x, y, Pixel(0, 0, 0));
            }
            else
            {
                image.setPixel(x, y, Pixel(maxVal, maxVal, maxVal));
            }
        }
    }
}

String ThresholdFilter::getName() const
{
    return "threshold";
}
