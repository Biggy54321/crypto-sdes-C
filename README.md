# Simplified Data Encryption Standard (S-DES)

* The S-DES algorithm is implemented in two different programs, each using the
same set of library routines.
* The two programs are **sdes_enc.c** and **sdes_dec.c**, for encryption and
decryption of the input messages respectively.
* Both the programs take the key as a command line argument and the message through
the standard input and prints the result message on the standard output.
* The library routine implemented involves the code for the following operations
    + Different data types required
    + Permutations boxes
    + Substitution boxes
    + Circular left shifting
* The parameters of S-DES implemented

    |**Parameter**|**Value**|
    |-|-|
    |Plaintext block size|8 bits|
    |Key size|10 bits|
    |Number of rounds|2|
    |Operation mode|Electronic Code Book (ECB)|

### Program source

#### Data types code (sdes_types.h)

Provides the different data types of various sizes required for S-DES

#### Substitution box code (sdes_sub_box.h and sdes_sub_box.c)

Provides the S-box functionality wherein substitutes two nibbles of a byte using
two different S-boxes.

#### Permutation boxes (sdes_perm.h and sdes_perm.c)

Provides the different permutation functionalities required which includes, 10
bit permutation for subkey generation, initial permutation, inverse initial
permutation, expansion permutation, etc.

#### Encryption, Decryption and Subkey Generation (sdes.h and sdes.c)

Provides the routines for subkey generation, encryption of given string and
decryption of the given string

#### Driver programs for encryption and decryption (sdes_enc.c and sdes_dec.c)

Provides two programs which use the above mentioned routines to provide a command
line interface to encrypt and decrypt messages using S-DES algorithm.

### Program usage

The programs can be compiled as follows

```zsh
$> # For encryption program (sdes_enc)
$> cc sdes.c sdes_enc.c sdes_left_shft.c sdes_perm.c sdes_sub_box.c -o sdes_enc
$> # For decryption program (sdes_dec)
$> cc sdes.c sdes_dec.c sdes_left_shft.c sdes_perm.c sdes_sub_box.c -o sdes_dec
```

The programs can be used as follows:

```zsh
$> # For encryption
$> ./sdes_enc <key>
<plaintext_msg> (input)
<ciphertext_msg> (output)
```

```zsh
$> # For decryption
$> ./sdes_dec <key>
<ciphertext_msg> (input)
<plaintext_msg> (output)
```

### Program output

To test the correctness of the programs, we can run the encryption program,
and give the output of the encryption program i.e. the ciphertext immediately
to the decryption program. If the output of the decryption program at the end
as same as the input then, both the programs are correct

For doing that test do the following

```zsh
$> ./sdes_enc <key> | ./sdes_dec <key>
<plaintext_msg> (input)
<plaintext_msg> (output)
```