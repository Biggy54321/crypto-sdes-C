#ifndef SDES_H
#define SDES_H

#include "./sdes_types.h"

/* Simplified Data Encryption Standard Encryption Routine */
void sdes_encrypt(i8_t *plaintext, i8_t *ciphertext, i64_t size, i16_t key);

/* Simplified Data Encryption Standard Decryption Routine */
void sdes_decrypt(i8_t *ciphertext, i8_t *plaintext, i64_t size, i16_t key);

#endif