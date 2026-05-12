#include "Image.h"

void Image::runFilters()
{
    for (size_t i = 0; i < pendingFilters.getSize(); i++)
    {
        pendingFilters[i]->apply(*this);
    }

    clearFilters();
}
