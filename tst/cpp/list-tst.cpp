// list-tst.cpp

#include "src/list/cpp/list.hpp"
#include "src/list/cpp/list-linked.hpp"
#include "tst/tst.h"

#define TINY   1
#define SMALL  10
#define MEDIUM 100
#define LARGE  1000
#define GIANT  10000

class integer_comparator_t : public comparator_t {
public:
  static integer_comparator_t& instance()
  {
    static integer_comparator_t instance;
    return instance;
  }

  int equals(const void *arg0, const void *arg1)
  {
    return (*(int *)arg0 == *(int *)arg1);
  }
};

static void run_list_test(list_t *list);

int main(int argc, char *argv[])
{
  list_t *list = new list_linked_t();
  run_list_test(list);
  delete list;
  return 0;
}

static void run_list_test(list_t *list)
{
  size_t size = list->size();
  tst_expect_equals(size, 0);

  int data0 = TINY;
  list->addback(&data0);

  size = list->size();
  tst_expect_equals(size, 1);

  const void *data = list->get(0);
  tst_expect(data);
  tst_expect_equals(*(int *)data, TINY);

  int data1 = SMALL;
  list->addback(&data1);

  size = list->size();
  tst_expect_equals(size, 2);

  data = list->get(0);
  tst_expect(data);
  tst_expect_equals(*(int *)data, TINY);
  data = list->get(1);
  tst_expect(data);
  tst_expect_equals(*(int *)data, SMALL);

  int data2 = MEDIUM;
  list->addback(&data2);
  int data3 = LARGE;
  list->addback(&data3);

  size = list->size();
  tst_expect_equals(size, 4);

  data = list->get(0);
  tst_expect_equals(*(int *)data, TINY);
  data = list->get(1);
  tst_expect_equals(*(int *)data, SMALL);
  data = list->get(2);
  tst_expect_equals(*(int *)data, MEDIUM);
  data = list->get(3);
  tst_expect_equals(*(int *)data, LARGE);

  int data4 = GIANT;
  list->addfront(&data4);

  size = list->size();
  tst_expect_equals(size, 5);

  data = list->get(0);
  tst_expect_equals(*(int *)data, GIANT);
  data = list->get(1);
  tst_expect_equals(*(int *)data, TINY);
  data = list->get(2);
  tst_expect_equals(*(int *)data, SMALL);
  data = list->get(3);
  tst_expect_equals(*(int *)data, MEDIUM);
  data = list->get(4);
  tst_expect_equals(*(int *)data, LARGE);

  data = list->find(&data0, integer_comparator_t::instance());
  tst_expect(data);
  tst_expect_equals(data0, *(int *)data);

  int dataX = -1;
  data = list->find(&dataX, integer_comparator_t::instance());
  tst_expect(!data);

  data = list->remove(&dataX, integer_comparator_t::instance());
  tst_expect(!data);

  data = list->remove(&data0, integer_comparator_t::instance());
  tst_expect(data);
  tst_expect_equals(data0, *(int *)data);

  size = list->size();
  tst_expect_equals(size, 4);

  data = list->get(0);
  tst_expect_equals(*(int *)data, GIANT);
  data = list->get(1);
  tst_expect_equals(*(int *)data, SMALL);
  data = list->get(2);
  tst_expect_equals(*(int *)data, MEDIUM);
  data = list->get(3);
  tst_expect_equals(*(int *)data, LARGE);

  list->addback(&data0);

  size = list->size();
  tst_expect_equals(size, 5);

  data = list->get(0);
  tst_expect_equals(*(int *)data, GIANT);
  data = list->get(1);
  tst_expect_equals(*(int *)data, SMALL);
  data = list->get(2);
  tst_expect_equals(*(int *)data, MEDIUM);
  data = list->get(3);
  tst_expect_equals(*(int *)data, LARGE);
  data = list->get(4);
  tst_expect_equals(*(int *)data, TINY);

  list->reverse();
  data = list->get(0);
  tst_expect_equals(*(int *)data, TINY);
  data = list->get(1);
  tst_expect_equals(*(int *)data, LARGE);
  data = list->get(2);
  tst_expect_equals(*(int *)data, MEDIUM);
  data = list->get(3);
  tst_expect_equals(*(int *)data, SMALL);
  data = list->get(4);
  tst_expect_equals(*(int *)data, GIANT);
}
