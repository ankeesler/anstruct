// set-tst.cpp

#include "src/set/cpp/set.hpp"
#include "src/set/cpp/set-tree.hpp"
#include "tst/tst.h"

#define TINY   1
#define SMALL  10
#define MEDIUM 100
#define LARGE  1000
#define GIANT  10000

static void run_set_test(set_t *set);

int main(int argc, char *argv[])
{
  tst_start();

  set_t *set = new set_tree_t(integer_comparator_t::instance());
  run_set_test(set);
  delete set;

  tst_end();

  return 0;
}

static void run_set_test(set_t *set)
{
  size_t size = set->size();
  tst_expect_equals(size, 0);

  int dataMedium = MEDIUM;
  bool contains = set->contains(&dataMedium);
  tst_expect(!contains);
  bool added = set->add(&dataMedium);
  tst_expect(added);
  contains = set->contains(&dataMedium);
  tst_expect(contains);

  size = set->size();
  tst_expect_equals(size, 1);

  added = set->add(&dataMedium);
  tst_expect(!added);

  int dataSmall = SMALL;
  added = set->add(&dataSmall);
  tst_expect(added);

  size = set->size();
  tst_expect_equals(size, 2);

  int dataLarge = LARGE;
  added = set->add(&dataLarge);
  tst_expect(added);

  size = set->size();
  tst_expect_equals(size, 3);

  int dataTiny = TINY;
  added = set->add(&dataTiny);
  tst_expect(added);

  size = set->size();
  tst_expect_equals(size, 4);

  added = set->add(&dataLarge);
  tst_expect(!added);

  contains = set->contains(&dataTiny);
  tst_expect(contains);
  contains = set->contains(&dataSmall);
  tst_expect(contains);
  contains = set->contains(&dataMedium);
  tst_expect(contains);
  contains = set->contains(&dataLarge);
  tst_expect(contains);
}
