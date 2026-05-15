#include "PPMImage.h"
#include <fstream>

void PPMImage::load()
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
        Vector<Pixel> row;
        for (int x = 0; x < width; x++)
        {
            int r, g, b;
            file >> r >> g >> b;
            row.push_back(Pixel(r, g, b));
        }
        pixels.push_back(row);
    }
    file.close();
}

void PPMImage::save(const String &customPath) const
{
    const char *path = (customPath.getSize() > 0) ? customPath.getData() : filePath.getData();

    std::ofstream file(path);
    if (!file.is_open())
    {
        return;
    }

    file << "P3" << "\n";
    file << width << " " << height << "\n";
    file << maxVal << "\n";

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            const Pixel &p = pixels[y][x];
            file << p.r << " " << p.g << " " << p.b;

            if (x < width - 1)
            {
                file << " ";
            }
        }
        file << "\n";
    }
    file.close();
}

Pixel PPMImage::getPixel(int x, int y) const
{
    return pixels[y][x];
}

void PPMImage::setPixel(int x, int y, const Pixel &p)
{
    pixels[y][x] = p;
}
