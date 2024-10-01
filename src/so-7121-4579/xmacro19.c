/* SO 7121-4579 */
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} color_t;

#define INIT_RGB(rv, gv, bv) { .r = (rv), .g = (gv), .b = (bv) }

#define EXPAND_COLORS                                           \
  DEFINE_COLOR(COLOR_RED,       INIT_RGB(0xFF, 0x00, 0x00)  )   \
  DEFINE_COLOR(COLOR_GREEN,     INIT_RGB(0x00, 0xFF, 0x00)  )   \
  DEFINE_COLOR(COLOR_BLUE,      INIT_RGB(0x00, 0x00, 0xFF)  )   \
  DEFINE_COLOR(COLOR_AUBERGENE, INIT_RGB(0x69, 0x3B, 0x58)  )

#undef DEFINE_COLOR
#define DEFINE_COLOR(_name, _value) _value,

color_t color_map[] = { EXPAND_COLORS };
