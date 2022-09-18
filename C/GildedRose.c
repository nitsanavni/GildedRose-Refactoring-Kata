#include <string.h>

#include "GildedRose.h"

void update_item(Item *item);

void update_brie(Item *item);

void update_backstage(Item *item);

void update_sulfuras();

void update_regular_item(Item *item);

int always_true();

int is_brie(const Item *item);

int is_backstage(const Item *item);

int is_sulfuras(const Item *item);

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
    typedef int (*item_predicate_t)(const Item *);
    typedef void (*update_item_t)(Item *);

    struct Handler {
        item_predicate_t predicate;
        update_item_t update;
    };

    static struct Handler handler[] = {
            {is_brie,      update_brie},
            {is_backstage, update_backstage},
            {is_sulfuras,  update_sulfuras},
            {always_true,  update_regular_item},
    };

    for (int i = 0; i < 4; ++i) {
        if (handler[i].predicate(item)) {
            handler[i].update(item);
            return;
        }
    }
}

int is_sulfuras(const Item *item) { return !strcmp(item->name, "Sulfuras, Hand of Ragnaros"); }

int is_backstage(const Item *item) { return !strcmp(item->name, "Backstage passes to a TAFKAL80ETC concert"); }

int is_brie(const Item *item) { return !strcmp(item->name, "Aged Brie"); }

int always_true() { return 1; }

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

void update_backstage(Item *item) {
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

