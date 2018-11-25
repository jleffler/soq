#ifndef HEADER1_H
#define HEADER1_H
int complicated1(int input);
int complicated2(int input);
static inline int timestwo(int input) {
  return input * 2;
}
static inline int plusfive(int input) {
  return input + 5;
}
#endif
