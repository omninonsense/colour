#include "colour.h"
#include "test.h"

#define TEST_NAME "HSL to RGB"

int main(int argc, char const *argv[]) {

  Colour losos = colour_hsl(10, 80, 60);

  if (assert_rgb(losos, 235, 99, 71)) {
    #ifndef __AVR__
      printf("%s %s\n", PASSED, TEST_NAME);
    #endif
      } else {
    #ifndef __AVR__
      printf("%s %s\n", FAILED, TEST_NAME);
    #endif
  }

  return 0;
}
