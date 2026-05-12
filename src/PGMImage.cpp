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
    const char *path = (customPath.getData() > 0) ? customPath.getData() : filePath.getData();

    std::ofstream file(path);
    if (!file.is_open())
    {
        return;
    }

    file << "P2" << "\n";
    file << width << " " << height << "\n";
    file << maxVal << "\n";

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            file << pixels[y][x];

            if (x < width - 1)
            {
                file << "";
            }
        }
        file << "\n";
    }
    file.close();
}

int PGMImage::getPixel(int x, int y) const
{
    return pixels[y][x];
}

void PGMImage::setPixel(int x, int y, int value)
{
    pixels[y][x] = value;
}

int PGMImage::getMaxVal() const
{
    return maxVal;
}
