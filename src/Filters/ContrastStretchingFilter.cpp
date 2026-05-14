#include "ContrastStretchingFilter.h"

void ContrastStretching::apply(Image &image) const
{
    int width = image.getWidth();
    int height = image.getHeight();
    int maxVal = image.getMaxVal();

    int minLum = maxVal;
    int maxLum = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Pixel p = image.getPixel(x, y);

            int lum = (int)(0.299 * p.r + 0.587 * p.g + 0.114 * p.b);

            if (lum < minLum)
            {
                minLum = lum;
            }

            if (lum > maxLum)
            {
                maxLum = lum;
            }
        }
    }

    if (maxLum == minLum)
    {
        return;
    }
    double scale = (double)maxVal / (maxLum - minLum);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Pixel p = image.getPixel(x, y);

            int r = (int)((p.r - minLum) * scale);
            int g = (int)((p.g - minLum) * scale);
            int b = (int)((p.b - minLum) * scale);

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

String ContrastStretching::getName() const
{
    return "contrast stretching";
}
