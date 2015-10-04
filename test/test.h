#ifndef __TEST_H__
#define __TEST_H__

#ifndef __AVR__

#include <stdio.h>

#define BASH_RED   "\e[0;31m"
#define BASH_GREEN "\e[0;32m"
#define BASH_RESET "\e[0m"

#define PASSED BASH_GREEN "passed" BASH_RESET
#define FAILED BASH_RED   "failed" BASH_RESET

#else

#endif

int assert_rgb(colour_t c, colour_byte_t r, colour_byte_t g, colour_byte_t b)
{
  if (c.red == r && c.green == g && c.blue == b) {
    return 1;
  }

#ifndef __AVR__
  fprintf(stderr, "assert_rgb(%d, %d, %d) " FAILED " for rgb(%d, %d, %d)\n", r, g, b, c.red, c.green, c.blue);
#endif
  return 0;
}

int assert_hsl(colour_t c, colour_decimal_t h, colour_decimal_t s, colour_decimal_t l)
{

  colour_decimal_t hue, saturation, lightness;
  colour_to_hsl(c, &hue, &saturation, &lightness);

  if (round(hue) == h && round(saturation) == s && round(lightness) == l) {
    return 1;
  }

#ifndef __AVR__
  fprintf(stderr, "assert_hsl(%.2f, %.2f, %.2f) " FAILED " for hsl(%.2f, %.2f, %.2f)\n", h, s, l, hue, saturation, lightness);
#endif
  return 0;
}

#endif
