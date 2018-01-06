/* SO 4584-8084 - answer by chux */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
typedef struct {
  int start_addr;
  size_t length;
} Section;

// Is point `a` in the section?
// return left:-1, right:1, else 0
static int LeftInRight(intmax_t a, const Section *sec) {
  if (a < sec->start_addr) return -1;
  if (a >= sec->start_addr + (intmax_t) sec->length) return 1;
  return 0;
}

static
bool isEncapsulated_helper(intmax_t addr, size_t len, const Section *sec, size_t n) {
  for (size_t i = 0; i<n; i++) {
    if (len == 0) return true;
    int LSide =  LeftInRight(addr, &sec[i]);
    if (LSide > 0) continue;  // all of addr/len is to the right of this section
    int RSide =  LeftInRight(addr + (intmax_t) (len - 1), &sec[i]);
    if (RSide < 0) continue;  // all of addr/len is to the left of this section

    if (LSide < 0) {
      // portion of addr/len is to the left of this section
      intmax_t Laddr = addr;
      size_t Llen = (size_t) (sec[i].start_addr - addr);
      if (!isEncapsulated_helper(Laddr, Llen, sec + 1, n-i-1)) {
        return false;
      }
    }
    if (RSide <= 0) return true;
    // portion of addr/len is to the right of this section, continue with that
    intmax_t Raddr = sec[i].start_addr + (intmax_t) sec[i].length;
    size_t Rlen = (size_t) (addr + (intmax_t) len - Raddr);
    addr = Raddr;
    len = Rlen;
  }
  return len == 0;
}

static const Section arr[] = { // x
    { .start_addr = 0, .length = 100, }, // x
    { .start_addr = 150, .length = 25, }, // x
    { .start_addr = 175, .length = 25, }, };

#define SECTION_N (sizeof arr/sizeof arr[0])

static
bool isEncapsulated(int addr, size_t len) {
  return isEncapsulated_helper(addr, len, arr, SECTION_N);
}

#include <stdio.h>

int main(void) {
  printf("%d\n", isEncapsulated(170,10));
}
