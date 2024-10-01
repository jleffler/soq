/* SO 7121-4579 */
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color_t;

#define INIT_RGB(rv, gv, bv) { rv, gv, bv }

#define EXPAND_COLORS                                                      \
    DEFINE_COLOR(COLOR_RED,       INIT_RGB(.r = 0xFF, .g = 0x00, .b = 0x00)) \
    DEFINE_COLOR(COLOR_GREEN,     INIT_RGB(.r = 0x00, .g = 0xFF, .b = 0x00)) \
    DEFINE_COLOR(COLOR_BLUE,      INIT_RGB(.r = 0x00, .g = 0x00, .b = 0xFF)) \
    DEFINE_COLOR(COLOR_AUBERGINE, INIT_RGB(.r = 0x69, .g = 0x3B, .b = 0x58))

#undef DEFINE_COLOR
#define DEFINE_COLOR(_name, _value) _value,

color_t color_map[] = { EXPAND_COLORS };

#undef DEFINE_COLOR
#define DEFINE_COLOR(name, value)   name,
enum
{
    EXPAND_COLORS
    MAX_COLOR_NAME
};
#undef DEFINE_COLOR

typedef struct
{
    color_t tl_corner;
    color_t tr_corner;
    color_t bl_corner;
    color_t br_corner;
} gradient_t;

#define RGB_RED       INIT_RGB(.r = 0xFF, .g = 0x00, .b = 0x00)
#define RGB_GREEN     INIT_RGB(.r = 0x00, .g = 0xFF, .b = 0x00)
#define RGB_BLUE      INIT_RGB(.r = 0x00, .g = 0x00, .b = 0xFF)
#define RGB_AUBERGINE INIT_RGB(.r = 0x69, .g = 0x3B, .b = 0x58)

#define EXPAND_GRADIENT \
    DEFINE_GRADIENT(VARIANT1, RGB_RED, RGB_GREEN, RGB_BLUE, RGB_AUBERGINE) \
    DEFINE_GRADIENT(VARIANT2, RGB_GREEN, RGB_BLUE, RGB_AUBERGINE, RGB_RED) \
    DEFINE_GRADIENT(VARIANT3, RGB_BLUE, RGB_AUBERGINE, RGB_RED, RGB_GREEN) \
    DEFINE_GRADIENT(VARIANT4, RGB_AUBERGINE, RGB_RED, RGB_GREEN, RGB_BLUE)

#undef DEFINE_GRADIENT
#define DEFINE_GRADIENT(name, tlc, trc, blc, brc) \
    { .tl_corner = tlc, .tr_corner = trc, .bl_corner = blc, .br_corner = brc },

static gradient_t boxes[] = { EXPAND_GRADIENT };
