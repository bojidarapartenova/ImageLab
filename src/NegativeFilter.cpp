#include "NegativeFilter.h"

void NegativeFilter::apply(Image &image) const
{
    int width = image.getWidth();
    int height = image.getHeight();
    int maxVal = image.getMaxVal();

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Pixel p = image.getPixel(x, y);

            // 1. ЗАСТРАХОВКА ЗА PBM (Черно-бяла):
            // Ако пикселите са само 0 и 1, а maxVal е останал 255 по подразбиране
            if (maxVal == 255 && (p.r == 0 || p.r == 1) && (p.g == 0 || p.g == 1) && (p.b == 0 || p.b == 1))
            {
                p.r = 1 - p.r;
                p.g = 1 - p.g;
                p.b = 1 - p.b;
            }
            // 2. ЗАСТРАХОВКА ЗА PGM и PPM (Сива и Цветна)
            else
            {
                p.r = maxVal - p.r;
                p.g = maxVal - p.g;
                p.b = maxVal - p.b;
            }

            image.setPixel(x, y, p);
        }
    }
}

String NegativeFilter::getName() const
{
    return "negative";
}
