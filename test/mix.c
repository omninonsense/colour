#include "colour.h"
#include "test.h"

#define TEST_NAME "mix"

int main(int argc, char const *argv[]) {

  //mix(#EA6146, #009150,
  colour_t poop = colour_mix(colour_css("#EA6146"), colour_css("#009150"), 60);

  if (assert_rgb(poop, 140, 116, 74)) {
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
