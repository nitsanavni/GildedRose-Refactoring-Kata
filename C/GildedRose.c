#include <string.h>

#include "GildedRose.h"

void update_item(Item *item);

Item *
init_item(Item *item, const char *name, int sellIn, int quality) {
    item->sellIn = sellIn;
    item->quality = quality;
    item->name = strdup(name);

    return item;
}

void
update_quality(Item items[], int size) {
    for (int i = 0; i < size; i++) {
        Item *item = items + i;
        update_item(item);
    }
}

void update_item(Item *item) {
    int brie = !strcmp(item->name, "Aged Brie");
    int backstage = !strcmp(item->name, "Backstage passes to a TAFKAL80ETC concert");
    int sulfuras = !strcmp(item->name, "Sulfuras, Hand of Ragnaros");

    if (brie) {
        if (item->quality < 50) {
            item->quality = item->quality + 1;
        }

        item->sellIn = item->sellIn - 1;

        if (item->sellIn < 0) {
            if (item->quality < 50) {
                item->quality = item->quality + 1;
            }
        }
    } else if (backstage) {
        if (item->quality < 50) {
            item->quality = item->quality + 1;

            if (item->sellIn < 11) {
                if (item->quality < 50) {
                    item->quality = item->quality + 1;
                }
            }
            if (item->sellIn < 6) {
                if (item->quality < 50) {
                    item->quality = item->quality + 1;
                }
            }
        }

        item->sellIn = item->sellIn - 1;

        if (item->sellIn < 0) {
            item->quality = item->quality - item->quality;
        }
    } else if (sulfuras) {
        // do nothing
    } else {
        if (item->quality > 0) {
            item->quality = item->quality - 1;
        }

        item->sellIn = item->sellIn - 1;

        if (item->sellIn < 0) {
            if (item->quality > 0) {
                item->quality = item->quality - 1;
            }
        }
    }

}

