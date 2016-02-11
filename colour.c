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
  colour_t colour = COLOUR_EMPTY;

  // Check if valid CSS color (must begin with `#`)
  if (css[0] != '#')
    return colour;

  /**
   * CSS colours can either be `#RRGGBB` or the shorthand version `#RGB` which
   * expanded to `#RRGGBB`.
   */
  if (css[7] == 0) {
    colour.red   = _hex_to_int(*(css+1)) * 16 + _hex_to_int(*(css+2));
    colour.green = _hex_to_int(*(css+3)) * 16 + _hex_to_int(*(css+4));
    colour.blue  = _hex_to_int(*(css+5)) * 16 + _hex_to_int(*(css+6));
  } else if (css[4] == 0) {
    colour.red   =  _hex_to_int(*(css+1)) * 16;
    colour.green =  _hex_to_int(*(css+2)) * 16;
    colour.blue  =  _hex_to_int(*(css+3)) * 16;

    // Copy the bytes to their lower magnitude
    colour.red   += colour.red >> 4;
    colour.green += colour.green >> 4;
    colour.blue  += colour.blue >> 4;
  }

  return colour;
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

  colour.red   = COLOUR_ROUND(_hue_to_rgb(p, q, h + 1.0/3.0) * 255.0);
  colour.green = COLOUR_ROUND(_hue_to_rgb(p, q, h          ) * 255.0);
  colour.blue  = COLOUR_ROUND(_hue_to_rgb(p, q, h - 1.0/3.0) * 255.0);

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

  if (p < 0.0) p = 0.0;
  if (p > 1.0) p = 1.0;

  colour.red   = colour1.red   * p + colour2.red   * (1.0-p);
  colour.green = colour1.green * p + colour2.green * (1.0-p);
  colour.blue  = colour1.blue  * p + colour2.blue  * (1.0-p);

  return colour;
}

colour_matrix_t colour_matrix_new(int c, int r, uint16_t f, colour_t* m)
{
  colour_matrix_t cm;
  cm.columns = c;
  cm.rows    = r;
  cm.matrix  = m;
  cm.flags   = f;

  return cm;
}

void colour_matrix_set_pixel(colour_matrix_t self, int x, int y, colour_t c)
{
  if (x < 0 || y < 0) return;
  if (x >= self.columns || y >= self.rows) return;

  if (self.flags & COLOUR_MATRIX_ZIGZAG && y % 2)
    x = self.columns - x;

  self.matrix[_cm_addr(x, y, self.columns)] = c;
}

colour_t colour_matrix_get_pixel(colour_matrix_t self, int x, int y)
{
  if (x < 0 || y < 0) return COLOUR_BLACK;
  if (x >= self.columns || y >= self.rows) return COLOUR_BLACK;

  if (self.flags & COLOUR_MATRIX_ZIGZAG && y % 2)
    x = self.columns - x;

  return self.matrix[_cm_addr(x, y, self.columns)];
}

void set_row(colour_matrix_t self, int row, colour_t c)
{
  if (row >= self.rows || row < 0)  return;

  for (int i = 0; i < self.columns; i++)
    colour_matrix_set_pixel(self, i, row, c);
}

void set_column(colour_matrix_t self, int col, colour_t c)
{
  if (col >= self.columns || col < 0)  return;

  for (int i = 0; i < self.rows; i++)
    colour_matrix_set_pixel(self, col, i, c);
}

/* Helper functions */
/* Converts a Base 16 character to an integer */
uint8_t _hex_to_int(char c)
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

int _cm_addr(int x, int y, int c)
{
  if (x >= c) return -1;
  return c * y + x;
}

int _cm_x(int addr, int c) {
  if (c <= 0) return 0;

  return addr % c;
}

int _cm_y(int addr, int c) {
  if (c <= 0) return 0;

  return addr / c;
}
