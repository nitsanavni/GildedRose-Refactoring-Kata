#include <string.h>
#include <stdio.h>

#include "GildedRose.h"

void update_item(Item *item);

void update_brie(Item *item);

void update_backstage_passes(Item *item);

void update_sulfuras(Item *item);

void update_regular_item(Item *item);

int is_brie(const Item *item);

int is_backstage_passes(const Item *item);

int is_sulfuras(const Item *item);

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
        update_item(items + i);
    }
}

void update_item(Item *item) {
    int brie = is_brie(item);
    int backstage_passes = is_backstage_passes(item);
    int sulfuras = is_sulfuras(item);

    if (brie) {
        update_brie(item);
    } else if (backstage_passes) {
        update_backstage_passes(item);
    } else if (sulfuras) {
        update_sulfuras(item);
    } else {
        update_regular_item(item);
    }
}

int is_sulfuras(const Item *item) { return !strcmp(item->name, "Sulfuras, Hand of Ragnaros"); }

int is_backstage_passes(const Item *item) { return !strcmp(item->name, "Backstage passes to a TAFKAL80ETC concert"); }

int is_brie(const Item *item) { return !strcmp(item->name, "Aged Brie"); }

void update_regular_item(Item *item) {
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

void update_sulfuras(Item *item) {
    (void) item;
    // do nothing
}

void update_backstage_passes(Item *item) {
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
