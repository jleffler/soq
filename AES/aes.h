/*
This optimized <../aesbench/> AES implementation conforms to FIPS-197.
Source: http://www.cs.rochester.edu/u/brown/Crypto/src/AES.c
*/

#ifndef AES_H_INCLUDED
#define AES_H_INCLUDED

#ifndef uint8
#define uint8  unsigned char
#endif

#ifndef uint32
#define uint32 unsigned long int
#endif

typedef struct
{
    uint32 erk[64];     /* encryption round keys */
    uint32 drk[64];     /* decryption round keys */
    int nr;             /* number of rounds */
} aes_context;

int  aes_set_key(aes_context *ctx, uint8 *key, int nbits);
void aes_encrypt(aes_context *ctx, uint8 input[16], uint8 output[16]);
void aes_decrypt(aes_context *ctx, uint8 input[16], uint8 output[16]);
void aes_gen_tables(void);

#endif /* aes.h */
