#include "colour.h"

/* Creates a colour from RGB values */
colour_t colour_rgb(colour_byte_t red, colour_byte_t green, colour_byte_t blue)
{
  colour_t colour;
  colour.red   = red;
  colour.green = green;
  colour.blue  = blue;

  return colour;
}

colour_t colour_css(const char* css)
{
  const char *c = css;
  size_t len;
  colour_t colour;

  // Check if valid CSS color (must begin with `#`)
  if (*c == '#')
    ++c;
  else {
    goto invalid_colour;
  }

  /**
   * CSS colours can either be `#RRGGBB` or the shorthand version `#RGB` which
   * expanded to `#RRGGBB`.
   */
  len = strlen(c);
  if (len != 3 && len != 6) {
    goto invalid_colour;
  }


  if (len == 6) {
    colour.red    = _base16c_to_byte(*c++) * 16;
    colour.red   += _base16c_to_byte(*c++);

    colour.green  = _base16c_to_byte(*c++) * 16;
    colour.green += _base16c_to_byte(*c++);

    colour.blue   = _base16c_to_byte(*c++) * 16;
    colour.blue  += _base16c_to_byte(*c++);

  } else {
    colour.red   =  _base16c_to_byte(*c++) * 16;
    colour.green =  _base16c_to_byte(*c++) * 16;
    colour.blue  =  _base16c_to_byte(*c++) * 16;

    // Copy the bytes to their lower magnitude
    colour.red   += colour.red >> 4;
    colour.green += colour.green >> 4;
    colour.blue  += colour.blue >> 4;
  }

  return colour;

invalid_colour:
  return COLOUR_EMPTY;
}

/* Creates a colour from HSL values */
colour_t colour_hsl(colour_decimal_t h, colour_decimal_t s, colour_decimal_t l)
{
  colour_t colour = COLOUR_EMPTY;

  colour_decimal_t p;
  colour_decimal_t q;

  h /= 360.0;
  s /= 100.0;
  l /= 100.0;

  if (l < 0) l = 0;
  if (s < 0) s = 0;
  if (l > 1) l = 1;
  if (s > 1) s = 1;
  while (h < 0) h += 1;
  while (h > 1) h -= 1;

  if (l <= 0.5) q = l*(s+1.0);
  else q = (l+s)-(l*s);
  p = (l*2.0)-q;

  colour.red   = round(_hue_to_rgb(p, q, h + 1.0/3.0) * 255.0);
  colour.green = round(_hue_to_rgb(p, q, h          ) * 255.0);
  colour.blue  = round(_hue_to_rgb(p, q, h - 1.0/3.0) * 255.0);

  return colour;
}

/* Extract HSL values from a colour */
void colour_to_hsl(colour_t colour, colour_decimal_t *hue, colour_decimal_t *saturation, colour_decimal_t *lightness)
{

  double r = colour.red / 255.0;
  double g = colour.green / 255.0;
  double b = colour.blue / 255.0;

  double max = MAX(r, MAX(g, b));
  double min = MIN(r, MIN(g, b));
  double del = max - min;

  double h = 0;
  double s = 0;
  double l = (max + min) / 2.0;

  if (max == min) {
    h = s = 0; // no chroma
  } else {
    if (l < 0.5) s = del / (max + min);
    else         s = del / (2.0 - max - min);

    if      (r == max) h = (g - b) / del + (g < b ? 6 : 0);
    else if (g == max) h = (b - r) / del + 2;
    else if (b == max) h = (r - g) / del + 4;
  }

  *hue        = h / 6.0 * 360.0;
  *saturation = s * 100;
  *lightness  = l * 100;
}

colour_t colour_mix(colour_t colour1, colour_t colour2, colour_decimal_t weight)
{

  colour_t colour;
  colour_decimal_t p = weight / 100.0;

  colour.red   = floor(colour1.red   * p + colour2.red   * (1.0-p));
  colour.green = floor(colour1.green * p + colour2.green * (1.0-p));
  colour.blue  = floor(colour1.blue  * p + colour2.blue  * (1.0-p));

  return colour;
}


/* Helper functions */
/* Converts a Base 16 character to an integer */
uint8_t _base16c_to_byte(char c)
{
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;

  return -1;
}

/* Extract the R, G or B components from the hue */
colour_decimal_t _hue_to_rgb(colour_decimal_t p, colour_decimal_t q, colour_decimal_t t)
{
  if (t < 0) t += 1;
  if (t > 1) t -= 1;
  if (t*6.0 < 1) return p + (q - p)*t*6;
  if (t*2.0 < 1) return q;
  if (t*3.0 < 2) return p + (q - p) * (2.0/3.0 - t)*6;
  return p;
}
