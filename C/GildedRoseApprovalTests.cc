#define APPROVALS_CPPUTEST_EXISTING_MAIN

#include "ApprovalTests.hpp"

using namespace ApprovalTests;

#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>

#include <vector>
#include <sstream>

extern "C" {
#include "GildedRose.h"
}

TEST_GROUP(TestGildedRoseGroup) {
    void setup() {
    }

    void teardown() {
    }
};

TEST(TestGildedRoseGroup, TestUsingApprovals) {
    const int n = 9;
    Item items[n];
    int last = 0;

    init_item(items + last++, "+5 Dexterity Vest", 10, 20);
    init_item(items + last++, "Aged Brie", 2, 0);
    init_item(items + last++, "Elixir of the Mongoose", 5, 7);
    init_item(items + last++, "Sulfuras, Hand of Ragnaros", 0, 80);
    init_item(items + last++, "Sulfuras, Hand of Ragnaros", -1, 80);
    init_item(items + last++, "Backstage passes to a TAFKAL80ETC concert", 15, 20);
    init_item(items + last++, "Backstage passes to a TAFKAL80ETC concert", 10, 49);
    init_item(items + last++, "Backstage passes to a TAFKAL80ETC concert", 5, 49);
    // this Conjured item doesn't yet work properly
    init_item(items + last++, "Conjured Mana Cake", 3, 6);

    std::stringstream s;

    void (*printItem)(const Item &, std::ostream &) = [](const Item &item, std::ostream &os) {
        os << "name: " << item.name << ", "
           << "quality: " << item.quality << ", "
           << "sellIn: " << item.sellIn;
    };

    for (int day = 0; day < 30; ++day) {
        s << "day " << day << "\n";
        for (auto item : items) {
            printItem(item, s);
            s << "\n";
        }
        s << "\n\n";
        update_quality(items, n);
    }

    Approvals::verify(s.str());
}

int
main(int ac, char **av) {
    ApprovalTests::initializeApprovalTestsForCppUTest();
    const std::shared_ptr<GenericDiffReporter> &code = CustomReporter::create("code",
                                                                              "-d {Received} {Approved}");
    auto disposer = Approvals::useAsDefaultReporter(code);

    auto result = CommandLineTestRunner::RunAllTests(ac, av);

    TestRegistry::getCurrentRegistry()->resetPlugins();

    return result;
}
