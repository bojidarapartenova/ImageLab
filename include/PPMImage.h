#pragma once

#include "Image.h"

class PPMImage : public Image
{
protected:
    Vector<Vector<Pixel>> pixels;

public:
    PPMImage(const String &path) : Image(path) {}

    void load() override;
    void save(const String &customPath) const override;

    virtual Pixel getPixel(int x, int y) const override;
    virtual void setPixel(int x, int y, const Pixel &p) override;
};