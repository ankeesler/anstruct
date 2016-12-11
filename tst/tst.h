/* tst.h */

#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stddef.h>

#ifdef TST_VERBOSE
  #define note(n) \
    do { \
      printf("test '%s' %s\n", __FILE__, (n)); \
      fflush(stdout); \
    } while (0);
  #define print_status(pass, format, ...) \
    do { \
      printf("  line %d %s: '" format "'\n", __LINE__, ((pass) ? "PASSED" : "FAILED"), __VA_ARGS__); \
      fflush(stdout); \
    } while (0);
#else
  #define note(n)
  #define print_status(pass, format, ...)
#endif

#define tst_start() note("START")
#define tst_end() note("DONE")
#define tst_expect(cond) \
  do { \
    print_status(cond, "%s", #cond); \
    assert(cond); \
  } while (0); 
#define tst_expect_memequals(mem0, mem1, size) \
  do { \
    int pass = (memcmp((mem0), (mem1), (size)) == 0); \
    print_status(pass, "%s == %s", #mem0, #mem1); \
    assert(pass); \
  } while (0); 
#define tst_expect_equals(arg0, arg1) \
  do { \
    int pass = (arg0 == arg1); \
    print_status(pass, "%ld == %ld", (long)arg0, (long)arg1); \
    assert(pass); \
  } while (0);
