#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include "Structures/Vector.h"
#include "Structures/String.h"
#include "Image.h"

class ImageManager
{
private:
    Vector<Image *> images;

    int findImageIndex(const String &name) const;
    Filter *createFilterByName(const String &name) const;

public:
    ImageManager();
    ~ImageManager();

    void load(const String &path);
    void addFilter(const String &imageName, const String &filterType);
    void removeFilter(const String &imageName, int filterIdx);
    void showFilters(const String &imageName) const;
    void showAllFilters() const;
    void run(const String &imageName);
    void runAll();
    void save(const String &imageName, const String &outputName = "");
    void clearAll();
};

#endif