#include "PGMImage.h"
#include <fstream>

void PGMImage::load()
{
    std::ifstream file(filePath.getData());
    if (!file.is_open())
    {
        return;
    }

    char buffer[3];
    file >> buffer;

    file >> width >> height >> maxVal;

    for (int y = 0; y < height; y++)
    {
        Vector<int> row;
        for (int x = 0; x < width; x++)
        {
            int pixel;
            file >> pixel;
            row.push_back(pixel);
        }
        pixels.push_back(row);
    }
    file.close();
}

void PGMImage::save(const String &customPath) const
{
    const char *path = (customPath.getSize() > 0) ? customPath.getData() : filePath.getData();

    std::ofstream file(path);
    if (!file.is_open())
    {
        return;
    }

    file << "P2\n";
    file << width << " " << height << "\n";
    file << maxVal << "\n";

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            file << pixels[y][x] << " ";
        }
        file << "\n";
    }
    file.close();
}

Pixel PGMImage::getPixel(int x, int y) const
{
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (x >= width)
        x = width - 1;
    if (y >= height)
        y = height - 1;

    int value = pixels[y][x];
    return Pixel(value, value, value);
}

void PGMImage::setPixel(int x, int y, const Pixel &p)
{
    pixels[y][x] = p.r;
}
