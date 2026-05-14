#include "String.h"
#include "Vector.h"
#include "Image.h"
#include "Filter.h"

class ThresholdFilter : public Filter
{
private:
    double threshold;

public:
    ThresholdFilter(double threshold);

    void apply(Image &image) const override;

    String getName() const override;
};