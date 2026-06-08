#pragma once

#include "Filter.h"
#include "Image.h"

class ThresholdFilter : public Filter
{
private:
    double threshold;

public:
    ThresholdFilter(double threshold);

    void apply(Image &image) const override;

    String getName() const override;
};