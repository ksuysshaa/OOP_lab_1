#include "test.h"

void tests()
{
    length_constructor_check();
    copy_constructor_check();
}

void length_constructor_check()
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

void copy_constructor_check()
{
    Matrix <int> init_matrix ({{1, 2, 3},
                               {4, 5, 6}});
    std::cout << "basic matrix: " << init_matrix << std::endl;    
    Matrix <int> copied_matrix (init_matrix);
    std::cout << "copy constructor" << std::endl;
    std::cout << "basic matrix: " << init_matrix << "new matrix: " << copied_matrix << std::endl;
//    for (int i = 0; i < init_matrix.get_rows(); i++)
//    {
//        for (int j = 0; j < copied_matrix.get_cols(); j++)
//        {
//            data[i][j] = mat[i][j];
//        }
//    }
}
