#include "../src/nrdg.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define HIGHEST_BASE 16
#define BUFFER_SIZE (HIGHEST_BASE + 1)

// Amount of non-repeating-digit numbers are hard-coded.
// Input: The remainder from 0 to 15
// Output: The character from '0' to '9' and from 'A' to 'F'
static inline char valtochar(const uint8_t rem) {
  assert(rem < 16 && "Remainder is at least 16!");
  return (char)(rem + '0' + (7 * (rem > 9)));
}

// Converts the val provided to the base.
// Input: A value to convert, a base, and the 17-byte buffer to be written in reverse
// Output: A pointer to the last char written, or the start of the string
static inline char * valtostr(uint64_t val, char rdst[static 2], uint8_t base) {
  assert((base <= HIGHEST_BASE) && "uint64 doesn't support bases greater than 16!");
  assert(val && "Zero is never counted!");
  assert(*(rdst + 1) == 0 && "Byte after rdst is not null! This pointer it not the end!");
  for (uint8_t counter = 0; val && counter < (BUFFER_SIZE - 1); counter++, rdst--, val /= base) {
    *rdst = valtochar(val % base);
  }
  if (val) {
    *rdst = valtochar(val % base); // 16th iteration, rdst is never decremented, staying on first byte in buffer
  } else {
    rdst++;
  }
  return rdst;
}

// Simple ** function with base and exponent, faster than pow
// Input: A base and an exponent, both up to 255
// Output: The result
static inline uint64_t powi(const uint8_t base, const uint8_t exp) {
  if (exp == 0) {
    return 1;
  }
  uint64_t res = base;
  for (uint8_t i = 1; i < exp; i++) {
    res *= base;
  }
  return res;
}

// The "heart" of this program. Finds the first repeat, then increments the smallest digit of that repeat.
// Input: Pointer to a val to mutate, and a base
// Output: Boolean as to if the value still has repeating digits, nice for while-loops
static inline bool increment_repeating_digit(uint64_t * const val_ptr, const uint8_t base) {
  uint64_t val_copy = (*val_ptr) + 1;
  uint8_t read_order[HIGHEST_BASE];
  uint32_t bitmap = 0;
  for (uint8_t read_size = 0; val_copy && read_size <= base; read_size++) {
    const uint8_t digit = val_copy % base;
    const uint32_t reader = 1U << digit;
    if (bitmap & reader) {
      assert(read_size && "There is no track history despite history in bitmap!");
      for (uint8_t j = 0; j < read_size; j++) {
        if (read_order[j] == digit) {
          (*val_ptr) += powi(base, j);
          return true;
        }
      }
      assert(false && "Track history doesn't match what just happened!");
    }
    read_order[read_size] = digit;
    bitmap |= reader;
    val_copy /= base;
  }
  (*val_ptr)++; // Because copy is destroyed, increment val directly
  return false;
}

/*
1.
If there is a conflict, add 1 to lowest place-value digit
65250 -> 65260 -> 65270
2.
If there is a descending order from 9 to the first digit,
round to the place after the 9, increment that place if it conflicts with others on left,
then place smallest available digits going right
2439876 -> 2440000 -> 2450000  -> 2450136
X.
If amount of digits = value of base, permutations thing?
Something faster than increment lowest to-repeat place-value?
987654301
*/

// The "ribcage" of this program. Returns the next* number of no-repeating-digits
// Input: An unsigned 64 bit number and a base
// Output: The next* number of no-repeating-digits
// *Always works if input also has no repeating digits, and most of the time for numbers with repeating digits
static inline uint64_t next_nrd_number(uint64_t curr, const uint8_t base) {
  assert((base <= HIGHEST_BASE) && "uint64 doesn't support bases greater than 16!");
  assert(curr && "Zero is never counted!");
  while (increment_repeating_digit(&curr, base)) {
  }
  return curr;
}

uint64_t nrdg_all_no_repeating_digits(const uint8_t base,
                                      uint64_t start,
                                      const uint64_t num_of_iters,
                                      const uint64_t last_num) {
  if (base == 0) {
    (void)puts("A base of zero outputs nothing!");
    return 0;
  }
  if (base == 1) {
    (void)puts("1");
    return 1;
  }
  if (base > HIGHEST_BASE) {
    (void)puts("This program doesn't support bases greater than 16!");
    return 0;
  }

  while (increment_repeating_digit(&start, base)) {
  }

  uint64_t num_of_vals = 0;
  char to_print[BUFFER_SIZE];
  char * const end_ptr = to_print + HIGHEST_BASE - 1;
  to_print[HIGHEST_BASE] = 0;
  uint64_t cur = start;
  for (uint64_t i = 0; i < num_of_iters && cur < last_num; cur = next_nrd_number(cur, base), num_of_vals++, i++) {
    puts(valtostr(cur, end_ptr, base));
  }
  if (num_of_vals < num_of_iters) {
    puts(valtostr(cur, end_ptr, base));
    num_of_vals++;
  }
  return num_of_vals;
}
