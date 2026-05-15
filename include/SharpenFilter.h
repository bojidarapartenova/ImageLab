#ifndef SHARPENFILTER_H
#define SHARPENFILTER_H

#include "Filter.h"
#include "Image.h"

class SharpenFilter : public Filter
{
    void apply(Image &image) const override;

    String getName() const override;
};

#endif