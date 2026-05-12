#include "Image.h"
#include "Filter.h"

class NegativeFilter : public Filter
{
public:
    void apply(Image &image) const override;

    String getName() const override;
};
