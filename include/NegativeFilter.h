#include "Image.h"
#include "Filter.h"

class NegativeFilter : public Filter
{
public:
    void apply(Image &image) const override
    {
        int width = image.getWidth();
        int height = image.getHeight();
        int maxVal = image.getMaxVal();

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int currentPixel = image.getPixel(x, y);
                image.setPixel(x, y, maxVal - currentPixel);
            }
        }
    }

    String getName() const override
    {
        return "negative";
    }
};
