#include "sdes_types.h"
#include "./sdes_sub_box.h"

/**
 * @brief Permforms Substitution of the first nibble using S-box S0 and the next
 *        nibble using S-box S1. Takes in 8 bits and spits out 4 bits
 *
 * @param val
 * @return i8_t
 */
i8_t sub_box(i8_t val) {

    static i8_t _tab_s0[4][4] = {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2}
    };

    static i8_t _tab_s1[4][4] = {
        {0, 1, 2, 3},
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3}
    };

    /* Get the row and column values for S-box S0 */
    int row_s0 = (val & 0b0001) >> 0 | (val & 0b1000) >> 2;
    int col_s0 = (val & 0b0110) >> 1;

    /* Get the row and column values for S-box S1 */
    int row_s1 = (val & 0b00010000) >> 4 | (val & 0b10000000) >> 6;
    int col_s1 = (val & 0b01100000) >> 5;

    return _tab_s0[row_s0][col_s0] | (_tab_s1[row_s1][col_s1] << 2);
}