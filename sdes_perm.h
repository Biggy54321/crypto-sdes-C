#ifndef SDES_PERM_H
#define SDES_PERM_H

#include "./sdes_types.h"

/* Permute 4 bits of given 4 bits */
i8_t perm_4(i8_t val);

/* Permute 8 bits of given 10 bits */
i8_t perm_8(i16_t val);

/* Permute 10 bits of given 10 bits */
i16_t perm_10(i16_t val);

/* Permute 8 bits of given 8 bits */
i8_t init_perm(i8_t val);

/* Permute 8 bits of given 8 bits */
i8_t init_perm_inv(i8_t val);

/* Permute 8 bits of given 4 bits */
i8_t exp_perm(i8_t val);

#endif