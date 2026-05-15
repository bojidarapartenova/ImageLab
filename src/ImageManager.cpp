#include "ImageManager.h"
#include <cstring>
#include <iostream>

#include "ImageTypes/PPMImage.h"
#include "ImageTypes/PGMImage.h"
#include "ImageTypes/PBMImage.h"

#include "Filters/NegativeFilter.h"
#include "Filters/BlurFilter.h"
#include "Filters/SobelFilter.h"
#include "Filters/SharpenFilter.h"
#include "Filters/ThresholdFilter.h"
#include "Filters/ContrastStretchingFilter.h"

static Image *createImageByExtension(const String &path)
{
    const char *rawPath = path.getData();
    size_t len = 0;

    while (rawPath[len] != '\0')
    {
        len++;
    }

    if (len < 4)
    {
        return nullptr;
    }

    const char *ext = rawPath + (len - 4);

    if (std::strcmp(ext, ".ppm") == 0)
    {
        return new PPMImage(path);
    }
    if (std::strcmp(ext, ".pgm") == 0)
    {
        return new PGMImage(path);
    }
    if (std::strcmp(ext, ".pbm") == 0)
    {
        return new PBMImage(path);
    }

    return nullptr;
}

int ImageManager::findImageIndex(const String &name) const
{
    for (size_t i = 0; i < images.getSize(); i++)
    {
        if (images[i]->getPath() == name)
        {
            return i;
        }
    }
    return -1;
}

Filter *ImageManager::createFilterByName(const String &name) const
{
    if (name == "negative")
    {
        return new NegativeFilter();
    }
    if (name == "blur")
    {
        return new BlurFilter();
    }
    if (name == "sobel")
    {
        return new SobelFilter();
    }
    if (name == "sharpen")
    {
        return new SharpenFilter();
    }
    if (name == "normalize")
    {
        return new ContrastStretchingFilter();
    }

    return nullptr;
}

ImageManager::ImageManager() {}

ImageManager::~ImageManager()
{
    clearAll();
}

void ImageManager::load(const String &path)
{
    Image *newImg = createImageByExtension(path);

    if (!newImg)
    {
        std::cout << "Unsupported file format" << std::endl;
        return;
    }

    try
    {
        newImg->load();
        images.push_back(newImg);
        std::cout << "Loaded: " << path << " (" << newImg->getWidth() << "x" << newImg->getHeight() << ")" << std::endl;
    }
    catch (...)
    {
        delete newImg;
        std::cout << "Error: Image '" << path << "' not loaded." << std::endl;
        return;
    }
}