#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include "Structures/Vector.h"
#include "Structures/String.h"
#include "Image.h"

class ImageManager
{
private:
    Vector<Image *> images;

public:
    ImageManager();
    ~ImageManager();

    void load(const String &path);
    void addFilter(int imageIndex, const String &filter);
    void removeFilter(int imageIndex, int filterIndex);
    void showFilters(int imageIndex) const;
    void showAllFilters() const;
    void run(int imageIndex);
    void runAll();
    void save(int imageIndex, const String &outputName = "");
    void quit() const;
};

#endif