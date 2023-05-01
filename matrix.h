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
    Matrix();
    ~Matrix();
    Matrix(const Matrix<T>& mat);
    Matrix (Matrix<T>&& mat);
    explicit Matrix(std::initializer_list < std::initializer_list < T >> lst);

    int get_rows() const;
    int get_cols() const;

    bool is_square();

    void set_elem(unsigned int i, unsigned j, const T& elem);
    T& operator () (unsigned int i, unsigned int j);
    T& get_elem (unsigned int i, unsigned int j);

    Matrix<T>& operator = (const Matrix<T>&mat);
    Matrix<T>& operator +=(const Matrix<T>&mat);
    Matrix<T>& operator -=(const Matrix<T>&mat);

    Matrix<T> operator +(const Matrix<T>& mat);
    Matrix<T> operator -(const Matrix<T>& mat);
    Matrix<T> operator *(const Matrix<T>& mat);

    Matrix<T> operator +(double num);
    Matrix<T> operator -(double num);
    Matrix<T> operator *(double num);
    Matrix<T> operator /(double num);

    template <typename _T>
    friend std::ostream& operator <<(std::ostream& os, const Matrix<_T>& mat);

    Iterator<T> iterator_begin() {return Iterator<T>(*this, 0, 0);};
    Iterator<T> iterator_end() {return Iterator<T>(*this, get_rows(), get_cols());};
};

template <typename T> //выделение памяти - вспомогательная функция
void Matrix <T>::alloc_memory()
{
    try {
        data = new T* [rows];
        for (int i = 0; i < rows; i++)
            data[i] = new T [cols];
    }
    catch (std::bad_alloc &ex) {
        throw Exceptions ("memory allocation error.");
        if (data != NULL)
            delete[] data;
    }
}

template <typename T> //конструктор длины
Matrix <T>::Matrix (int n, int m)
{
    if (n < 0 || m < 0)
        throw Exceptions ("incorrect size.");
    rows = (size_t) n;
    cols = (size_t) m;
    alloc_memory();
}

template <typename T>
Matrix <T>::Matrix(const Matrix<T>& mat) //конструктор копирования
{
    rows = mat.get_rows();
    cols = mat.get_cols();
    if (rows == 0 || cols == 0)
        throw Exceptions ("memory allocation error.");
    alloc_memory();
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++)
            data[i][j] = mat.data[i][j];
    }
}

template <typename T> //конструктор перемещения
Matrix <T>::Matrix(Matrix<T>&& mat)
{
    rows = mat.rows;
    cols = mat.cols;
    data = mat.data;
    mat.data = nullptr;
}

template <typename T>
Matrix <T>::Matrix(std::initializer_list<std::initializer_list< T>> lst) //конструктор со списком инициализации
{
    int ind_i = 0, ind_j = 0;
    rows = lst.size();
    cols = 0;
    for (auto i : lst) {
        for (auto j : i)
            cols++;
        break;
    }
    if (rows == 0 || cols == 0)
        throw Exceptions ("incorrect initializer list.");
    else {
        alloc_memory();
        for (auto i : lst) {
            ind_j = 0;
            for (auto j : i) {
                set_elem(ind_i, ind_j, j);
                ind_j++;
            }
            ind_i++;
        }
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
    if (mat.get_rows() == 0 || mat.get_cols() == 0)
        throw Exceptions ("matrix is null.");
    for (int i = 0; i<mat.get_rows(); i++) {
        os << "\n";
        for (int j = 0; j<mat.get_cols(); j++)
            os << mat.data[i][j] << " ";
    }
    os << "\n";
    return os;
}

template <typename T>
void Matrix <T>::set_elem (unsigned int i, unsigned j, const T& elem)
{
    if (i < 0 || i >= get_rows() || j < 0 || j >= get_cols())
        throw Exceptions ("incorrect index");
    data[i][j] = elem;
}

template <typename T>
T& Matrix <T>::operator () (unsigned int i, unsigned int j)
{
    if (i < 0 || i > get_rows() || j < 0 || j > get_cols())
        throw Exceptions ("incorrect index");
    return data[i][j];
}

template <typename T>
T& Matrix <T>::get_elem (unsigned int i, unsigned int j)
{
    if (i < 0 || i > get_rows() || j < 0 || j > get_cols())
        throw Exceptions ("incorrect index");
    return data[i][j];
}

template <typename T>
Matrix<T>& Matrix <T>::operator = (const Matrix<T>& mat) //перегрузка оператора присваивания
{
    if (rows != mat.get_rows() || cols != mat.get_cols())
        throw Exceptions ("different size of matrix.");
    alloc_memory();
    for (int i = 0; i<rows; i++)
        for (int j = 0; j<cols; j++)
            data[i][j] = mat.data[i][j];
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator +=(const Matrix<T>&mat)
{
    if (rows != mat.get_rows() || cols != mat.get_cols())
        throw Exceptions ("different size of matrix.");
    for (int i = 0; i<rows; i++)
        for (int j = 0; j<cols; j++)
            data[i][j] += mat.data[i][j];
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator -= (const Matrix<T> &mat)
{
    if (rows != mat.get_rows() || cols != mat.get_cols())
        throw Exceptions ("different size of matrix.");
    for (int i = 0; i<rows; i++)
        for (int j = 0; j<cols; j++)
            data[i][j] -= mat.data[i][j];
    return *this;
}

template<typename T>
Matrix<T> Matrix <T>::operator +(const Matrix<T>& mat)
{
    Matrix <T> new_mat(*this);
    new_mat += mat;
    return new_mat;
}

template<typename T>
Matrix<T> Matrix <T>::operator -(const Matrix<T>& mat)
{
    Matrix <T> new_mat(*this);
    new_mat -= mat;
    return new_mat;
}

template<typename T>
Matrix<T> Matrix <T>::operator *(const Matrix<T>& mat)
{
    Matrix <T> new_mat(*this);
    for (int i = 0; i<mat.get_rows(); i++)
        for (int j = 0; j<mat.get_cols(); j++)
            new_mat.data[i][j] *= mat.data[i][j];
    return new_mat;
}

template <typename T>
Matrix<T> Matrix <T>::operator +(double num)
{
    Matrix <T> new_mat(*this);
    for (int i = 0; i<new_mat.get_rows(); i++)
        for (int j = 0; j<new_mat.get_cols(); j++)
            new_mat.data[i][j] += num;
    return new_mat;
}

template <typename T>
Matrix<T> Matrix <T>::operator -(double num)
{
    Matrix <T> new_mat(*this);
    for (int i = 0; i<new_mat.get_rows(); i++)
        for (int j = 0; j<new_mat.get_cols(); j++)
            new_mat.data[i][j] -= num;
    return new_mat;
}

template <typename T>
Matrix<T> Matrix <T>::operator *(double num)
{
    Matrix <T> new_mat(*this);
    for (int i = 0; i<new_mat.get_rows(); i++)
        for (int j = 0; j<new_mat.get_cols(); j++)
            new_mat.data[i][j] *= num;
    return new_mat;
}

template <typename T>
Matrix<T> Matrix <T>::operator /(double num)
{
    Matrix <T> new_mat(*this);
    for (int i = 0; i<new_mat.get_rows(); i++)
        for (int j = 0; j<new_mat.get_cols(); j++)
            new_mat.data[i][j] /= num;
    return new_mat;
}

template <typename T>
Matrix <T>::Matrix()
{
    rows = 0;
    cols = 0;
    data = nullptr;
}
#endif // MATRIX_H
