#include "SharpenFilter.h"

void SharpenFilter::apply(Image &image) const
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
            Pixel p = image.getPixel(x, y);
            row.push_back(p);
        }
        copy.push_back(std::move(row));
    }

    double kernel[3][3] = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}};

    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {
            double redSum = 0, greenSum = 0, blueSum = 0;
            for (int ky = -1; ky <= 1; ky++)
            {
                for (int kx = -1; kx <= 1; kx++)
                {
                    Pixel neighbour = copy[y + ky][x + kx];
                    double weight = kernel[ky + 1][kx + 1];

                    redSum += neighbour.r * weight;
                    greenSum += neighbour.g * weight;
                    blueSum += neighbour.b * weight;
                }
            }
            int r = (int)redSum;
            int g = (int)greenSum;
            int b = (int)blueSum;

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
        }
    }
}

String SharpenFilter::getName() const
{
    return "sharpen";
}
