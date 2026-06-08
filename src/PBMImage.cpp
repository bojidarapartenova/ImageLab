#include "PBMImage.h"
#include <fstream>

PBMImage::PBMImage(const String &path) : Image(path)
{
    maxVal = 1;
}

void PBMImage::load()
{
    std::ifstream file(filePath.getData());
    if (!file.is_open())
    {
        return;
    }

    char buffer[3];
    file >> buffer;

    file >> width >> height;
    for (int y = 0; y < height; y++)
    {
        Vector<int> row;
        for (int x = 0; x < width; x++)
        {
            int bit;
            file >> bit;
            row.push_back(bit);
        }
        pixels.push_back(row);
    }
}

void PBMImage::save(const String &customPath) const
{
    const char *path = (customPath.getSize() > 0) ? customPath.getData() : filePath.getData();

    std::ofstream file(path);
    if (!file.is_open())
    {
        return;
    }

    file << "P1\n";
    file << width << " " << height << "\n";

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Твърдо печатаме бита последван от интервал!
            file << pixels[y][x] << " ";
        }
        file << "\n";
    }
    file.close();
}

Pixel PBMImage::getPixel(int x, int y) const
{
    int value = pixels[y][x] * 255;
    return Pixel(value, value, value);
}

void PBMImage::setPixel(int x, int y, const Pixel &p)
{
    if (p.r == 0 || p.r == 254)
    {
        pixels[y][x] = 0;
    }
    else
    {
        pixels[y][x] = 1;
    }
}
