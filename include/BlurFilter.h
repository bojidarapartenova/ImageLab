#include "Image.h"
#include "Filter.h"

class BlurFilter : public Filter
{
public:
    void apply(Image &image) const override;

    String getName() const override;
};