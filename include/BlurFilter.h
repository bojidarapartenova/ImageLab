#ifndef BLURFILTER_H
#define BLURFILTER_H

#include "Filter.h"
#include "Image.h"

class BlurFilter : public Filter
{
public:
    void apply(Image &image) const override;

    String getName() const override;
};

#endif