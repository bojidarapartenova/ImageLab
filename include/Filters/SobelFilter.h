#ifndef SOBELFILTER_H
#define SOBELFILTER_H

#include "String.h"
#include "Vector.h"
#include "Image.h"
#include "Filter.h"

class SobelFilter : public Filter
{
private:
    bool useThreshold;
    int thresholdValue;

public:
    SobelFilter(int thresholdValue = -1);

    void apply(Image &image) const override;

    String getName() const override;
};

#endif