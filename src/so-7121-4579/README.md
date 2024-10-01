### Stack Overflow Question 7121-4579

[SO 7121-4579](https://stackoverflow.com/q/71214579) &mdash;
Passing comma-separated struct initializers to C preprocessor macros

o### Basic answer
Does this work for you?
```
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} color_t;

#define INIT_RGB(rv, gv, bv) { .r = (rv), .g = (gv), .b = (bv) }

#define EXPAND_COLORS                                         \
  DEFINE_COLOR(COLOR_RED,       INIT_RGB(0xFF, 0x00, 0x00))   \
  DEFINE_COLOR(COLOR_GREEN,     INIT_RGB(0x00, 0xFF, 0x00))   \
  DEFINE_COLOR(COLOR_BLUE,      INIT_RGB(0x00, 0x00, 0xFF))   \
  DEFINE_COLOR(COLOR_AUBERGINE, INIT_RGB(0x69, 0x3B, 0x58))

#undef DEFINE_COLOR
#define DEFINE_COLOR(_name, _value) _value,

color_t color_map[] = { EXPAND_COLORS };
```
Running `cpp xmacro71.c`, I got the output:
```
# 0 "xmacro71.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "xmacro71.c"

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} color_t;
# 19 "xmacro71.c"
color_t color_map[] = { { .r = (0xFF), .g = (0x00), .b = (0x00) }, { .r = (0x00), .g = (0xFF), .b = (0x00) }, { .r = (0x00), .g = (0x00), .b = (0xFF) }, { .r = (0x69), .g = (0x3B), .b = (0x58) }, };
```
Reformatting, that yields:
```
# 0 "xmacro71.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "xmacro71.c"

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} color_t;
# 19 "xmacro71.c"
color_t color_map[] =
{
    { .r = (0xFF), .g = (0x00), .b = (0x00) },
    { .r = (0x00), .g = (0xFF), .b = (0x00) },
    { .r = (0x00), .g = (0x00), .b = (0xFF) },
    { .r = (0x69), .g = (0x3B), .b = (0x58) },
};
```
The one gotcha I ran into in the first edition of the answer — don't call the macro arguments `r`, `g`, `b`; if you do, you end up with output like:
```
{ . 0xFF = (0xFF), . 0x00 = (0x00), . 0x00 = (0x00) },
```
That is not what you want!

If you prefer to keep the explicitness of the initializers visible, you can also use:
```
/* SO 7121-4579 */
typedef struct {
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
```
That produces essentially the same output — the difference is primarily the absence of parentheses around the values in this example (missing because they aren't present in the arguments like `.r = (0xFF)`).

### Extended answer
Tackling nested structures is doable.  This too works for me:
```
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
```
Output after reformatting (adding newlines and blanks, and removing some newlines corresponding to macro definitions):
```
# 0 "xmacro97.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "xmacro97.c"

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color_t;
# 20 "xmacro97.c"
color_t color_map[] =
{
    { .r = 0xFF, .g = 0x00, .b = 0x00 },
    { .r = 0x00, .g = 0xFF, .b = 0x00 },
    { .r = 0x00, .g = 0x00, .b = 0xFF },
    { .r = 0x69, .g = 0x3B, .b = 0x58 },
};

enum
{
    COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_AUBERGINE,
    MAX_COLOR_NAME
};

typedef struct
{
    color_t tl_corner;
    color_t tr_corner;
    color_t bl_corner;
    color_t br_corner;
} gradient_t;
# 54 "xmacro97.c"
static gradient_t boxes[] =
{
    {
        .tl_corner = { .r = 0xFF, .g = 0x00, .b = 0x00 },
        .tr_corner = { .r = 0x00, .g = 0xFF, .b = 0x00 },
        .bl_corner = { .r = 0x00, .g = 0x00, .b = 0xFF },
        .br_corner = { .r = 0x69, .g = 0x3B, .b = 0x58 }
    },
    {
        .tl_corner = { .r = 0x00, .g = 0xFF, .b = 0x00 },
        .tr_corner = { .r = 0x00, .g = 0x00, .b = 0xFF },
        .bl_corner = { .r = 0x69, .g = 0x3B, .b = 0x58 },
        .br_corner = { .r = 0xFF, .g = 0x00, .b = 0x00 }
    },
    {
        .tl_corner = { .r = 0x00, .g = 0x00, .b = 0xFF },
        .tr_corner = { .r = 0x69, .g = 0x3B, .b = 0x58 },
        .bl_corner = { .r = 0xFF, .g = 0x00, .b = 0x00 },
        .br_corner = { .r = 0x00, .g = 0xFF, .b = 0x00 }
    },
    {
        .tl_corner = { .r = 0x69, .g = 0x3B, .b = 0x58 },
        .tr_corner = { .r = 0xFF, .g = 0x00, .b = 0x00 },
        .bl_corner = { .r = 0x00, .g = 0xFF, .b = 0x00 },
        .br_corner = { .r = 0x00, .g = 0x00, .b = 0xFF }
    },
};
```
