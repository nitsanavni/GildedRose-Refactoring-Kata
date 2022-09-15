#include <string.h>
#include <stdio.h>

#include "GildedRose.h"

void update_item_quality(Item *item);

void update_brie(Item *item);

void update_backstage_passes(Item *item);

void clip_quality(Item *item);

int backstage_passes_qd(int sellIn);

void default_update_item(Item *item);

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
        // do nothing
    } else if (brie) {
        update_brie(item);
    } else if (backstage_passes) {
        update_backstage_passes(item);
    } else {
        default_update_item(item);
    }
}

void default_update_item(Item *item) {
    item->sellIn = item->sellIn - 1;

    int decBy = item->sellIn < 0 ? 2 : 1;

    item->quality -= decBy;

    clip_quality(item);
}

void update_backstage_passes(Item *item) {
    item->sellIn = item->sellIn - 1;

    if (item->sellIn < 0) {
        item->quality = 0;
        return;
    }

    item->quality += backstage_passes_qd(item->sellIn);

    clip_quality(item);

}

int backstage_passes_qd(int sellIn) {
    return (sellIn < 5) ? 3 :
           (sellIn < 10) ? 2 :
           1;
}

void clip_quality(Item *item) {
    if (item->quality > 50) {
        item->quality = 50;
    } else if (item->quality < 0) {
        item->quality = 0;
    }
}

void update_brie(Item *item) {
    item->sellIn = item->sellIn - 1;

    // this looks like a bug... brie might go above 50 like this
    if (item->quality >= 50) {
        return;
    }

    if (item->sellIn >= 0) {
        item->quality++;
    } else {
        item->quality += 2;
    }
}
