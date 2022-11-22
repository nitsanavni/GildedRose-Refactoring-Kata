#define _DEFAULT_SOURCE

#include <string.h>
#include <stdbool.h>
#include "GildedRose.h"

#undef _DEFAULT_SOURCE


void update_item(Item *item);

void update_brie(Item *item);

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
        update_item(items + i);
    }
}

bool is_brie(const Item *item) { return !strcmp(item->name, "Aged Brie"); }

void update_item(Item *item) {
    int not_backstage = strcmp(item->name,
                               "Backstage passes to a TAFKAL80ETC concert");
    int not_sulfuras = strcmp(item->name, "Sulfuras, Hand of Ragnaros");

    if (is_brie(item)) {
        update_brie(item);
    } else {
        if (not_backstage != 0) {
            if (item->quality > 0) {
                if (not_sulfuras) {
                    item->quality = item->quality - 1;
                }
            }
        } else {
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
        }

        if (not_sulfuras) {
            item->sellIn = item->sellIn - 1;
        }

        if (item->sellIn < 0) {
            if (not_backstage) {
                if (item->quality > 0) {
                    if (not_sulfuras) {
                        item->quality = item->quality - 1;
                    }
                }
            } else {
                item->quality = item->quality - item->quality;
            }
        }
    }
}

void update_brie(Item *item) {
    if (item->quality < 50) {
        item->quality = item->quality + 1;
    }

    item->sellIn = item->sellIn - 1;

    if (item->sellIn < 0) {
        if (item->quality < 50) {
            item->quality = item->quality + 1;
        }
    }
}
