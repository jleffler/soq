#include <cstddef>

template <typename I>
I ld_be(const unsigned char *buffer)
{
    I rv = 0;
    for (size_t i = 0; i < sizeof(I); ++i)
        rv = (rv << 8) | buffer[i];
    return rv;
}

template <typename I>
const unsigned char *ld2_be(const unsigned char *buffer, I &rv)
{
    rv = 0;
    for (size_t i = 0; i < sizeof(I); ++i)
        rv = (rv << 8) | buffer[i];
    return &buffer[sizeof(I)];
}

template <typename I>
I ld_le(const unsigned char *buffer)
{
    I rv = 0;
    for (size_t i = sizeof(I); i > 0; --i)
        rv = (rv << 8) | buffer[i-1];
    return rv;
}

template <typename I>
const unsigned char *ld2_le(const unsigned char *buffer, I &rv)
{
    rv = 0;
    for (size_t i = sizeof(I); i > 0; --i)
        rv = (rv << 8) | buffer[i-1];
    return &buffer[sizeof(I)];
}

template <typename I>
unsigned char *st_be(unsigned char *buffer, I value)
{
    for (size_t i = 0; i < sizeof(I); ++i)
    {
        *buffer++ = value & 0xFF;
        value >>= 8;
    }
    return buffer;
}

template <typename I>
unsigned char *st_le(unsigned char *buffer, I value)
{
    for (size_t i = 0; i < sizeof(I); ++i)
    {
        *buffer++ = value & 0xFF;
        value >>= 8;
    }
    return buffer;
}

#include <cstdint>
#include <iostream>
using namespace std;

void test1(void)
{
    unsigned char data[] = "A1C2E3G4";

    uint64_t be64 = ld_be<uint64_t>(data);
    uint64_t le64 = ld_le<uint64_t>(data);
    cout << "Data: " << data << ", BE64 = 0x" << hex << be64 << "\n";
    cout << "Data: " << data << ", LE64 = 0x" << hex << le64 << "\n";

    uint32_t be32 = ld_be<uint32_t>(data);
    uint32_t le32 = ld_le<uint32_t>(data);
    cout << "Data: " << data << ", BE32 = 0x" << hex << be32 << "\n";
    cout << "Data: " << data << ", LE32 = 0x" << hex << le32 << "\n";

    uint16_t be16 = ld_be<uint16_t>(data);
    uint16_t le16 = ld_le<uint16_t>(data);
    cout << "Data: " << data << ", BE16 = 0x" << hex << be16 << "\n";
    cout << "Data: " << data << ", LE16 = 0x" << hex << le16 << "\n";

    uint8_t be8 = ld_be<uint8_t>(data);
    uint8_t le8 = ld_le<uint8_t>(data);
    cout << "Data: " << data << ", BE08 = 0x" << hex << int(be8) << "\n";
    cout << "Data: " << data << ", LE08 = 0x" << hex << int(le8) << "\n";
}

/*
** Test ld2_le<I>() and ld2_be<I>().
** Storing values in the begin array is a test artefact rather than part
** of normal usage.  The data portion of the output line could be
** printed before the call to the function, which would render the array
** unnecessary.
** The disadvantage of this technique is that it requires variables
** defined before they're initialized.  If they're part of a structure,
** though, that isn't a problem.
** The advantage of this technique is that the controlling type is a
** parameter, so you don't need to specify the type in the call.  Or is
** that a disadvantage?
*/
void test2(void)
{
    const unsigned char data[] = "@0A1B2C3D4E5F6G7H8I9a1b2c3d4e5f6g7h8i9";
    const unsigned char *ptr = data;
    const unsigned char *begin[8];
    int i = 0;

    uint64_t be64;
    begin[i++] = ptr;
    ptr = ld2_be(ptr, be64);
    uint64_t le64;
    begin[i++] = ptr;
    ptr = ld2_le(ptr, le64);
    cout << "Data: " << begin[0] << ", BE64 = 0x" << hex << be64 << "\n";
    cout << "Data: " << begin[1] << ", LE64 = 0x" << hex << le64 << "\n";

    uint32_t be32;
    begin[i++] = ptr;
    ptr = ld2_be(ptr, be32);
    uint32_t le32;
    begin[i++] = ptr;
    ptr = ld2_le(ptr, le32);
    cout << "Data: " << begin[2] << ", BE32 = 0x" << hex << be32 << "\n";
    cout << "Data: " << begin[3] << ", LE32 = 0x" << hex << le32 << "\n";

    uint16_t be16;
    begin[i++] = ptr;
    ptr = ld2_be(ptr, be16);
    uint16_t le16;
    begin[i++] = ptr;
    ptr = ld2_le(ptr, le16);
    cout << "Data: " << begin[4] << ", BE16 = 0x" << hex << be16 << "\n";
    cout << "Data: " << begin[5] << ", LE16 = 0x" << hex << le16 << "\n";

    uint8_t be8;
    begin[i++] = ptr;
    ptr = ld2_be(ptr, be8);
    uint8_t le8;
    begin[i++] = ptr;
    ptr = ld2_be(ptr, le8);
    cout << "Data: " << begin[6] << ", BE08 = 0x" << hex << int(be8) << "\n";
    cout << "Data: " << begin[7] << ", LE08 = 0x" << hex << int(le8) << "\n";
    cout << "Unused: " << ptr << "\n";
}

int main()
{
    test1();
    test2();
}
