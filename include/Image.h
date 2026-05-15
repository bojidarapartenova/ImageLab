#ifndef IMAGE_H
#define IMAGE_H

#include "Structures/String.h"
#include "Structures/Vector.h"

class Filter;

struct Pixel
{
    int r, g, b;
    Pixel(int r = 0, int g = 0, int b = 0) : r(r), g(g), b(b) {}
};

class Image
{
protected:
    String filePath;
    int width;
    int height;
    int maxVal;
    Vector<Filter *> pendingFilters;

public:
    Image(const String &path);
    virtual ~Image() = default;

    virtual void load() = 0;
    virtual void save(const String &path) const = 0;

    void addFilter(Filter *filter);
    void clearFilters();
    void runFilters();

    int getWidth() const;
    int getHeight() const;
    int getMaxVal() const;

    virtual Pixel getPixel(int x, int y) const = 0;
    virtual void setPixel(int x, int y, const Pixel &p) = 0;
};

#endif