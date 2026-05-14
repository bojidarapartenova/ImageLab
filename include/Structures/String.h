#include <iostream>

class String
{
private:
    char *data;
    size_t size;

    void copyFrom(const String &other);
    void moveFrom(String &&other);
    void free();

public:
    String(const char *str = "");
    String(const String &other);
    String(String &&other) noexcept;
    ~String();

    String &operator=(const String &other);
    String &operator=(String &&other) noexcept;

    bool operator==(const String &other) const;
    bool operator==(const char *other) const;

    const char *getData() const;
    size_t getSize() const;

    friend std::ostream &operator<<(std::ostream &os, const String &str);
};
