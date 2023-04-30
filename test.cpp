#include "test.h"

void tests()
{
    length_constructor_check();
    copy_constructor_check();
    move_constructor_check();
    init_list_constructor_check();
    operator_equal_check();
    operator_equal_sum_check();
    operator_equal_diff_check();
    operator_plus();
    operator_minus();
    operator_mult();
    operator_mat_plus_num();
    operator_mat_minus_num();
    operator_mat_div_num();
    operator_mat_mult_num();
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
    std::cout << "copy constructor:" << std::endl;
    Matrix <int> init_matrix ({{1,2,3}, {4,5,6}});
    Matrix <int> copied_matrix (init_matrix);
    std::cout << "initial matrix: " << init_matrix << "copied matrix: " << copied_matrix << std::endl;
    for (int i = 0; i<init_matrix.get_rows(); i++)
        for (int j = 0; j<init_matrix.get_cols(); j++)
            if (init_matrix(i,j) != copied_matrix(i,j))
                std::cerr << "copy constuctor error" << std::endl;

    std::cout << "trying empty matrix: " << std::endl;
    try {
        Matrix <int> init_matrix ({});
        Matrix <int> copied_matrix (init_matrix);
        std::cout << "copied matrix: " << copied_matrix << std::endl;
    } catch (Exceptions &ex) {
        std::cout << ex<< std::endl;
    }
}

//template <typename T>
//Matrix <T> create_matrix (Matrix <T> &mat)
//{
//    Matrix <T> matrix (mat);
//    return matrix;
//}

void move_constructor_check()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "move constructor:" << std::endl;
    Matrix <int> init_matrix ({{1,2,3}, {4,5,6}});
    Matrix <int> temp_matrix (init_matrix);
    Matrix <int> new_matrix (init_matrix);
    std::cout << "moved matrix: " << new_matrix << std::endl;
    for (int i = 0; i<temp_matrix.get_rows(); i++)
        for (int j = 0; j<temp_matrix.get_cols(); j++)
            if (temp_matrix(i,j) != new_matrix(i,j))
                std::cerr << "move constuctor error" << std::endl;
    std::cout << "trying empty matrix: " << std::endl;
    try {
        Matrix <int> init_matrix ({});
        Matrix <int> moved_matrix (init_matrix);
        std::cout << "moved matrix: " << moved_matrix << std::endl;
    } catch (Exceptions &ex) {
        std::cout << ex<< std::endl;
    }
}

void init_list_constructor_check()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "constructor with initializer list:" << std::endl;
    const std::initializer_list<std::initializer_list<int>> lst = {{1, 2, 3, 4}, {6, 8, 10, 15}, {22, 7, 5, 19}};
    Matrix <int> mat (lst);
    int ind_i = 0, ind_j = 0;
    std::cout << "initializer list:" << std::endl;
    for (auto i : lst) {
        ind_j = 0;
        for (auto j : i){
            std::cout << j << " ";
            ind_j ++;
        }
        ind_i++;
        std::cout << std::endl;
    }
    std::cout << "initialized matrix:" << mat << std::endl;
    ind_i = 0;
    for (auto i : lst) {
        ind_j = 0;
        for (auto j : i){
            if (j != mat(ind_i, ind_j))
                std::cerr<< "initializer list constructor error:" << std::endl;
            ind_j ++;
        }
        ind_i++;
    }
    std::cout << "trying empty list:" << std::endl;
    try {
        Matrix <int> matr ({});
        std::cout << matr << std::endl;
    } catch (Exceptions &ex){
        std::cout << ex << std::endl;
    }
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
    std::cout << "operator -=:" << std::endl;
    Matrix <int> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "initial matrix: " << init_matrix;
    Matrix <int> min_matrix ({{4, 5, 6}, {1, 2, 3}});
    init_matrix -= min_matrix;
    std::cout << "equal diff matrix: " << init_matrix << std::endl;
}

void operator_plus()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "operator +:" << std::endl;
    Matrix <int> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "initial matrix: " << init_matrix;
    Matrix <int> sec_matrix ({{4, 5, 6}, {1, 2, 3}});
    Matrix <int> res_matrix = init_matrix + sec_matrix;
    std::cout << "result matrix: " << res_matrix << std::endl;
}

void operator_minus()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "operator -:" << std::endl;
    Matrix <int> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "initial matrix: " << init_matrix;
    Matrix <int> sec_matrix ({{4, 5, 6}, {1, 2, 3}});
    Matrix <int> res_matrix = init_matrix - sec_matrix;
    std::cout << "result matrix: " << res_matrix << std::endl;
}

void operator_mult()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "operator *:" << std::endl;
    Matrix <int> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "initial matrix: " << init_matrix;
    Matrix <int> sec_matrix ({{4, 5, 6}, {1, 2, 3}});
    Matrix <int> res_matrix = init_matrix * sec_matrix;
    std::cout << "result matrix: " << res_matrix << std::endl;
}

void operator_mat_plus_num()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "operator + for matrix and number:" << std::endl;
    Matrix <double> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "initial matrix: " << init_matrix;
    double a = 5.2;
    Matrix <double> res_matrix = init_matrix + a;
    std::cout << "result matrix: " << res_matrix << std::endl;
}

void operator_mat_minus_num()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "operator - for matrix and number:" << std::endl;
    Matrix <double> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "initial matrix: " << init_matrix;
    double a = 5.2;
    Matrix <double> res_matrix = init_matrix - a;
    std::cout << "result matrix: " << res_matrix << std::endl;
}

void operator_mat_div_num()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "operator / for matrix and number:" << std::endl;
    Matrix <double> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "initial matrix: " << init_matrix;
    double a = 5.2;
    Matrix <double> res_matrix = init_matrix / a;
    std::cout << "result matrix: " << res_matrix << std::endl;
}

void operator_mat_mult_num()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "operator * for matrix and number:" << std::endl;
    Matrix <double> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "initial matrix: " << init_matrix;
    double a = 5.2;
    Matrix <double> res_matrix = init_matrix * a;
    std::cout << "result matrix: " << res_matrix << std::endl;
}
