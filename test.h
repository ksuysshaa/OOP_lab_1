#ifndef TEST_H
#define TEST_H

#include "iterator.h"

void tests();
void length_constructor_check();
void copy_constructor_check();
void move_constructor_check();
void init_list_constructor_check();
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
void get_elem_check();
void is_square_check();
void get_rows_cols_check();
void set_elem_check();
void iterator_begin_end_check();
void iterator_next_increment_check();
void iterator_value_check();
void iterator_operators_check();

#endif // TEST_H
