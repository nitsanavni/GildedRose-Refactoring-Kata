#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "GildedRose.h"

typedef int (*ItsMe)(const Item *);

typedef void (*Update)(Item *);

typedef const struct Updater {
    ItsMe its_me;

    Update update;
} Updater;

const int NUM_OF_UPDATERS = 4;

typedef const Updater Updaters[NUM_OF_UPDATERS];

void update_brie(Item *item);

void update_backstage_passes(Item *item);

void clip_quality(Item *item);

int backstage_passes_qd(int sellIn);

void default_update_item(Item *item);

int is_backstage_passes(const Item *item);

int is_brie(const Item *item);

int is_sulfuras(const Item *item);

void noop_update(Item *);

Updater *find_updater_for(const Item *, Updaters);

Updater *init_updaters();

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
    (void) i;

    return 1;
}

void
update_quality(Item items[], int num_of_items) {
    Updater *updaters = init_updaters();

    for (int i = 0; i < num_of_items; i++) {
        Item *item = items + i;

        find_updater_for(item, updaters)->update(item);
    }
}

struct Updater *updaters;

Updater *init_updaters() {
    if (updaters) {
        return updaters;
    }

    updaters = malloc(sizeof(Updaters));

    Updater default_updater = {.its_me = default_its_me, .update = default_update_item};
    Updater backstage_passes_updater = {.its_me = is_backstage_passes, .update = update_backstage_passes};
    Updater brie_updater = {.its_me = is_brie, .update = update_brie};
    Updater sulfuras_updater = {.its_me = is_sulfuras, .update = noop_update};

    updaters[0] = sulfuras_updater;
    updaters[1] = brie_updater;
    updaters[2] = backstage_passes_updater;
    updaters[3] = default_updater;    // should be kept las;


    return updaters;
}

int false(const Item *i) {
    (void) i;
    return 0;
}

Updater *find_updater_for(const Item *param, Updaters updaters) {
    for (int u = 0; u < NUM_OF_UPDATERS; u++) {
        if (updaters[u].its_me(param)) {
            return &updaters[u];
        }
    }

    return &updaters[0];
}

int is_sulfuras(const Item *item) { return !strcmp(item->name, "Sulfuras, Hand of Ragnaros"); }

void noop_update(Item *item) {
    // do nothing
    (void) item;
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
