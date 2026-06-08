#include "BlurFilter.h"

void BlurFilter::apply(Image &image) const
{
    int width = image.getWidth();
    int height = image.getHeight();
    int maxVal = image.getMaxVal();

    Vector<Vector<Pixel>> copy;
    for (int y = 0; y < height; y++)
    {
        Vector<Pixel> row;
        for (int x = 0; x < width; x++)
        {
            row.push_back(image.getPixel(x, y));
        }
        copy.push_back(row);
    }

    double kernel[3][3] = {
        {0.0625, 0.125, 0.0625},
        {0.125, 0.25, 0.125},
        {0.0625, 0.125, 0.0625}};

    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {
            double redSum = 0, greenSum = 0, blueSum = 0;

            for (int ky = -1; ky <= 1; ky++)
                for (int kx = -1; kx <= 1; kx++)
                {
                    Pixel neighbour = copy[y + ky][x + kx];
                    double weight = kernel[ky + 1][kx + 1];
                    redSum += neighbour.r * weight;
                    greenSum += neighbour.g * weight;
                    blueSum += neighbour.b * weight;
                }

            int r = (int)(redSum + 0.5);
            int g = (int)(greenSum + 0.5);
            int b = (int)(blueSum + 0.5);

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

String BlurFilter::getName() const
{
    return "blur";
}
