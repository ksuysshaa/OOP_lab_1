#ifndef TEST_H
#define TEST_H

#include "matrix.h"
#include "exceptions.h"

void tests();
void length_constructor_check();
void copy_constructor_check();
void operator_equal_check();
void operator_equal_sum_check();
void operator_equal_diff_check();
void operator_plus();
void operator_minus();
void operator_mult();
void operator_mat_plus_num();
void operator_mat_minus_num();
void operator_mat_div_num();
void operator_mat_mult_num();

#endif // TEST_H
