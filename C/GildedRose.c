#include <string.h>
#include <stdio.h>

#include "GildedRose.h"

void update_item(Item *item);

Item *
init_item(Item *item, const char *name, int sellIn, int quality) {
    item->sellIn = sellIn;
    item->quality = quality;
    item->name = strdup(name);

    return item;
}

extern char *
print_item(char *buffer, Item *item) {
    sprintf(buffer, "%s, %d, %d", item->name, item->sellIn, item->quality);
}

void
update_quality(Item items[], int size) {
    int i;

    for (i = 0; i < size; i++) {
        update_item(items+i);
    }
}

void update_item(Item *item) {
    int brie = !strcmp(item->name, "Aged Brie");
    int backstage_passes = !strcmp(item->name, "Backstage passes to a TAFKAL80ETC concert");
    int sulfuras = !strcmp(item->name, "Sulfuras, Hand of Ragnaros");

    if (brie || backstage_passes) {
        if (item->quality < 50) {
            item->quality = item->quality + 1;

            if (backstage_passes) {
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
        }
    } else {
        if (item->quality > 0) {
            if (sulfuras) {}
            else {
                item->quality = item->quality - 1;
            }
        }
    }

    if (!sulfuras) {
        item->sellIn = item->sellIn - 1;
    }

    if (item->sellIn < 0) {
        if (brie) {
            if (item->quality < 50) {
                item->quality = item->quality + 1;
            }
        } else {
            if (backstage_passes) {
                item->quality = item->quality - item->quality;
            } else {
                if (item->quality > 0) {
                    if (strcmp(item->name, "Sulfuras, Hand of Ragnaros")) {
                        item->quality = item->quality - 1;
                    }
                }
            }
        }
    }
}
