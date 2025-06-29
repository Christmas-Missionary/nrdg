#ifndef RC_NO_REPEATING_DIGITS_GEN
#define RC_NO_REPEATING_DIGITS_GEN

#include <stdint.h>

// Prints all non-repeating-digit numbers within the limits of the args
// Input: unsigned int denoting base, with three limiting factors.
// Output: Printing of the numbers with non-repeating digits.
uint64_t nrdg_all_no_repeating_digits(uint8_t base, uint64_t start, uint64_t num_of_iters, uint64_t last_num);

#endif
