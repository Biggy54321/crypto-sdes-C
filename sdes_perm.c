#include "./sdes_types.h"
#include "./sdes_perm.h"

/**
 * @brief Generate the permutation as given by the table and the value
 *
 * @param val
 * @param _tab
 * @param _tab_sz
 */
static i16_t _gen_perm(i16_t val, i8_t *_tab, i8_t _tab_sz) {

    i16_t new_val = 0;

    for (int i = 0; i < _tab_sz; i++) {

        if (val & (1 << _tab[i])) {

            new_val |= (1 << i);
        }
    }

    return new_val;
}

/**
 * @brief Permute 4 bits of 4 bits (P4 permutation)
 *
 * @param val
 * @return i8_t
 */
i8_t perm_4(i8_t val) {

    static i8_t _tab[] = {1, 3, 2, 0};
    static i8_t _tab_sz = 4;

    return (i8_t)_gen_perm((i16_t)val, _tab, _tab_sz);
}

/**
 * @brief Permute 8 bits of 10 bits (P8 permutation)
 *
 * @param val
 * @return i8_t
 */
i8_t perm_8(i16_t val) {

    static i8_t _tab[] = {5, 2, 6, 3, 7, 4, 9, 8};
    static i8_t _tab_sz = 8;

    return (i8_t)_gen_perm((i16_t)val, _tab, _tab_sz);
}

/**
 * @brief Permute 10 bits of 10 bits (P10 permutation)
 *
 * @param val
 * @return i16_t
 */
i16_t perm_10(i16_t val) {

    static i8_t _tab[] = {2, 4, 1, 6, 3, 9, 0, 8, 7, 5};
    static i8_t _tab_sz = 10;

    return (i16_t)_gen_perm((i16_t)val, _tab, _tab_sz);
}

/**
 * @brief Permute 8 bits of 8 bits (IP permutation)
 *
 * @param val
 * @return i8_t
 */
i8_t init_perm(i8_t val) {

    static i8_t _tab[] = {1, 5, 2, 0, 3, 7, 4, 6};
    static i8_t _tab_sz = 8;

    return (i8_t)_gen_perm((i16_t)val, _tab, _tab_sz);
}

/**
 * @brief Permute 8 bits of 8 bits (IP^-1 permutation)
 *
 * @param val
 * @return i8_t
 */
i8_t init_perm_inv(i8_t val) {

    static i8_t _tab[] = {3, 0, 2, 4, 6, 1, 7, 5};
    static i8_t _tab_sz = 8;

    return (i8_t)_gen_perm((i16_t)val, _tab, _tab_sz);
}

/**
 * @brief Permute 8 bits of 4 bits (E/P permutation)
 *
 * @param val
 * @return i8_t
 */
i8_t exp_perm(i8_t val) {

    static i8_t _tab[] = {3, 0, 1, 2, 1, 2, 3, 0};
    static i8_t _tab_sz = 8;

    return (i8_t)_gen_perm((i16_t)val, _tab, _tab_sz);
}

