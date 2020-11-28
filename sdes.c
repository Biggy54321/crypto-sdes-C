#include "./sdes_types.h"
#include "./sdes_perm.h"
#include "./sdes_sub_box.h"
#include "./sdes_left_shft.h"
#include "./sdes.h"

/**
 * @brief Generate the two subkeys for each round using the given key
 *
 * @param key
 * @param subkeys
 */
static void _sdes_gen_subkeys(i16_t key, i8_t *subkeys) {

    i16_t key_p10;
    i16_t key_p10_ls1;
    i16_t key_p10_ls3;

    /* Permute the 10 bits input key */
    key_p10 = perm_10(key);

    /* Rotate the 5 bits groups to left by 1 for the first subkey */
    key_p10_ls1 = left_shft(key_p10, 1);

    /* Rotate the 5 bits groups to left by 3 for the second subkey */
    key_p10_ls3 = left_shft(key_p10, 3);

    /* Permute 8 bits out of 10 bits for both the subkeys */
    subkeys[0] = perm_8(key_p10_ls1);
    subkeys[1] = perm_8(key_p10_ls3);
}

/**
 * @brief Performs the 'fk' function on the given block using the given subkey
 *
 * @param block
 * @param subkey
 * @return i8_t
 */
static i8_t _sdes_fk(i8_t block, i8_t subkey) {

    i8_t temp;

    /* Get the left and right parts of the given block */
    i8_t block_l = (block & 0b11110000);
    i8_t block_r = (block & 0b1111);

    /* Expand the right block */
    temp = exp_perm(block_r);

    /* Exor with the given subkey */
    temp = temp ^ subkey;

    /* Pass the obtained 8 bit value to the S-boxes */
    temp = sub_box(temp);

    /* Permute the obtained 4 bit value */
    temp = perm_4(temp);

    /* Form the result block */
    temp = temp << 4;
    temp = temp ^ block_l;
    temp = temp | block_r;

    return temp;
}

/**
 * @brief Encrypt the given plaintext block using the two pregenerated subkeys
 *
 * @param plainblock
 * @param subkeys
 * @return i8_t
 */
static i8_t _sdes_enc_block(i8_t plainblock, i8_t *subkeys) {

    i8_t cipherblock;

    /* Apply the initial permutation to the plaintext block */
    cipherblock = init_perm(plainblock);

    /* Apply the SDES function `fk` to the current block using the first subkey */
    cipherblock = _sdes_fk(cipherblock, subkeys[0]);

    /* Swap the two nibbles */
    cipherblock = ((cipherblock & 0b11110000) >> 4) | ((cipherblock & 0b1111) << 4);

    /* Apply the SDES function `fk` to the current block using the second subkey */
    cipherblock = _sdes_fk(cipherblock, subkeys[1]);

    /* Apply the inverse initial permutation to the current block */
    cipherblock = init_perm_inv(cipherblock);

    return cipherblock;
}

/**
 * @brief Decrypt the given ciphertext block using the two pregenerated subkeys
 *
 * @param cipherblock
 * @param subkeys
 * @return i8_t
 */
static i8_t _sdes_dec_block(i8_t cipherblock, i8_t *subkeys) {

    i8_t plainblock;

    /* Apply the initial permutation to the cipherblock */
    plainblock = init_perm(cipherblock);

    /* Apply the SDES function `fk` to the current block using the second subkey */
    plainblock = _sdes_fk(plainblock, subkeys[1]);

    /* Swap the two nibbles */
    plainblock = ((plainblock & 0b11110000) >> 4) | ((plainblock & 0b1111) << 4);

    /* Apply the SDES function `fk` to the current block using the first subkey */
    plainblock = _sdes_fk(plainblock, subkeys[0]);

    /* Apply the inverse initial permutation to the current block */
    plainblock = init_perm_inv(plainblock);

    return plainblock;
}

/**
 * @brief Encrypt the given plaintext using the key and store the result in the
 *        ciphertext array
 *
 * @param plaintext
 * @param ciphertext
 * @param size
 * @param key
 */
void sdes_encrypt(i8_t *plaintext, i8_t *ciphertext, i64_t size, i16_t key) {

    i8_t subkeys[2];

    /* Generate the subkeys */
    _sdes_gen_subkeys(key, subkeys);

    /* For every block in the input plaintext */
    for (int i = 0; i < size; i++) {

        ciphertext[i] = _sdes_enc_block(plaintext[i], subkeys);
    }
}

/**
 * @brief Decrypt the given cipphertext using the key and store the result in
 *        the plaintext array
 *
 * @param ciphertext
 * @param plaintext
 * @param size
 * @param key
 */
void sdes_decrypt(i8_t *ciphertext, i8_t *plaintext, i64_t size, i16_t key) {

    i8_t subkeys[2];

    /* Generate the subkeys */
    _sdes_gen_subkeys(key, subkeys);

    /* For every block in the input ciphertext */
    for (int i = 0; i < size; i++) {

        plaintext[i] = _sdes_dec_block(ciphertext[i], subkeys);
    }
}