#ifndef RC_NO_REPEATING_DIGITS
#define RC_NO_REPEATING_DIGITS

#include <stdint.h>

// Input: unsigned int denoting base. Output: Printing of all numbers with non-repeating digits.
uint64_t rc_all_no_repeating_digits(uint8_t base, uint64_t start, uint64_t num_of_iters, uint64_t last_num);

#endif
