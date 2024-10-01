/* SO 7121-4579 */
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} color_t;

#define EXPAND_COLORS                                              \
  DEFINE_COLOR(COLOR_RED, {.r = 0xff, .g = 0x00, .b = 0x00})       \
  DEFINE_COLOR(COLOR_GREEN, {.r = 0x00, .g = 0xff, .b = 0x00})     \
  DEFINE_COLOR(COLOR_BLUE, {.r = 0x00, .g = 0x00, .b = 0xff})      \
  DEFINE_COLOR(COLOR_AUBERGENE, {.r = 0x69, .g = 0x3b, .b = 0x58})

// I would this to expand to:
//     color_t color_map[] = { {.r = 0xff, .g = 0x00, .b = 0x00},
//                             {.r = 0x00, .g = 0xff, .b = 0x00},
//                             ...
//                           };

#undef DEFINE_COLOR
#define DEFINE_COLOR(_name, _value) _value,
color_t color_map[] = { EXPAND_COLORS };
