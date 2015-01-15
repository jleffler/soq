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
I ld_le(const unsigned char *buffer)
{
    I rv = 0;
    for (size_t i = sizeof(I); i > 0; --i)
        rv = (rv << 8) | buffer[i-1];
    return rv;
}

#include <cstdint>
#include <iostream>
using namespace std;

int main(void)
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
