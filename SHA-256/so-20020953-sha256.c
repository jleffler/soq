#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Helper functions.
 */
static void PrintBin(uint32_t num)
{
    unsigned int size = sizeof(uint32_t);
    unsigned int maxPow = 1<<(size*8-1);

    for (size_t i = 0; i < size*8; ++i)
    {
        // print last bit and shift left.
        printf("%u ", num&maxPow ? 1 : 0);
        num = num<<1;
    }
}

/*************************************************/

/*
 * SHA256 - CONSTANTS.
 */

// Word size: 32bits
enum { WORD_SIZE = 32 };

// Size * 32-bits
enum { MESSAGE_BLOCK_SIZE    = 16 };
enum { MESSAGE_SCHEDULE_SIZE = 64 };
enum { WORKING_VARS_SIZE     =  8 };
enum { HASH_WORDS_SIZE       =  8 };
enum { TEMP_WORDS_SIZE       =  2 };

// Working vars vector index alias.
enum { W_VAR_A = 0 };
enum { W_VAR_B = 1 };
enum { W_VAR_C = 2 };
enum { W_VAR_D = 3 };
enum { W_VAR_E = 4 };
enum { W_VAR_F = 5 };
enum { W_VAR_G = 6 };
enum { W_VAR_H = 7 };

// Temp words vector index alias.
enum { TEMP_1 = 0 };
enum { TEMP_2 = 1 };

// SHA256 Constants K0 to K63 : Defined at fips180-3 - section 4.2.2  .
static const uint32_t SHA_256_K[] =
{
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// SHA256 initial hash value Hzero (Hzero 0-7): Defined at fips180-3 - section 5.3.3   .
static const uint32_t hash_0[] =
{
    0x6a09e667,
    0xbb67ae85,
    0x3c6ef372,
    0xa54ff53a,
    0x510e527f,
    0x9b05688c,
    0x1f83d9ab,
    0x5be0cd19
};

/*
 * SHA256 FUNCTIONS - Defined at fips180-3 - section 4.1.2  .
 * Each function operates on 32-bit words, which are represented as
 * x, y, and z. The result of each function is a new 32-bit word.
 */

static inline uint32_t ROTR32(int n, uint32_t x)
{
    return ((x >> n) | (x << (32 - n)));
}

// Function 4.2 - Ch(x,y,z) .
static inline uint32_t Ch(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) ^ (~x & z);
}

// Function 4.3 - Maj(x,y,z) .
static inline uint32_t Maj(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) ^ (x & z) ^ (y & z);
}

// Function 4.4 - UpperSigmaZero(x) .
static inline uint32_t UpperSigmaZero(uint32_t x)
{
    return ( (x >>  2) | (x << 30) ) ^
           ( (x >> 13) | (x << 19) ) ^
           ( (x >> 22) | (x << 10) );
}

// Function 4.5 - UpperSigmaOne(x) .
static inline uint32_t UpperSigmaOne(uint32_t x)
{
    return ( (x >>  6) | (x << 26) ) ^
           ( (x >> 11) | (x << 21) ) ^
           ( (x >> 25) | (x <<  7) );
}

// Function 4.6 - LowerSigmaZero(x) .
static inline uint32_t LowerSigmaZero(uint32_t x)
{
    return ( (x >>  7) | (x << 25) ) ^
           ( (x >> 18) | (x << 14) ) ^
           (x >> 3);
}

// Function 4.7 LowerSigmaOne(x) .
static inline uint32_t LowerSigmaOne(uint32_t x)
{
    return ( (x >> 17) | (x << 15) ) ^
           ( (x >> 19) | (x << 13) ) ^
           (x >> 10);
}

/*
 * Global variables.
 */

// Message schedule (W). Defined at fips180-3 - section 6.2 .
static uint32_t message_schedule[MESSAGE_SCHEDULE_SIZE];

// Working vars.  Defined at fips180-3 - section 6.2 .
// position 0->a , 1->b, 2->c, 3->d, 4->e, 5->f, 6->g, 7->h.
static uint32_t working_vars[WORKING_VARS_SIZE];

// Hash value. Defined at fips180-3 - section 6.2 .
static uint32_t hash_words[HASH_WORDS_SIZE];

// Temp words (0->T1; 1->T2). Defined at fips180-3 - section 6.2 .
static uint32_t temp_words[TEMP_WORDS_SIZE];

int main(void)
{
    int i;
    int sch_idx;
    int number_of_blocks = 1;
    uint32_t message_block[MESSAGE_BLOCK_SIZE];

    // Dummy message block 'a'
    memset(message_block, (uint32_t)0, MESSAGE_BLOCK_SIZE*sizeof(uint32_t));
    message_block[0] = 0x61; // ASCII 'a'.
    message_block[1] = 0x80; // append 10000000.
    message_block[MESSAGE_BLOCK_SIZE-1] = 0x08; // Original message length->8bits.

    printf("\n-----------DUMMY MESSAGE BLOCK representing the message 'a'-------------\n");
    for (i = 0; i < MESSAGE_BLOCK_SIZE; ++i)
    {
        PrintBin(message_block[i]);
        printf("\n");
    }
    printf("\n--------------------\n");

    /*
     * PREPROCESSING:
     */
    // 1 - TODO: MESSAGE PADDING.

    // 2 - TODO: SPLIT MESSAGE INTO n 512bits BLOCKS. M1,M2, ..., Mn

    // 3 - Set Hash words to constant hash H0;
    memcpy(hash_words, hash_0, HASH_WORDS_SIZE*sizeof(uint32_t));

    printf("\nInitial Hash:\n");
    for (i = 0; i < HASH_WORDS_SIZE; ++i)
    {
        printf("0x%08x\n", hash_words[i]);
    }

    /*************************************************/

    /* Hash Computation 6.2.2 */

    for (i = 0; i < number_of_blocks; ++i)
    {
        // 1. Prepare message schedule:
        for (sch_idx = 0; sch_idx < MESSAGE_SCHEDULE_SIZE; ++sch_idx)
        {
            if (sch_idx <= 15)
            {
                message_schedule[sch_idx] = message_block[sch_idx];
            }
            else
            {
                message_schedule[sch_idx] = LowerSigmaOne(message_schedule[sch_idx-2]) +
                                            message_schedule[sch_idx-7] +
                                            LowerSigmaZero(message_schedule[sch_idx-15]) +
                                            message_schedule[sch_idx-16];
            }
        }

        // 2. Set working var with hash val.
        memcpy(working_vars, hash_words, WORKING_VARS_SIZE*sizeof(uint32_t));

        // 3.
        for (sch_idx = 0; sch_idx < MESSAGE_SCHEDULE_SIZE; ++sch_idx)
        {
            temp_words[TEMP_1] = working_vars[W_VAR_H] +
                                 UpperSigmaOne(working_vars[W_VAR_E]) +
                                 Ch(working_vars[W_VAR_E], working_vars[W_VAR_F], working_vars[W_VAR_G]) +
                                 SHA_256_K[sch_idx] +
                                 message_schedule[sch_idx];

            temp_words[TEMP_2] = UpperSigmaZero(working_vars[W_VAR_A]) +
                                 Maj(working_vars[W_VAR_A], working_vars[W_VAR_B], working_vars[W_VAR_C]);

            working_vars[W_VAR_H] = working_vars[W_VAR_G];
            working_vars[W_VAR_G] = working_vars[W_VAR_F];
            working_vars[W_VAR_F] = working_vars[W_VAR_E];
            working_vars[W_VAR_E] = working_vars[W_VAR_D] + temp_words[TEMP_1];
            working_vars[W_VAR_D] = working_vars[W_VAR_C];
            working_vars[W_VAR_C] = working_vars[W_VAR_B];
            working_vars[W_VAR_B] = working_vars[W_VAR_A];
            working_vars[W_VAR_A] = temp_words[TEMP_1] + temp_words[TEMP_2];
        }

        // 4. Compute intermediate hash.
        hash_words[0] += working_vars[W_VAR_A];
        hash_words[1] += working_vars[W_VAR_B];
        hash_words[2] += working_vars[W_VAR_C];
        hash_words[3] += working_vars[W_VAR_D];
        hash_words[4] += working_vars[W_VAR_E];
        hash_words[5] += working_vars[W_VAR_F];
        hash_words[6] += working_vars[W_VAR_G];
        hash_words[7] += working_vars[W_VAR_H];
    }

    printf("\nMessage Block:\n");
    for (i = 0; i < MESSAGE_BLOCK_SIZE; ++i)
    {
        printf("%08x\n", message_block[i]);
    }

    printf("\nComputed SHA256:\n");

    for (i = 0; i < HASH_WORDS_SIZE; ++i)
    {
        printf("%08x", hash_words[i]);
    }
    putchar('\n');

    return 0;
}

