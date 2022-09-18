#include <string.h>

#include "GildedRose.h"

void update_item(Item *item);

void update_brie(Item *item);

void update_backstage_passes(Item *item);

void update_sulfuras();

void update_regular_item(Item *item);

int is_brie(const Item *item);

int is_backstage_passes(const Item *item);

int is_sulfuras(const Item *item);

int is_regular_item();

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
    typedef int (*predicate_t)(const Item *);
    typedef void (*update_t)(Item *);

    static const struct {
        const predicate_t predicate;
        const update_t update
    } handlers[] = {
            {is_brie,             update_brie},
            {is_backstage_passes, update_backstage_passes},
            {is_sulfuras,         update_sulfuras},
            {is_regular_item,     update_regular_item},
    };

    static const int NUM_OF_HANDLERS = sizeof(handlers) / sizeof(handlers[0]);

    for (int h = 0; h < NUM_OF_HANDLERS; h++) {
        if (handlers[h].predicate(item)) {
            handlers[h].update(item);
            return;
        }
    }
}

int is_regular_item() { return 1; }

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

void update_sulfuras() {
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

