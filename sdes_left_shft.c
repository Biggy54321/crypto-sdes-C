#include "sdes_types.h"
#include "sdes_left_shft.h"

/**
 * @brief Circularly shift the 5 bit groups of the input 10 bits by n places to
 *        the left each
 *
 * @param val
 * @param n
 * @return i16_t
 */
i16_t left_shft(i16_t val, i8_t n) {

    /* Update the rotation value */
    n = n % 5;

    /* Return if the required rotation is zero */

    int new_val;
    int mask;

    /* Get the mask for the bits which do not overflow past the MSB */
    mask = ~(~0 << (5 - n)) | ~(~0 << (5 - n)) << 5;

    /* Set the new value using the non-overflowing bits */
    new_val = (val & mask) << n;

    /* Get the mask for the bits which do overflow past the MSB */
    mask = ((~0 << (5 - n)) & 0b11111) | ((~0 << (5 - n)) & 0b11111) << 5;

    /* Set the new value using the overflowing bits */
    new_val |= (val & mask) >> (5 - n);

    return new_val;
}