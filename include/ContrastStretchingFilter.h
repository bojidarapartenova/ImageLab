#pragma once

#include "Filter.h"
#include "Image.h"

class ContrastStretchingFilter : public Filter
{
    void apply(Image &image) const override;

    String getName() const override;
};