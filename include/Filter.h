#pragma once

#include "MyString.h"

class Image;

class Filter
{
public:
    virtual void apply(Image &image) const = 0;
    virtual String getName() const = 0;
    virtual ~Filter() = default;
};