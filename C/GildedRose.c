#include <string.h>
#include <stdio.h>

#include "GildedRose.h"

void update_item_quality(Item *item);

void update_brie(Item *item);

void update_backstage_passes(Item *item);

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
    for (int i = 0; i < size; i++) {
        update_item_quality(items + i);
    }
}

void update_item_quality(Item *item) {
    int sulfuras = !strcmp(item->name, "Sulfuras, Hand of Ragnaros");
    int brie = !strcmp(item->name, "Aged Brie");
    int backstage_passes = !strcmp(item->name, "Backstage passes to a TAFKAL80ETC concert");

    if (sulfuras) {
        return;
    }

    if (brie) {
        update_brie(item);
        return;
    }

    if (backstage_passes) {
        update_backstage_passes(item);
        return;
    }

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

void update_backstage_passes(Item *item) {
    item->sellIn = item->sellIn - 1;

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

    if (item->sellIn < 0) {
        item->quality = 0;
    }
}

void update_brie(Item *item) {
    item->sellIn = item->sellIn - 1;

    if (item->quality >= 50) {
        return;
    }

    if (item->sellIn >= 0) {
        item->quality++;
    } else {
        item->quality += 2;
    }
}
