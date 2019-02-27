#ifndef H_897097BDA717A54EDF4C0E75A1E9DD98
#define H_897097BDA717A54EDF4C0E75A1E9DD98

/*
** Store integers to an array of bytes.
** Load integers from an array of bytes.
** Exploiting templates and C++11 auto.
*/

template <typename I>
I ld_be(const unsigned char *buffer)
{
    I rv = 0;
    for (auto i = 0U; i < sizeof(I); ++i)
        rv = (rv << 8) | buffer[i];
    return rv;
}

template <typename I>
const unsigned char *ld2_be(const unsigned char *buffer, I &rv)
{
    rv = 0;
    for (auto i = 0U; i < sizeof(I); ++i)
        rv = (rv << 8) | buffer[i];
    return &buffer[sizeof(I)];
}

template <typename I>
I ld_le(const unsigned char *buffer)
{
    I rv = 0;
    for (auto i = sizeof(I); i > 0; --i)
        rv = (rv << 8) | buffer[i-1];
    return rv;
}

template <typename I>
const unsigned char *ld2_le(const unsigned char *buffer, I &rv)
{
    rv = 0;
    for (auto i = sizeof(I); i > 0; --i)
        rv = (rv << 8) | buffer[i-1];
    return &buffer[sizeof(I)];
}

template <typename I>
unsigned char *st_be(unsigned char *buffer, I value)
{
    for (auto i = sizeof(I); i > 0; --i)
    {
        buffer[i-1] = value & 0xFF;
        value >>= 8;
    }
    return buffer + sizeof(I);
}

template <typename I>
unsigned char *st_le(unsigned char *buffer, I value)
{
    for (auto i = 0U; i < sizeof(I); ++i)
    {
        *buffer++ = value & 0xFF;
        value >>= 8;
    }
    return buffer;
}

#endif /* H_897097BDA717A54EDF4C0E75A1E9DD98 */
