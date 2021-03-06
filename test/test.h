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

int assert_rgb(Colour c, uint8_t r, uint8_t g, uint8_t b)
{
  if (c.red == r && c.green == g && c.blue == b) {
    return 1;
  }

#ifndef __AVR__
  fprintf(stderr, "assert_rgb(%d, %d, %d) " FAILED " for rgb(%d, %d, %d)\n", r, g, b, c.red, c.green, c.blue);
#endif
  return 0;
}

char* Colouro_css(Colour c, char* s) // s must be at least `char[8]`
{
  sprintf(s, "#%02x%02x%02x", c.red, c.green, c.blue);
  return s;
}

int assert_hsl(Colour c, double h, double s, double l)
{

  double hue, saturation, lightness;
  Colouro_hsl(c, &hue, &saturation, &lightness);

  hue        = COLOUR_ROUND(hue);
  saturation = COLOUR_ROUND(saturation);
  lightness  = COLOUR_ROUND(lightness);

  if (hue == h && saturation == s && lightness == l) {
    return 1;
  }

#ifndef __AVR__
  fprintf(stderr, "assert_hsl(%.2f, %.2f, %.2f) " FAILED " for hsl(%.2f, %.2f, %.2f)\n", h, s, l, hue, saturation, lightness);
#endif
  return 0;
}

#endif
