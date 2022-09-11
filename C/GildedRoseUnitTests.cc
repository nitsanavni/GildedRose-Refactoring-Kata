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
  Approvals::verify(42, Options(*CustomReporter::createForegroundReporter("code", "-d {Received} {Approved}")));
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
  auto gpReporter = CustomReporter::createForegroundReporter("code", "-d");
  // Approvals::useAsDefaultReporter(std::make_shared<DiffReporter>(gpReporter));

  // does this line cause a failure?
  // TestRegistry::getCurrentRegistry()->resetPlugins();

  return CommandLineTestRunner::RunAllTests(ac, av);
}
