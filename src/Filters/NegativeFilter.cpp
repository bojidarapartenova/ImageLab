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
            Pixel p = image.getPixel(x, y);

            p.r = maxVal - p.r;
            p.g = maxVal - p.g;
            p.b = maxVal - p.b;

            image.setPixel(x, y, p);
        }
    }
}

String NegativeFilter::getName() const
{
    return "negative";
}
