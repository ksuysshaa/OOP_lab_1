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
    Matrix(const Matrix<T>& mat);
    explicit Matrix(std::initializer_list < std::initializer_list < T >> lst);

    int get_rows() const;
    int get_cols() const;
    void set_elem(unsigned int i, unsigned j, const T& elem);

    bool is_square();

    T& operator ()(unsigned int i, unsigned int j);


    template <typename _T>
    friend std::ostream& operator <<(std::ostream& os, const Matrix<_T>& mat);
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
        throw Exceptions ("memory allocation error.");
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
Matrix <T>::Matrix(const Matrix<T>& mat)
{
    rows = get_rows();
    cols = get_cols();
    if (rows == 0 || cols == 0)
        throw Exceptions ("memory allocation error.");
    alloc_memory();
    for (int i = 0; i<rows; i++)
    {
        for (int j = 0; j<cols; j++)
            data[i][j] = mat.data[i][j];
    }
}

template <typename T>
Matrix <T>::Matrix(std::initializer_list<std::initializer_list< T>> lst)
{
    int ind_i = 0;
    int ind_j = 0;
    rows = lst.size();
    cols = 3;
    alloc_memory();
    for (auto i : lst) {
        ind_j = 0;
        for (auto j : i) {           
            data[ind_i][ind_j] = j;
            ind_j++;
        }
        ind_i++;
    }
}

template <typename T>
Matrix <T>::~Matrix()
{
    for (int i = 0; i< rows; i++)
        delete[] data[i];
    delete[] data;
}

template <typename T>
int Matrix <T>::get_cols() const
{
    return cols;
}

template <typename T>
int Matrix <T>::get_rows() const
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

template <typename _T>
std::ostream& operator <<(std::ostream& os, const Matrix<_T>& mat)
{
    //проверка на 0
    for (int i = 0; i<2; i++)
    {
        os << "\n";
        for (int j = 0; j<3; j++)
            os << mat.data[i][j] << " ";
    }
    os << "\n";
    return os;
}

template <typename T>
void Matrix <T>::set_elem(unsigned int i, unsigned j, const T& elem)
{
    data[i][j] = elem;
}

template <typename T>
T& Matrix <T>::operator ()(unsigned int i, unsigned int j)
{
    if (i < 0 || i >= rows || j < 0 || j >= cols)
        throw Exceptions ("incorrect index");
    return data[i][j];
}

#endif // MATRIX_H
