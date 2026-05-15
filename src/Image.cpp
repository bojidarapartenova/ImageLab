#include "Image.h"
#include "Filter.h"

Image::Image(const String &path) : filePath(path), width(0), height(0), maxVal(255)
{
}

void Image::addFilter(Filter *filter)
{
    if (filter)
    {
        pendingFilters.push_back(filter);
    }
}

void Image::clearFilters()
{
    for (size_t i = 0; i < pendingFilters.getSize(); i++)
    {
        delete pendingFilters[i];
    }

    while (!pendingFilters.isEmpty())
    {
        pendingFilters.pop_at(0);
    }
}

void Image::runFilters()
{
    for (size_t i = 0; i < pendingFilters.getSize(); i++)
    {
        pendingFilters[i]->apply(*this);
    }

    clearFilters();
}

int Image::getWidth() const
{
    return width;
}

int Image::getHeight() const
{
    return height;
}

int Image::getMaxVal() const
{
    return maxVal;
}

String Image::getPath() const
{
    return filePath;
}
