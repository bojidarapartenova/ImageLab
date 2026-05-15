#ifndef PBMIMAGE_H
#define PBMIMAGE_H

#include "Image.h"

class PBMImage : public Image
{
protected:
    Vector<Vector<int>> pixels;

public:
    PBMImage(const String &path);

    void load() override;
    void save(const String &customPath) const override;

    Pixel getPixel(int x, int y) const override;
    void setPixel(int x, int y, const Pixel &p) override;
};

#endif