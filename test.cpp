#include "test.h"

void tests()
{
    length_constructor_check();
    copy_constructor_check();
    init_list_constructor_check();
    //move_constructor_check();
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
    get_elem_check();
    get_rows_cols_check();
    is_square_check();
    set_elem_check();

    iterator_begin_end_check();

    move_constructor_check();
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
        Matrix <int> init_matrix;
        Matrix <int> copied_matrix (init_matrix);
        std::cout << copied_matrix << std::endl;
    } catch (Exceptions &ex) {
        std::cout << ex<< std::endl;
    }
}

void move_constructor_check() //??? программа заканчивается сразу после этого конструктора
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "move constructor:" << std::endl;
    Matrix <int> init_matrix ({{1,2,3}, {4,5,6}});
    Matrix <int> temp_matrix (init_matrix);
    Matrix <int> moved_matrix (std::move(init_matrix));
    std::cout << "init matrix copied to temp matrix: "<< temp_matrix << std::endl;
    std::cout << "moved matrix: " << moved_matrix << std::endl;
    for (int i = 0; i<temp_matrix.get_rows(); i++)
        for (int j = 0; j<temp_matrix.get_cols(); j++)
            if (temp_matrix(i,j) != moved_matrix(i,j))
                std::cerr << "move constuctor error" << std::endl;

    std::cout << "trying empty matrix: " << std::endl;
    try {
        Matrix <int> init_matrix (1,1);
        Matrix <int> moved_matrix (std::move(init_matrix));
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
    std::cout << "list of initializer lists:" << std::endl;
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
    for (int i = 0; i<init_matrix.get_rows(); i++)
        for (int j = 0; j<init_matrix.get_cols(); j++)
            if (init_matrix(i,j) != equal_matrix(i,j))
                std::cerr << "operator = error." << std::endl;

    std::cout << "trying to equate matrix with different sizes:" << std::endl;
    try {
        Matrix <int> matr (1,1);
        std::cout << "first matrix number of rows and cols: "<< matr.get_rows() << " " << matr.get_cols() << std::endl;
        std::cout << "second matrix number of rows and cols: "<< equal_matrix.get_rows() << " " << equal_matrix.get_cols() << std::endl;
        equal_matrix = matr;
        std::cout << matr << std::endl;
    } catch (Exceptions &ex){
        std::cout << ex << std::endl;
    }

    std::cout << "trying to equate empty matrix to matrix:" << std::endl;
    try {
        Matrix <int> matr;
//        std::cout << matr << std::endl;
        Matrix <int> new_mat = matr;
        std::cout << new_mat << matr <<  std::endl;
    } catch (Exceptions &ex){
        std::cout << ex << std::endl;
    }
}

void operator_equal_sum_check()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "operator +=:" << std::endl;
    Matrix <int> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "initial matrix: " << init_matrix;
    Matrix <int> temp_matrix (init_matrix);
    Matrix <int> sum_matrix ({{7, -5, 29}, {2, 4, 7}});
    std::cout << "second matrix: " << sum_matrix;
    init_matrix += sum_matrix;
    std::cout << "equal sum matrix: " << init_matrix << std::endl;
    for (int i = 0; i<init_matrix.get_rows(); i++)
        for (int j = 0; j<init_matrix.get_cols(); j++)
            if (init_matrix(i,j) != temp_matrix(i,j)+sum_matrix(i,j))
                std::cerr << "operator += error." << std::endl;

    std::cout << "trying += equal matrix: " << std::endl;
    std::cout << "initial matrix: " << temp_matrix;
    Matrix <int> t_temp_matrix (temp_matrix);
    Matrix <int> sec_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "second matrix: " << sec_matrix;
    temp_matrix += sec_matrix;
    std::cout << "equal sum matrix: " << temp_matrix << std::endl;
    for (int i = 0; i<init_matrix.get_rows(); i++)
        for (int j = 0; j<init_matrix.get_cols(); j++)
            if (temp_matrix(i,j) != t_temp_matrix(i,j)+sec_matrix(i,j))
                std::cerr << "operator += error." << std::endl;

    std::cout << "trying to += matrix with different sizes:" << std::endl;
    try {
        Matrix <int> matr (1,1);
        std::cout << "first matrix number of rows and cols: "<< matr.get_rows() << " " << matr.get_cols() << std::endl;
        std::cout << "second matrix number of rows and cols: "<< sum_matrix.get_rows() << " " << sum_matrix.get_cols() << std::endl;
        matr += sum_matrix;
        std::cout << matr << std::endl;
    } catch (Exceptions &ex){
        std::cout << ex << std::endl;
    }

    std::cout << "trying to += empty matrix to matrix:" << std::endl;
    try {
        Matrix <int> matr;
        init_matrix += matr;
        std::cout << init_matrix << matr <<  std::endl;
    } catch (Exceptions &ex){
        std::cout << ex << std::endl;
    }
}

void operator_equal_diff_check()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "operator -=:" << std::endl;
    Matrix <int> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "initial matrix: " << init_matrix;
    Matrix <int> temp_matrix (init_matrix);
    Matrix <int> min_matrix ({{7, -5, 29}, {2, 4, 7}});
    init_matrix -= min_matrix;
    std::cout << "equal diff matrix: " << init_matrix << std::endl;
    for (int i = 0; i<init_matrix.get_rows(); i++)
        for (int j = 0; j<init_matrix.get_cols(); j++)
            if (init_matrix(i,j) != temp_matrix(i,j)-min_matrix(i,j))
                std::cerr << "operator -= error." << std::endl;

    std::cout << "trying -= equal matrix: " << std::endl;
    std::cout << "initial matrix: " << temp_matrix;
    Matrix <int> t_temp_matrix (temp_matrix);
    Matrix <int> sec_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "second matrix: " << sec_matrix;
    temp_matrix -= sec_matrix;
    std::cout << "equal diff matrix: " << temp_matrix << std::endl;
    for (int i = 0; i<init_matrix.get_rows(); i++)
        for (int j = 0; j<init_matrix.get_cols(); j++)
            if (temp_matrix(i,j) != t_temp_matrix(i,j)-sec_matrix(i,j))
                std::cerr << "operator += error." << std::endl;

    std::cout << "trying to -= matrix with different sizes:" << std::endl;
    try {
        Matrix <int> matr (1,1);
        std::cout << "first matrix number of rows and cols: "<< matr.get_rows() << " " << matr.get_cols() << std::endl;
        std::cout << "second matrix number of rows and cols: "<< min_matrix.get_rows() << " " << min_matrix.get_cols() << std::endl;
        matr -= min_matrix;
        std::cout << matr << std::endl;
    } catch (Exceptions &ex){
        std::cout << ex << std::endl;
    }

    std::cout << "trying to -= empty matrix to matrix:" << std::endl;
    try {
        Matrix <int> matr;
        init_matrix -= matr;
        std::cout << init_matrix << matr <<  std::endl;
    } catch (Exceptions &ex){
        std::cout << ex << std::endl;
    }
}

void operator_plus()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "operator +:" << std::endl;
    Matrix <int> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    Matrix <int> sec_matrix ({{7, -5, 29}, {2, 4, 7}});
    std::cout << "initial matrix: " << init_matrix << "second matrix" << sec_matrix;
    Matrix <int> res_matrix = init_matrix + sec_matrix;
    std::cout << "result matrix: " << res_matrix << std::endl;
    for (int i = 0; i<init_matrix.get_rows(); i++)
        for (int j = 0; j<init_matrix.get_cols(); j++)
            if (res_matrix(i,j) != sec_matrix(i,j)+init_matrix(i,j))
                std::cerr << "operator + error." << std::endl;


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

void get_elem_check()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "get elem:" << std::endl;
    Matrix <int> init_matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "initial matrix: " << init_matrix;
    const int ind_r = 1, ind_c = 1;
    std::cout << "expected elem: " << init_matrix(ind_r, ind_c) << std::endl << "actual elem: " << init_matrix.get_elem(ind_r,ind_c) << std::endl;
    if (init_matrix(ind_r, ind_c) != init_matrix.get_elem(ind_r,ind_c))
            std::cerr << "get elem error." << std::endl;
    std::cout << "trying index for rows: " << -ind_r << std::endl;
    try {
        std::cout << init_matrix.get_elem(-ind_r, ind_c) <<std::endl;
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }
    std::cout << "trying index for cols: " << -ind_c << std::endl;
    try {
        std::cout << init_matrix.get_elem(ind_r, -ind_c) <<std::endl;
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }

    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "operator ():" << std::endl;
    std::cout << "initial matrix: " << init_matrix;
    const int ind_r_2 = 0, ind_c_2 = 0;
    std::cout << "expected elem: " << init_matrix.get_elem(ind_r_2, ind_c_2) << std::endl << "actual elem: " << init_matrix(ind_r_2,ind_c_2) << std::endl;
    if (init_matrix(ind_r_2, ind_c_2) != init_matrix.get_elem(ind_r_2,ind_c_2))
            std::cerr << "get elem error." << std::endl;
    std::cout << "trying index for rows: " << init_matrix.get_rows()+5 << std::endl;
    try {
        std::cout << init_matrix.get_elem(init_matrix.get_rows()+5, ind_c_2) <<std::endl;
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }
    std::cout << "trying index for cols: " << init_matrix.get_cols()+5 << std::endl;
    try {
        std::cout << init_matrix.get_elem(ind_r, init_matrix.get_cols()+5) <<std::endl;
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }
}

void is_square_check()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "is square:" << std::endl;
    Matrix <int> init_matrix ({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    std::cout << "squared matrix: " << init_matrix;
    if (init_matrix.is_square())
        std::cout<<"matrix is a square."<<std::endl;
    else
        std::cout<<"matrix is not a square."<<std::endl;

    std::cout << std::endl;
    Matrix <int> matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "not squared matrix: " << matrix;
    if (matrix.is_square())
        std::cout<<"matrix is a square."<<std::endl;
    else
        std::cout<<"matrix is not a square."<<std::endl;
}

void get_rows_cols_check()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "get rows:" << std::endl;
    const int rows = 2, cols = 3;
    Matrix <int> mat_1 (rows, cols);
    Matrix <int> mat_2 (rows, cols);
    std::cout << "first mat number of rows: " << mat_1.get_rows() << std::endl
                  << "second mat number of rows: " << mat_2.get_rows() << std::endl << std::endl;
    if (mat_1.get_rows() != mat_2.get_rows()) {
        std::cerr << "get rows error." << std::endl;
    }
    std::cout << "get cols:" << std::endl;
    std::cout << "first mat number of cols: " << mat_1.get_cols() << std::endl
                  << "second mat number of cols: " << mat_2.get_cols() << std::endl << std::endl;
    if (mat_1.get_cols() != mat_2.get_cols()) {
        std::cerr << "get cols error." << std::endl;
    }

    std::cout << "trying empty matrix" << std::endl;
    Matrix <int> mat;
    std::cout << "matrix number of rows, cols: " << mat.get_rows() << ", " << mat.get_cols() << std::endl;
}

void set_elem_check()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "set elem:" << std::endl;
    const int elem = 89;
    const int ind_r = 0;
    const int ind_c = 1;
    Matrix <int> matrix ({{1, 2, 3}, {4, 5, 6}});
    std::cout << "initial matrix: " << matrix;
    matrix.set_elem(ind_r, ind_c, elem);
    std::cout << "changed matrix: " << matrix;
    std::cout<<std::endl;
    std::cout << "expected element: " << elem << std::endl << "actual element: " << matrix(ind_r, ind_c) << std::endl;
    std::cout<<std::endl;
    std::cout << "trying index for rows: " << matrix.get_rows()+5 << std::endl;
    try {
        matrix.set_elem(matrix.get_rows()+5, ind_c, elem);
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }
    std::cout << "trying index for cols: " << matrix.get_cols()+5 << std::endl;
    try {
        matrix.set_elem(ind_r, matrix.get_cols()+5, elem);
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }
}

void iterator_begin_end_check()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "iterator begin:" << std::endl;
    Matrix <int> matrix ({{1, 2, 3}, {4, 5, 6}});
    Iterator <int> it_1 = matrix.iterator_begin();
    it_1.is_begin() ? std::cout << "test passed" << std::endl : std::cout << "test not passed. iterator begin error." << std::endl;

    std::cout << "iterator end:" << std::endl;
    Iterator <int> it_2 = matrix.iterator_end();
    it_2.is_end() ? std::cout << "test passed" << std::endl : std::cout << "test not passed. iterator end error." << std::endl;
}
