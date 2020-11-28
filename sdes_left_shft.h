#ifndef SDES_LEFT_SHFT_H
#define SDES_LEFT_SHFT_H

#include "./sdes_types.h"

/* Circularly shift the 5 bit groups of the input 10 bits by n places to the
 * left each */
i16_t left_shft(i16_t val, i8_t n);

#endif