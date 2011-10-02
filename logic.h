
    #ifndef LOGIC_H_
    #define LOGIC_H_

    #include <stdint.h>

    /**
     * Basic element of the LC-3 machine.
     *
     * BIT takes on values ZER0 (0) or ONE (1)
     */
    typedef enum {
    ZERO = (uint8_t) 0, ONE = (uint8_t) 1
    } BIT;

    /**
    * A 16-"BIT" LC-3 word in big-endian format
    */
    typedef BIT word[16];

    void word_not(word *R, word *A);

    #endif

