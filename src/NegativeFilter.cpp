#include "NegativeFilter.h"

void NegativeFilter::apply(Image &image) const
{
    int width = image.getWidth();
    int height = image.getHeight();
    int maxVal = image.getMaxVal();

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int currentPixel = image.getPixel(x, y);
            image.setPixel(x, y, maxVal - currentPixel);
        }
    }
}

String NegativeFilter::getName() const
{
    return "negative";
}
