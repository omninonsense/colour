#include "colour.h"
#include "test.h"

#define TEST_NAME "CSS"

int main(int argc, char const *argv[]) {

  colour_t losos = colour_css("#EA6146");
  colour_t orange = colour_css("#FA3");

  if (assert_rgb(losos, 234, 97, 70) && assert_rgb(orange, 255, 170, 51)) {
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
