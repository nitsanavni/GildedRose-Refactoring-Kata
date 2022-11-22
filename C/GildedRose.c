#define _DEFAULT_SOURCE

#include <string.h>
#include <stdbool.h>

#undef _DEFAULT_SOURCE

#include "GildedRose.h"

void a_true_b_true() {}

void a_true_b_false() {}

void a_false_b_true() {}

void a_false_b_false() {}

void lift_up_conditional(bool a, bool b) {
    if (a) {
        if (b) {
            a_true_b_true();
        } else {
            a_true_b_false();
        }
    } else {
        if (b) {
            a_false_b_true();
        } else {
            a_false_b_false();
        }
    }
}

Item *
init_item(Item *item, const char *name, int sellIn, int quality) {
    item->sellIn = sellIn;
    item->quality = quality;
    item->name = strdup(name);

    return item;
}

void
update_quality(Item items[], int size) {
    int i;

    for (i = 0; i < size; i++) {
        if (strcmp(items[i].name, "Aged Brie") &&
            strcmp(items[i].name, "Backstage passes to a TAFKAL80ETC concert")) {
            if (items[i].quality > 0) {
                if (strcmp(items[i].name, "Sulfuras, Hand of Ragnaros")) {
                    items[i].quality = items[i].quality - 1;
                }
            }
        } else {
            if (items[i].quality < 50) {
                items[i].quality = items[i].quality + 1;

                if (!strcmp(items[i].name, "Backstage passes to a TAFKAL80ETC concert")) {
                    if (items[i].sellIn < 11) {
                        if (items[i].quality < 50) {
                            items[i].quality = items[i].quality + 1;
                        }
                    }

                    if (items[i].sellIn < 6) {
                        if (items[i].quality < 50) {
                            items[i].quality = items[i].quality + 1;
                        }
                    }
                }
            }
        }

        if (strcmp(items[i].name, "Sulfuras, Hand of Ragnaros")) {
            items[i].sellIn = items[i].sellIn - 1;
        }

        if (items[i].sellIn < 0) {
            if (strcmp(items[i].name, "Aged Brie")) {
                if (strcmp(items[i].name, "Backstage passes to a TAFKAL80ETC concert")) {
                    if (items[i].quality > 0) {
                        if (strcmp(items[i].name, "Sulfuras, Hand of Ragnaros")) {
                            items[i].quality = items[i].quality - 1;
                        }
                    }
                } else {
                    items[i].quality = items[i].quality - items[i].quality;
                }
            } else {
                if (items[i].quality < 50) {
                    items[i].quality = items[i].quality + 1;
                }
            }
        }
    }
}
