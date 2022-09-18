#include <string.h>
#include <stdio.h>

#include "GildedRose.h"

static void update_item(Item *item);

void update_brie(Item *item);

void update_backstage_passes(Item *item);

void update_sulfuras(Item *item);

void update_regular_item(Item *);

int is_true(const Item *);

int is_brie(const Item *);

int is_backstage_passes(const Item *item);

int is_sulfuras(const Item *item);

typedef void (*const update)(Item *);

typedef const struct {
    const update update;
} Updater;

static Updater *get_updater_for(const Item *item);

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

static void update_item(Item *item) {
    get_updater_for(item)->update(item);
}

typedef int (*const is_item)(const Item *);

typedef const struct {
    const is_item is_item;
    const Updater updater;
} Handler;

static const int NUM_OF_HANDLERS = 4;

Handler *get_handlers() {
    static const Handler handlers[] = {
            {is_brie,             {update_brie}},
            {is_backstage_passes, {update_backstage_passes}},
            {is_sulfuras,         {update_sulfuras}},
            // default - keep last
            {is_true,             {update_regular_item}}
    };

    return handlers;
}

Handler *find_handler_for(const Item *item) {
    Handler *handlers = get_handlers();

    for (int h = 0; h < NUM_OF_HANDLERS; h++) {
        if (handlers[h].is_item(item)) {
            return handlers + h;
        }
    }
}

static Updater *get_updater_for(const Item *item) {
    return &find_handler_for(item)->updater;
}

int is_true(const Item *item) {
    (void) item;
    return 1;
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
