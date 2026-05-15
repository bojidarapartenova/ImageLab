#ifndef NEGATIVEFILTER_H
#define NEGATIVEFILTER_H

#include "Filter.h"
#include "Image.h"

class NegativeFilter : public Filter
{
public:
    void apply(Image &image) const override;

    String getName() const override;
};

#endif
