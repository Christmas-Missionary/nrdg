#include "nrdg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef CODE_CHECK
#error "I am just checking my code and do not wish for the writing of the program to disk."
#endif

// Amount of non-repeating-digit numbers are hard-coded.
// Input: The base
// Output: Number of all non-repeating-digit numbers for that base up to 16.
static inline uint64_t last_nre(const uint8_t base) {
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

#define HELP_TEST                                                                                                      \
  "\nnrdg <base (1-16)> [options]\n\nOPTIONS:\n\n"                                                                     \
  "[-v | --version]\n\nPrints the version of this program.\n\n"                                                        \
  "[-h | --help]\n\nPrints this text.\n\n"                                                                             \
  "[-s | --start] <integer with specifying base>\n\nExample: nrdg $ ./nrdg 9 --start 102345678\n\n"                    \
  "Gives a starting point as opposed to 0.\n\n"                                                                        \
  "[-f | --for] <integer up to (2 ** 64) - 1>\n\nExample: nrdg $ ./nrdg 10 -s 1260345 --for 900\n\n"                   \
  "Gives the amount of non-repeating-digit numbers to print before terminating.\n\n"                                   \
  "[-u | --until] <integer with specifying base>\n\nExample: nrdg $ ./nrdg 10 -s 10000 -u 1000000\n\n"                 \
  "Gives the last number (or its next non-repeating-digit number) before terminating."

int main(const int argc, const char ** const argv) {
  if (argc <= 1) {
    (void)puts("Hello!\nFor help, type `-h` or `--help`.");
    return 0;
  }
  uint64_t start = 0;
  uint64_t num_of_iters = -1ULL;
  for (const char ** str_ptr = argv + 1; *str_ptr != NULL; str_ptr++) {
    if (strncmp(*str_ptr, "-v", 2) == 0 || strncmp(*str_ptr, "--version", 8) == 0) {
      (void)puts("No Repeating Digits Generator\nVersion: 0.1");
      return 0;
    }
    if (strncmp(*str_ptr, "-h", 2) == 0 || strncmp(*str_ptr, "--help", 6) == 0) {
      (void)puts(HELP_TEST);
      return 0;
    }
  }
  uint8_t base = 0;
  for (const char ** str_ptr = argv + 1; *str_ptr != NULL; str_ptr++) {
    base = (uint8_t)strtoull(*str_ptr, NULL, 10);
    if (base >= 1 && base <= 16) {
      break;
    }
  }
  if (base == 0 || base > 16) {
    (void)printf("Invalid option or command.\n");
    return 0;
  }

  // The start should ideally by a number with no repeating digits.
  // Example via `next_nrd_number`, input (81227, 10) to get 81237, not 81230.
  for (const char ** str_ptr = argv + 1; *str_ptr != NULL; str_ptr++) {
    if (strncmp(*str_ptr, "-s", 2) == 0 || strncmp(*str_ptr, "--start", 7) == 0) {
      if (++str_ptr == NULL) {
        break;
      }
      const uint64_t temp = strtoull(*str_ptr, NULL, base);
      if (temp >= 0xfedcba9876543210 || temp == 0) {
        (void)printf("Invalid argument to start!\n");
        return 0;
      }
      start = temp;
      break;
    }
  }
  for (const char ** str_ptr = argv + 1; *str_ptr != NULL; str_ptr++) {
    if (strncmp(*str_ptr, "-f", 2) == 0 || strncmp(*str_ptr, "--for", 5) == 0) {
      if (++str_ptr == NULL) {
        break;
      }
      const uint64_t temp = strtoull(*str_ptr, NULL, 10);
      if (temp == 0) {
        (void)printf("Invalid argument for the amount of numbers to generate!\n");
        return 0;
      }
      num_of_iters = temp;
      break;
    }
  }
  uint64_t custom_last_num = 0;
  for (const char ** str_ptr = argv + 1; *str_ptr != NULL; str_ptr++) {
    if (strncmp(*str_ptr, "-u", 2) == 0 || strncmp(*str_ptr, "--until", 7) == 0) {
      if (++str_ptr == NULL) {
        break;
      }
      const uint64_t temp = strtoull(*str_ptr, NULL, base);
      if (temp == 0) {
        (void)printf("Invalid argument for the last number!\n");
        return 0;
      }
      custom_last_num = temp;
      break;
    }
  }
  const clock_t time = clock();
  const uint64_t num_of_values =
    nrdg_all_no_repeating_digits(base, start, num_of_iters, custom_last_num ? custom_last_num : last_nre(base));
  const long double seconds = ((long double)(clock() - time)) / CLOCKS_PER_SEC;
  (void)printf(
    "%llu value%s given with a base of %d, calculated in %Lf seconds.\n"
    "The time recorded may be inaccurate. On POSIX systems, use the `time` command for a more accurate time.\n",
    (unsigned long long)num_of_values,
    (num_of_values == 1) ? "" : "s",
    +base,
    seconds);
  return 0;
}
