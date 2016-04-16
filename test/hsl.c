#include "colour.h"
#include "test.h"

#define TEST_NAME "HSL"

int main(int argc, char const *argv[]) {

  Colour violet = colour_css("#7F00FF");

  if (assert_hsl(violet, 270, 100, 50)) {
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
