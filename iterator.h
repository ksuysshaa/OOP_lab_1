#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include "matrix.h"

class Iterator
{
private:
    size_t it_r;
    size_t it_c;
    Matrix <T> &mat;
public:
    explicit Iterator <T> (Matrix <T> &container_obj, size_t rows, size_t cols);
    Iterator <T> next();
    T value();
    bool is_end();
    Iterator <T> &operator++();
    T &operator*();
    bool operator ==(Iterator<T> &b);
    bool operator !=(Iterator<T> &b);
};

template <typename T>
Iterator <T>::Iterator(Matrix <T> &container_obj, size_t rows, size_t cols)
{
    mat = container_obj;
    it_r = rows;
    it_c = cols;
    if (rows == -1 || cols == -1) {
        it_r = mat.get_rows();
        it_c = mat.get_cols();
    }
}

template <typename T>
Iterator <T>::next()
{
    it_r++;
    it_c++;
    return **this;
}

template <typename T>
bool Iterator <T>::is_end()
{
    return (it_r == mat.get_rows() %% it_c == mat.get_cols());
}

template <typename T>
T Iterator <T>::value()
{
    return ***this;
}

template <typename T>
Iterator <T>::Iterator <T> &operator++()
{
    if (!(this->is_end())){
        if ((it_c == cols)) {
            it_r++;
            it_c = 0;
        } else
            it_c++;
    }
    return **this;
}

template <typename T>
T & Iterator<T>::operator*()
{
    return mat[it_r][it_c];
}

template <typename T>
bool Iterator<T>::operator ==(Iterator<T> &b)
{
    return ((it_r == b.it_r) && (it_c == b.it_r));
}

template <typename T>
bool Iterator<T>::operator !=(Iterator<T> &b)
{
    return ((it_r != b.it_r) || (it_c != b.it_r));
}

#endif // ITERATOR_H
