#include "ContrastStretchingFilter.h"

void ContrastStretchingFilter::apply(Image &image) const
{
    int width = image.getWidth();
    int height = image.getHeight();
    int maxVal = image.getMaxVal();

    int minR = maxVal, maxR = 0;
    int minG = maxVal, maxG = 0;
    int minB = maxVal, maxB = 0;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Pixel p = image.getPixel(x, y);
            if (p.r < minR)
            {
                minR = p.r;
            }
            if (p.r > maxR)
            {
                maxR = p.r;
            }
            if (p.g < minG)
            {
                minG = p.g;
            }
            if (p.g > maxG)
            {
                maxG = p.g;
            }
            if (p.b < minB)
            {
                minB = p.b;
            }
            if (p.b > maxB)
            {
                maxB = p.b;
            }
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Pixel p = image.getPixel(x, y);

            int r = (maxR != minR) ? (int)((double)(p.r - minR) / (maxR - minR) * maxVal + 0.5) : p.r;
            int g = (maxG != minG) ? (int)((double)(p.g - minG) / (maxG - minG) * maxVal + 0.5) : p.g;
            int b = (maxB != minB) ? (int)((double)(p.b - minB) / (maxB - minB) * maxVal + 0.5) : p.b;

            if (r < 0)
            {
                r = 0;
            }
            if (r > maxVal)
            {
                r = maxVal;
            }
            if (g < 0)
            {
                g = 0;
            }
            if (g > maxVal)
            {
                g = maxVal;
            }
            if (b < 0)
            {
                b = 0;
            }
            if (b > maxVal)
            {
                b = maxVal;
            }

            image.setPixel(x, y, Pixel(r, g, b));
        }
    }
}

String ContrastStretchingFilter::getName() const
{
    return "normalize";
}
