#include "test.h"

void tests()
{
    length_constructor_check();
    copy_constructor_check();
    operator_equal_check();
    operator_equal_sum_check();
    operator_equal_diff_check();
}

void length_constructor_check()
{
    const int rows = 5;
    const int cols = 6;
    Matrix <int> mat (rows, cols);
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "length constructor:" << std::endl;
    std::cout << "expected number of rows: 5, " << "actual number of rows: " << mat.get_rows() << std::endl;
    std::cout << "expected number of columns: 6, " << "actual number of columns: " << mat.get_cols() << std::endl << std::endl;;

    if (mat.get_rows() != rows)
        std::cerr << "error with length constructor" << std::endl;
    std::cout << "trying size for rows: " << -rows << std::endl;
    try {
        Matrix <int> mat_new(-rows, cols);
    } catch (Exceptions &ex) {
        std::cout << ex;
    }

    if (mat.get_cols() != cols)
        std::cerr << "error with length constructor" << std::endl;
    std::cout << "trying size for cols: " << -cols << std::endl;
    try {
        Matrix <int> mat_new(rows, -cols);
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }
}

void copy_constructor_check()
{
    std::cout << "----------------------------------------------" << std::endl;
    Matrix <int> init_matrix ({{1, 2, 3},
                               {4, 5, 6}});   
    Matrix <int> copied_matrix (init_matrix);
    std::cout << "copy constructor:" << std::endl;
    std::cout << "initial matrix: " << init_matrix << "copied matrix: " << copied_matrix << std::endl;
    for (int i = 0; i<init_matrix.get_rows(); i++)
        for (int j = 0; j<init_matrix.get_cols(); j++)
            if (init_matrix(i,j) != copied_matrix(i,j))
                std::cerr << "copy constuctor error" << std::endl;
}

void operator_equal_check()
{
    std::cout << "----------------------------------------------" << std::endl;
    Matrix <int> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    Matrix <int> equal_matrix = init_matrix;
    std::cout << "operator =:" << std::endl;
    std::cout << "initial matrix: " << init_matrix << "equal matrix: " << equal_matrix << std::endl;
}

void operator_equal_sum_check()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "operator +=:" << std::endl;
    Matrix <int> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "initial matrix: " << init_matrix;
    Matrix <int> sum_matrix ({{1, 2, 3}, {4, 5, 6}});
    init_matrix += sum_matrix;
    std::cout << "equal sum matrix: " << init_matrix << std::endl;
}

void operator_equal_diff_check()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "operator +=:" << std::endl;
    Matrix <int> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "initial matrix: " << init_matrix;
    Matrix <int> min_matrix ({{4, 5, 6}, {1, 2, 3}});
    init_matrix -= min_matrix;
    std::cout << "equal sum matrix: " << init_matrix << std::endl;
}
