#include "Image.h"

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
    while (!pendingFilters.isEmpty())
    {
        pendingFilters.pop_at(pendingFilters.getSize());
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
