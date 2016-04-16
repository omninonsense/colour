/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Visualia Group
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __COLOUR_H__
#define __COLOUR_H__
#include <inttypes.h>

#define COLOUR_WHITE colour_rgb(255,255,255)
#define COLOUR_BLACK colour_rgb(0,0,0)

#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef COLOUR_EMPTY
#define COLOUR_EMPTY COLOUR_BLACK
#endif

#ifndef COLOUR_ROUND
#define COLOUR_ROUND(num) ((int)((num) < 0 ? (num) - 0.5 : (num) + 0.5))
#endif

#define COLOUR_MATRIX_ZIGZAG_ODD          (1 <<  0)
#define COLOUR_MATRIX_ZIGZAG_EVEN (1 <<  1)

/* Provide a certain level of type consistency */
typedef uint8_t colour_byte_t;
typedef double  colour_decimal_t;

typedef struct {
  colour_byte_t red;
  colour_byte_t green;
  colour_byte_t blue;
} colour_t;

typedef struct {
  int    columns;
  int    rows;
  uint16_t flags;
  colour_t* matrix;
} colour_matrix_t;

colour_t colour_rgb(colour_byte_t red, colour_byte_t green, colour_byte_t blue);
colour_t colour_css(const char* css);
colour_t colour_hsl(colour_decimal_t hue, colour_decimal_t saturation, colour_decimal_t lightness);

/* Conversion functions */
void colour_to_hsl(colour_t colour, colour_decimal_t *hue, colour_decimal_t *saturation, colour_decimal_t *lightness);

/* Colour functions */
colour_t colour_mix(colour_t colour1, colour_t colour2, colour_decimal_t weight);

/* Colour Matrix functions */
colour_matrix_t colour_matrix_new(int c, int r, uint16_t f, colour_t* m);
void colour_matrix_set_pixel(colour_matrix_t self, int x, int y, colour_t c);
colour_t colour_matrix_get_pixel(colour_matrix_t self, int x, int y);
void set_row(colour_matrix_t self, int row, colour_t c);
void set_column(colour_matrix_t self, int col, colour_t c);

// Helper Functions
uint8_t _hex_to_int(char c);
colour_decimal_t _hue_to_rgb(colour_decimal_t p, colour_decimal_t q, colour_decimal_t t);
int _cm_addr(int x, int y, int c);
int _cm_x(int addr, int c);
int _cm_y(int addr, int c);
#endif
