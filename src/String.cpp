#include "String.h"

void String::copyFrom(const String &other)
{
    size = other.size;
    data = new char[size + 1];
    for (size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
    data[size] = '\0';
}

void String::moveFrom(String &&other)
{
    data = other.data;
    size = other.size;

    other.data = nullptr;
    other.size = 0;
}

void String::free()
{
    delete[] data;
    data = nullptr;
}

String::String(const char *str)
{
    if (!str)
    {
        str = "";
    }

    size_t len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    size = len;

    data = new char[size + 1];
    for (size_t i = 0; i < size; i++)
    {
        data[i] = str[i];
    }
    data[size] = '\0';
}

String::String(const String &other)
{
    copyFrom(other);
}

String::String(String &&other) noexcept
{
    moveFrom(std::move(other));
}

String::~String()
{
    free();
}

String &String::operator=(const String &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

String &String::operator=(String &&other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

bool String::operator==(const String &other) const
{
    if (size != other.size)
    {
        return false;
    }

    for (size_t i = 0; i < size; i++)
    {
        if (data[i] != other.data[i])
        {
            return false;
        }
    }
    return true;
}

bool String::operator==(const char *other) const
{
    if (!other)
    {
        return false;
    }

    size_t i = 0;
    while (other[i] != '\0')
    {
        if (data[i] != other[i])
        {
            return false;
        }
        i++;
    }
    return data[i] == other[i];
}

const char *String::getData() const
{
    return data;
}

size_t String::getSize() const
{
    return size;
}

std::ostream &operator<<(std::ostream &os, const String &str)
{
    os << str.data;
    return os;
}
