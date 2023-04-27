#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "exceptions.h"

template <typename T>
class Iterator;

template <typename T>
class Matrix
{
private:
    size_t rows;
    size_t cols;
    T **data;
    void alloc_memory();
public:
    explicit Matrix(int n, int m);
    ~Matrix();

    size_t get_rows() const;
    size_t get_cols() const;

    bool is_square();
};

template <typename T>
void Matrix <T>::alloc_memory()
{
    try
    {
        data = new T* [rows];
        for (int i = 0; i < rows; i++)
            data[i] = new T [cols];
    }
    catch (std::bad_alloc &ex)
    {
        throw Exceptions("memory allocation error.");
        if (data != NULL)
            delete[] data;
    }
}

template <typename T>
Matrix <T>::Matrix (int n, int m)
{
    if (n < 0 || m < 0)
        throw Exceptions ("incorrect size.");
    rows = (size_t) n;
    cols = (size_t) m;
    alloc_memory();
}

template <typename T>
Matrix <T>::~Matrix()
{
    for (int i = 0; i< rows; i++)
        delete[] data[i];
    delete[] data;
}

template <typename T>
size_t Matrix <T>::get_cols() const
{
    return cols;
}

template <typename T>
size_t Matrix <T>::get_rows() const
{
    return rows;
}

template <typename T>
bool Matrix <T>::is_square()
{
    bool result;
    if (rows == cols)
        result = true;
    return result;
}


#endif // MATRIX_H
