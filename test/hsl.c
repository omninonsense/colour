#include "colour.h"
#include "test.h"

#define TEST_NAME "HSL"

int main(int argc, char const *argv[]) {

  colour_t losos = colour_css("#EA6146");

  if (assert_hsl(losos, 10, 80, 60)) {
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
