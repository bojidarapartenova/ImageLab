#ifndef CONTRASTSTRETCHINGFILTER_H
#define CONTRASTSTRETCHINGFILTER_H

#include "String.h"
#include "Vector.h"
#include "Filter.h"
#include "Image.h"

class ContrastStretchingFilter : public Filter
{
    void apply(Image &image) const override;

    String getName() const override;
};

#endif