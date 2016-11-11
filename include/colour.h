/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 - 2016 Nino Miletich
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

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} Colour;

Colour colour_rgb(uint8_t red, uint8_t green, uint8_t blue);
Colour colour_css(const char* css);
Colour colour_hsl(double hue, double saturation, double lightness);

/* Conversion functions */
void colour_to_hsl(Colour colour, double *hue, double *saturation, double *lightness);

/* Colour functions */
Colour colour_mix(Colour colour1, Colour colour2, double weight);

// Helper Functions
uint8_t _hex_to_int(char c);
double _hue_to_rgb(double p, double q, double t);
#endif
