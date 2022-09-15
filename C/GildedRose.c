#include <string.h>
#include <stdio.h>

#include "GildedRose.h"

typedef int (*ItsMe)(const Item *);

typedef void (*Update)(Item *);

struct Updater {
    ItsMe its_me;

    Update update;
};

int NUM_OF_UPDATERS = 3;

void update_item_quality(Item *item, struct Updater updaters[]);

void update_brie(Item *item);

void update_backstage_passes(Item *item);

void clip_quality(Item *item);

int backstage_passes_qd(int sellIn);

void default_update_item(Item *item);

int is_backstage_passes(const Item *item);

int is_brie(const Item *item);

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

    return buffer;
}


int default_its_me(const Item *i) {
    return 1;
};


void
update_quality(Item items[], int size) {
    struct Updater updaters[NUM_OF_UPDATERS];

    const struct Updater default_updater = {.its_me = default_its_me, .update = default_update_item};
    const struct Updater backstage_passes_updater = {.its_me = is_backstage_passes, .update = update_backstage_passes};
    const struct Updater brie_updater = {.its_me = is_brie, .update = update_brie};

    updaters[0] = brie_updater;
    updaters[1] = backstage_passes_updater;
    updaters[2] = default_updater;

    for (int i = 0; i < size; i++) {
        update_item_quality(items + i, updaters);
    }
}

void update_item_quality(Item *item, struct Updater updaters[]) {
    int sulfuras = !strcmp(item->name, "Sulfuras, Hand of Ragnaros");
    int brie = is_brie(item);

    if (sulfuras) {
        // do nothing
    } else {
        for (int u = 0; u < NUM_OF_UPDATERS; u++) {
            const struct Updater updater = updaters[u];

            if (updater.its_me(item)) {
                updater.update(item);
                break;
            }
        }
    }
}

int is_brie(const Item *item) { return !strcmp(item->name, "Aged Brie"); }

int is_backstage_passes(const Item *item) { return !strcmp(item->name, "Backstage passes to a TAFKAL80ETC concert"); }

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
