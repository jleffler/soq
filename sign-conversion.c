/* SO 21050620 */
#include <stdint.h>
extern int32_t foo(uint32_t v);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wsign-conversion"
int32_t foo(uint32_t v)
{
    uint32_t result = v;
    return result;
}
#pragma GCC diagnostic pop
