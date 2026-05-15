#ifndef PGMIMAGE_H
#define PGMIMAGE_H

#include "String.h"
#include "Vector.h"
#include "Filter.h"
#include "Image.h"

class PGMImage : public Image
{
protected:
    Vector<Vector<int>> pixels;

public:
    PGMImage(const String &path) : Image(path) {}

    void load() override;
    void save(const String &customPath) const override;

    Pixel getPixel(int x, int y) const override;
    void setPixel(int x, int y, const Pixel &p) override;
};

#endif