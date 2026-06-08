#pragma once

#include "Vector.hpp"
#include "MyString.h"
#include "Image.h"

class ImageManager
{
private:
    Vector<Image *> images;

    int findImageIndex(const String &name) const;
    Filter *createFilterByName(const String &name, int sobelThreshold = -1) const;

public:
    ImageManager();
    ~ImageManager();

    void load(const String &path);
    void addFilter(const String &imageName, const String &filterType, int sobelThreshold = -1);
    void removeFilter(const String &imageName, int filterIdx);
    void showFilters(const String &imageName) const;
    void showAllFilters() const;
    void run(const String &imageName);
    void runAll();
    void save(const String &imageName, const String &outputName = "");
    void clearAll();
};
