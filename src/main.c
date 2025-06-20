#include "nrd.h"
// #include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef CODE_CHECK
#error "I am just checking my code and do not wish for the writing of the program to disk."
#endif

int main(const int argc, const char ** argv) {
  const clock_t time = clock();
  if (argc <= 1) {
    printf("No input!\n");
    return 0;
  }
  const uint8_t base = (uint8_t)strtoull(argv[1], NULL, 10);
  if (base > 16) {
    printf("Base is too large!\n");
  }
  // silences a warning in GCC about uint64_t being unsigned long
  const unsigned long long num_of_values = rc_all_no_repeating_digits(base);
  const long double seconds = ((long double)(clock() - time)) / CLOCKS_PER_SEC;
  printf("%llu values given with a base of %d, calculated in %Lf seconds.\n", num_of_values, +base, seconds);
  return 0;
}
