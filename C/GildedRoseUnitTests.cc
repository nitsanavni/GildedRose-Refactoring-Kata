#include <cstring>
#define APPROVALS_CPPUTEST_EXISTING_MAIN
// must come before the CppUTest #includes to avoid some build errors
#include "ApprovalTests.hpp"

using namespace ApprovalTests;

#include <memory>


#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTestExt/MockSupport.h>



extern "C" {
#include "GildedRose.h"
}

TEST_GROUP(TestGildedRoseGroup)
{
  void setup() {
  }
  void teardown() {
  }
};

TEST(TestGildedRoseGroup, FirstTest)
{
    Item items[1];
    init_item(items, "Foo", 0, 0);
    update_quality(items, 1);
    STRCMP_EQUAL("fixme", items[0].name);
}

TEST(TestGildedRoseGroup, ApprovalTestsTest)
{
  Item items[1];
  
  init_item(items, "Foo", 0, 0);
  
  char before[20];
  print_item(before, items);
  
  update_quality(items, 1);

  char after[20];
  print_item(after, items);

  char all[1000];

  all[0] = 0;

  strcat(all, "before");
  strcat(all, "\n");
  strcat(all, before);
  strcat(all, "\n");
  strcat(all, "after");
  strcat(all, "\n");
  strcat(all, after);
  strcat(all, "\n");
  
  Approvals::verify(all);
}

void example()
{
    Item items[6];
    int last = 0;
    
    init_item(items + last++, "+5 Dexterity Vest", 10, 20);
    init_item(items + last++, "Aged Brie", 2, 0);
    init_item(items + last++, "Elixir of the Mongoose", 5, 7);
    init_item(items + last++, "Sulfuras, Hand of Ragnaros", 0, 80);
    init_item(items + last++, "Backstage passes to a TAFKAL80ETC concert", 15, 20);
    init_item(items + last++, "Conjured Mana Cake", 3, 6);
    update_quality(items, last);
}


int
main(int ac, char** av)
{
  ApprovalTests::initializeApprovalTestsForCppUTest();
  auto disposer = Approvals::useAsDefaultReporter(CustomReporter::createForegroundReporter("code", "-d {Received} {Approved}"));

  auto result = CommandLineTestRunner::RunAllTests(ac, av);
  
  TestRegistry::getCurrentRegistry()->resetPlugins();
  
  return result;
}
