#include <string.h>
#include <stdio.h>

#include "GildedRose.h"

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

        int brie = !strcmp(items[i].name, "Aged Brie");
        int backstage_passes = !strcmp(items[i].name, "Backstage passes to a TAFKAL80ETC concert");
        int sulfuras = !strcmp(items[i].name, "Sulfuras, Hand of Ragnaros");

        if (brie || backstage_passes) {
            if (items[i].quality < 50) {
                items[i].quality = items[i].quality + 1;

                if (backstage_passes) {
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
        } else {
            if (items[i].quality > 0) {
                if (sulfuras) {}
                else {
                    items[i].quality = items[i].quality - 1;
                }
            }
        }

        if (!sulfuras) {
            items[i].sellIn = items[i].sellIn - 1;
        }

        if (items[i].sellIn < 0) {
            if (brie) {
                if (items[i].quality < 50) {
                    items[i].quality = items[i].quality + 1;
                }
            } else {
                if (backstage_passes) {
                    items[i].quality = items[i].quality - items[i].quality;
                } else {
                    if (items[i].quality > 0) {
                        if (strcmp(items[i].name, "Sulfuras, Hand of Ragnaros")) {
                            items[i].quality = items[i].quality - 1;
                        }
                    }
                }
            }
        }
    }
}
