#include "../src/nrd.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define HIGHEST_BASE 16
#define BUFFER_SIZE (HIGHEST_BASE + 1)

static inline uint64_t last_nre(const uint8_t base) {
  assert(base > 3 && "Someone tampered with the switch statement in `all_no_repeating_digits`!");
  assert((base <= HIGHEST_BASE) && "uint64 doesn't support bases greater than 16!");
  switch (base) {
    case 0:
    case 1:
    case 2:
      return base;
    case 3:
      return 21;
    case 4:
      return 228;
    case 5:
      return 2930;
    case 6:
      return 44790;
    case 7:
      return 800667;
    case 8:
      return 16434824;
    case 9:
      return 381367044;
    case 10:
      return 9876543210;
    case 11:
      return 282458553905;
    case 12:
      return 8842413667692;
    case 13:
      return 300771807240918;
    case 14:
      return 11046255305880158;
    case 15:
      return 435659737878916215;
    case 16:
      return 0xfedcba9876543210;
    default:
      return 0;
  }
}

static inline char valtochar(const uint8_t rem) {
  assert(rem < 16 && "Remainder is at least 16!");
  return (char)(rem + '0' + (7 * (rem > 9)));
}

static inline char * valtostr(uint64_t val, char rdst[static 2], uint8_t base) {
  assert(base > 3 && "Someone tampered with the switch statement in `all_no_repeating_digits`!");
  assert((base <= HIGHEST_BASE) && "uint64 doesn't support bases greater than 16!");
  assert(val && "Zero is never counted!");
  assert(*(rdst + 1) == 0 && "Byte after rdst is not null! This pointer it not the end!");
  for (uint8_t counter = 0; counter < (BUFFER_SIZE - 1) && val; counter++, rdst--, val /= base) {
    *rdst = valtochar(val % base);
  }
  if (val) {
    *rdst = valtochar(val % base); // 16th iteration, rdst is never decremented, staying on first byte in buffer
  } else {
    rdst++;
  }
  return rdst;
}

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

// 1. Add one
// 2. If there is a conflict, add 1 to lowest place-value digit
static inline bool increment_repeating_digit(uint64_t * const val_ptr, const uint8_t base) {
  uint8_t read_order[HIGHEST_BASE];
  uint32_t bitmap = 0;
  uint64_t val_copy = (*val_ptr) + 1;
  for (uint8_t read_size = 0; val_copy && read_size < HIGHEST_BASE; read_size++) {
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

static inline uint64_t next_nrd_number(uint64_t curr, const uint8_t base) {
  assert(base > 3 && "Someone tampered with the switch statement in `all_no_repeating_digits`!");
  assert((base <= HIGHEST_BASE) && "uint64 doesn't support bases greater than 16!");
  assert(curr && "Zero is never counted!");
  if (curr >= last_nre(base)) {
    return -1ULL;
  }
  while (increment_repeating_digit(&curr, base)) {
  }
  return curr;
}

// Input: unsigned int denoting base.
// Output: Printing of all numbers with non-repeating digits + value representing amount of numbers printed.
uint64_t rc_all_no_repeating_digits(const uint8_t base) {
  if (base == 0) {
    puts("A base of zero or lower will not work!");
    return 0;
  }
  if (base == 1) {
    puts("1");
    return 1;
  }
  if (base == 2) {
    puts("1\n10");
    return 2;
  }
  if (base == 3) {
    puts("1\n2\n10\n12\n20\n21\n102\n120\n201\n210");
    return 10;
  }
  if (base > HIGHEST_BASE) {
    puts("This program doesn't support bases greater than 16!");
    return 0;
  }
  assert((base <= HIGHEST_BASE) && "uint64 doesn't support bases greater than 16!");
  assert(base > 3 && "Someone tampered with the switch statement above!");
  uint64_t number_of_values = 0;
  char to_print[BUFFER_SIZE];
  to_print[BUFFER_SIZE - 1] = 0;
  char * const end_ptr = to_print + HIGHEST_BASE - 1;
  for (uint64_t i = 1; i != -1ULL; i = next_nrd_number(i, base), number_of_values++) {
    puts(valtostr(i, end_ptr, base));
  }
  return number_of_values;
}
