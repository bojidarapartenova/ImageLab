#include "ImageManager.h"
#include <cstring>
#include <iostream>

#include "PPMImage.h"
#include "PGMImage.h"
#include "PBMImage.h"

#include "NegativeFilter.h"
#include "BlurFilter.h"
#include "SobelFilter.h"
#include "SharpenFilter.h"
#include "ThresholdFilter.h"
#include "ContrastStretchingFilter.h"

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
    if (name == "threshold")
    {
        return new ThresholdFilter(150);
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

void ImageManager::addFilter(const String &imageName, const String &filterType, int sobelThreshold)
{
    int idx = findImageIndex(imageName);
    if (idx == -1)
    {
        std::cout << "Error: Image '" << imageName << "' not loaded." << std::endl;
        return;
    }

    Filter *f = createFilterByName(filterType);
    if (f)
    {
        images[idx]->addFilter(f);
        std::cout << "Added filter '" << filterType << "' to '" << imageName
                  << "' (index " << images[idx]->getPendingFiltersCount() - 1 << ")" << std::endl;
    }
    else
    {
        std::cout << "Error: Unknown filter '" << filterType << "'" << std::endl;
    }
}

void ImageManager::removeFilter(const String &imageName, int filterIdx)
{
    int idx = findImageIndex(imageName);

    if (idx != -1 && images[idx]->removeFilterAt(filterIdx))
    {
        std::cout << "Removed filter " << filterIdx << " from " << imageName << std::endl;
    }
    else
    {
        std::cout << "Error: Could not remove filter." << std::endl;
    }
}

void ImageManager::showFilters(const String &imageName) const
{
    int idx = findImageIndex(imageName);
    if (idx != -1)
    {
        std::cout << "Filters for " << imageName << ": ";
        images[idx]->printFilters();
        std::cout << std::endl;
    }
}

void ImageManager::showAllFilters() const
{
    for (size_t i = 0; i < images.getSize(); i++)
    {
        std::cout << "Filters for " << images[i]->getPath() << ": ";
        images[i]->printFilters();
        std::cout << std::endl;
    }
}

void ImageManager::run(const String &imageName)
{
    int idx = findImageIndex(imageName);
    if (idx != -1)
    {
        std::cout << "Running filters for " << imageName << "..." << std::endl;
        images[idx]->runFilters();
        images[idx]->save(imageName);
    }
}

void ImageManager::runAll()
{
    std::cout << "Running pipeline for all " << images.getSize() << " image(s)..." << std::endl;
    for (size_t i = 0; i < images.getSize(); i++)
    {
        std::cout << images[i]->getPath() << std::endl;
        images[i]->runFilters();
        images[i]->save(images[i]->getPath());
    }
}

void ImageManager::save(const String &imageName, const String &outputName)
{
    int idx = findImageIndex(imageName);
    if (idx != -1)
    {
        images[idx]->runFilters();
        String path = (outputName == "") ? imageName : outputName;
        images[idx]->save(path);
        std::cout << "Saved: " << path << std::endl;
    }
}

void ImageManager::clearAll()
{
    for (size_t i = 0; i < images.getSize(); i++)
    {
        delete images[i];
    }
}
