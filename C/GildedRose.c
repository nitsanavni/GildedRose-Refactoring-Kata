#include <string.h>

#include "GildedRose.h"

void update_item(Item *item);

void udpate_brie(Item *item);

void update_backstage_passes(Item *item);

void update_sulfuras();

void update_regular_item(Item *item);

int is_brie(const Item *);

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
        update_item(items + i);
    }
}

void update_item(Item *item) {
    typedef int (*const predicate_t)(const Item *);
    typedef void (*const update_t)(Item *);

    static const struct {
        predicate_t predicate;
        update_t update;
    } handlers[] = {
            {is_brie,             udpate_brie},
            {is_backstage_passes, update_backstage_passes},
            {is_sulfuras,         update_sulfuras},
            // default - keep last
            {is_regular_item,     update_regular_item}
    };

    static const int NUM_OF_HANDLERS = sizeof(handlers) / sizeof(handlers[0]);

    for (int i = 0; i < NUM_OF_HANDLERS; ++i) {
        if (handlers[i].predicate(item)) {
            handlers[i].update(item);
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

void update_sulfuras() {// do nothing
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


void udpate_brie(Item *item) {
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

