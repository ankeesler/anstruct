// list-tst.cpp

#include "src/list/cpp/list.hpp"
#include "src/list/cpp/list-linked.hpp"
#include "tst/tst.h"

#define TINY   1
#define SMALL  10
#define MEDIUM 100
#define LARGE  1000
#define GIANT  10000

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
}
