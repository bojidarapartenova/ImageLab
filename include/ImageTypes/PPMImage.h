#ifndef PPMIMAGE_H
#define PPMIMAGE_H

#include "String.h"
#include "Vector.h"
#include "Filter.h"
#include "Image.h"

class PPMImage : public Image
{
protected:
    Vector<Vector<Pixel>> pixels;

public:
    PPMImage(const String &path) : Image(path) {}

    void load() override;
    void save(const String &customPath) const override;
};

#endif