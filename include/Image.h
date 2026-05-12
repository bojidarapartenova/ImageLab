#include "String.h"
#include "Vector.h"

class Filter;

class Image
{
protected:
    String &path;
    int width;
    int height;
    int maxVal;
    Vector<Filter *> pendingFilters;

public:
    Image(const String &path);
    virtual ~Image();

    virtual void load() = 0;
    virtual void save(const String &path) const = 0;

    void addFilter(Filter *filter);
    void clearFilters();
    void runFilters();
};