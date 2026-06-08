#include "SobelFilter.h"
#include <cstring>
#include <cmath>
#include <fstream>

SobelFilter::SobelFilter(int thresholdValue)
    : useThreshold(thresholdValue >= 0), thresholdValue(thresholdValue) {}

static void makePBMPath(const char *src, char *dst, size_t dstSize)
{
    size_t len = 0;
    while (src[len] != '\0')
    {
        len++;
    }

    size_t dotPos = len;
    for (size_t i = len; i > 0; i--)
    {
        if (src[i - 1] == '.')
        {
            dotPos = i - 1;
            break;
        }
    }

    size_t i = 0;
    while (i < dotPos && i < dstSize - 20)
    {
        dst[i] = src[i];
        i++;
    }
    const char *suffix = "_sobel_binary.pbm";
    for (size_t j = 0; suffix[j] != '\0' && i < dstSize - 1; j++, i++)
    {
        dst[i] = suffix[j];
    }
    dst[i] = '\0';
}

static void savePBMDirect(const char *path, int width, int height, const Vector<Vector<int>> &bits)
{
    std::ofstream file(path);
    if (!file.is_open())
    {
        return;
    }

    file << "P1\n"
         << width << " " << height << "\n";

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            file << bits[y][x];
            if (x < width - 1)
            {
                file << " ";
            }
        }
        file << "\n";
    }
    file.close();
}

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

    if (useThreshold)
    {
        Vector<Vector<int>> bits;
        for (int y = 0; y < height; y++)
        {
            Vector<int> row;
            for (int x = 0; x < width; x++)
                row.push_back(1);
            bits.push_back(std::move(row));
        }

        for (int y = 1; y < height - 1; ++y)
        {
            for (int x = 1; x < width - 1; ++x)
            {
                double sumX = 0, sumY = 0;
                for (int ky = -1; ky <= 1; ++ky)
                    for (int kx = -1; kx <= 1; ++kx)
                    {
                        int val = grayMap[y + ky][x + kx];
                        sumX += val * Gx[ky + 1][kx + 1];
                        sumY += val * Gy[ky + 1][kx + 1];
                    }

                int magnitude = (int)sqrt(sumX * sumX + sumY * sumY);
                if (magnitude > 255)
                    magnitude = 255;

                bits[y][x] = (magnitude >= thresholdValue) ? 0 : 1;
            }
        }

        char pbmPath[600];
        makePBMPath(image.getPath().getData(), pbmPath, sizeof(pbmPath));
        savePBMDirect(pbmPath, width, height, bits);
        std::cout << "Sobel binary result saved as PBM: " << pbmPath << std::endl;

        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
            {
                int val = (bits[y][x] == 0) ? 255 : 0;
                image.setPixel(x, y, Pixel(val, val, val));
            }
    }
    else
    {
        for (int y = 1; y < height - 1; ++y)
        {
            for (int x = 1; x < width - 1; ++x)
            {
                double sumX = 0, sumY = 0;
                for (int ky = -1; ky <= 1; ++ky)
                    for (int kx = -1; kx <= 1; ++kx)
                    {
                        int val = grayMap[y + ky][x + kx];
                        sumX += val * Gx[ky + 1][kx + 1];
                        sumY += val * Gy[ky + 1][kx + 1];
                    }

                int magnitude = (int)sqrt(sumX * sumX + sumY * sumY);
                if (magnitude > 255)
                    magnitude = 255;

                image.setPixel(x, y, Pixel(magnitude, magnitude, magnitude));
            }
        }
    }
}

String SobelFilter::getName() const
{
    return useThreshold ? String("sobel-threshold") : String("sobel");
}
