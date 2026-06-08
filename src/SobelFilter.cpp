#include "SobelFilter.h"

SobelFilter::SobelFilter(int thresholdValue) : useThreshold(thresholdValue >= 0), thresholdValue(thresholdValue) {}

void SobelFilter::apply(Image &image) const
{
    int width = image.getWidth();
    int height = image.getHeight();

    Vector<Vector<int>> grayMap;
    for (int y = 0; y < height; y++)
    {
        Vector<int> row;
        for (int x = 0; x < width; x++)
        {
            Pixel p = image.getPixel(x, y);
            int maxVal = image.getMaxVal();
            int r = (maxVal > 0) ? (p.r * 255 / maxVal) : p.r;
            int g = (maxVal > 0) ? (p.g * 255 / maxVal) : p.g;
            int b = (maxVal > 0) ? (p.b * 255 / maxVal) : p.b;
            row.push_back((int)(0.299 * r + 0.587 * g + 0.114 * b));
        }
        grayMap.push_back(std::move(row));
    }

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int y = 1; y < height - 1; ++y)
    {
        for (int x = 1; x < width - 1; ++x)
        {
            double sumX = 0;
            double sumY = 0;

            for (int ky = -1; ky <= 1; ++ky)
            {
                for (int kx = -1; kx <= 1; ++kx)
                {
                    int val = grayMap[y + ky][x + kx];
                    sumX += val * Gx[ky + 1][kx + 1];
                    sumY += val * Gy[ky + 1][kx + 1];
                }
            }

            int magnitude = (int)sqrt(sumX * sumX + sumY * sumY);
            if (magnitude > 255)
            {
                magnitude = 255;
            }

            if (useThreshold)
            {
                int bit = (magnitude >= thresholdValue) ? 255 : 0;
                image.setPixel(x, y, Pixel(bit, bit, bit));
            }
            else
            {
                image.setPixel(x, y, Pixel(magnitude, magnitude, magnitude));
            }
        }
    }
}

String SobelFilter::getName() const
{
    return "sobel";
}
