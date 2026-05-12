#include "String.h"
#include "Vector.h"
#include "Filter.h"
#include "Image.h"

class PGMImage : public Image
{
protected:
    Vector<Vector<int>> pixels;

public:
    PGMImage(const String &path);

    void load() override;
    void save(const String &path) const override;

    int getPixel(int x, int y) const override;
    void setPixel(int x, int y, int value) override;
    int getMaxVal() const override;
};