#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

template <typename T>
class Vector
{
private:
    T *data;
    size_t size;
    size_t capacity;

    void copyFrom(const Vector<T> &other);
    void moveFrom(Vector<T> &&other);
    void free();
    void resize();

public:
    Vector();
    Vector(const Vector<T> &other);
    Vector(Vector<T> &&other) noexcept;
    Vector &operator=(const Vector<T> &other);
    Vector &operator=(Vector<T> &&other) noexcept;
    ~Vector();

    void push_back(const T &element);
    void push_back(T &&element);
    void pop_at(size_t index);

    T &operator[](size_t index);
    const T &operator[](size_t index) const;

    size_t getSize() const;
    bool isEmpty() const;
};

template <typename T>
inline void Vector<T>::copyFrom(const Vector<T> &other)
{
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];
    for (size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
inline void Vector<T>::moveFrom(Vector<T> &&other)
{
    data = other.data;
    size = other.size;
    capacity = other.capacity;

    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template <typename T>
inline void Vector<T>::free()
{
    delete[] data;
    data = nullptr;
}

template <typename T>
inline void Vector<T>::resize()
{
    size_t newCapacity = (capacity == 0) ? 2 : capacity * 2;
    T *newData = new T[newCapacity];
    for (size_t i = 0; i < size; i++)
    {
        newData[i] = std::move(data[i]);
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template <typename T>
inline Vector<T>::Vector() : data(nullptr), size(0), capacity(0) {}

template <typename T>
inline Vector<T>::Vector(const Vector<T> &other)
{
    copyFrom(other);
}

template <typename T>
inline Vector<T>::Vector(Vector<T> &&other) noexcept
{
    moveFrom(std::move(other));
}

template <typename T>
inline Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
inline Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
inline Vector<T>::~Vector()
{
    free();
}

template <typename T>
inline void Vector<T>::push_back(const T &element)
{
    if (size == capacity)
    {
        resize();
    }
    data[size++] = element;
}

template <typename T>
inline void Vector<T>::push_back(T &&element)
{
    if (size == capacity)
    {
        resize();
    }
    data[size++] = std::move(element);
}

template <typename T>
inline void Vector<T>::pop_at(size_t index)
{
    for (size_t i = index; i < size - 1; i++)
    {
        data[i] = data[i + 1];
    }
    size--;
}

template <typename T>
inline T &Vector<T>::operator[](size_t index)
{
    return data[index];
}

template <typename T>
inline const T &Vector<T>::operator[](size_t index) const
{
    return data[index];
}

template <typename T>
inline size_t Vector<T>::getSize() const
{
    return size;
}

template <typename T>
inline bool Vector<T>::isEmpty() const
{
    return size == 0;
}

#endif