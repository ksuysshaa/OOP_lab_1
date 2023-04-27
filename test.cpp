#include "test.h"

void tests()
{
    constructors_check();
}

void constructors_check()
{
    const int rows = 5;
    const int cols = 6;
    Matrix <int> mat (rows, cols);

    std::cout << "length constructor:" << std::endl << std::endl;;
    std::cout << "expected number of rows: 5, " << "actual number of rows: " << mat.get_rows() << std::endl;
    std::cout << "expected number of columns: 6, " << "actual number of columns: " << mat.get_cols() << std::endl << std::endl;;

    if (mat.get_rows() != rows)
        std::cerr << "error with length constructor" << std::endl;
    std::cout << "trying size for rows: " << -rows << std::endl;
    try
    {
        Matrix <int> mat_new(-rows, cols);
    } catch (Exceptions &ex)
    {
        std::cout << ex << std::endl;
    }

    if (mat.get_cols() != cols)
        std::cerr << "error with length constructor" << std::endl;
    std::cout << "trying size for cols: " << -cols << std::endl;
    try
    {
        Matrix <int> mat_new(rows, -cols);
    } catch (Exceptions &ex)
    {
        std::cout << ex << std::endl;
    }
}
