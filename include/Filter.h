#include "String.h"

class Image;

class Filter
{
public:
    virtual ~Filter();

    virtual void apply(const Image &image) const = 0;

    virtual String getName() const = 0;
};