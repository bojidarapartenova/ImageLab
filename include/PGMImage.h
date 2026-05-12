#include "String.h"
#include "Vector.h"
#include "Filter.h"
#include "Image.h"

class PGMImage : public Image
{
protected:
    Vector<Vector<int>> pixels;

public:
    PGMImage(const String &path) : Image(path) {}

    void load() override;
    void save(const String &customPath) const override;
};