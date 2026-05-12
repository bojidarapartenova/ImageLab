#include "BlurFilter.h"

void BlurFilter::apply(Image &image) const
{
    int width = image.getWidth();
    int height = image.getHeight();

    Vector<Vector<Pixel>> copy;
    for (int y = 0; y < width; y++)
    {
        Vector<Pixel> row;
        for (int x = 0; x < height; x++)
        {
            Pixel p = image.getPixel(x, y);
            row.push_back(p);
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

            image.setPixel(x, y, Pixel((int)redSum, (int)greenSum, (int)blueSum));
        }
    }
}

String BlurFilter::getName() const
{
    return "blur";
}
