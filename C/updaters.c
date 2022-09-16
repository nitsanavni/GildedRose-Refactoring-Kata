#include <string.h>

#include "updaters.h"
#include "brie_updater.h"
#include "sulfuras_updater.h"

const int NUM_OF_UPDATERS = 4;

static Updater **get_updaters();

static Updater *get_default_updater();

Updater *find_updater_for(const Item *item) {
    Updater **updaters = get_updaters();

    for (int u = 0; u < NUM_OF_UPDATERS; u++) {
        Updater *updater = updaters[u];

        if (updater->its_me(item)) {
            return updater;
        }
    }

    return get_default_updater();
}

static int default_its_me(const Item *i);

static void default_update_item(Item *item);

static int is_backstage_passes(const Item *item);

static void update_backstage_passes(Item *item);

static Updater **get_updaters() {
    static Updater *updaters[] = {NULL, NULL, NULL, NULL};

    if (updaters[0]) {
        return updaters;
    }

    static Updater backstage_passes_updater = {.its_me = is_backstage_passes, .update = update_backstage_passes};
    static Updater default_updater = {.its_me = default_its_me, .update = default_update_item};

    updaters[0] = get_sulfuras_updater();
    updaters[1] = &backstage_passes_updater;
    updaters[2] = get_brie_updater();
    // should be kept last
    updaters[3] = &default_updater;

    return updaters;
}

static Updater *get_default_updater() {
    Updater *last_updater = get_updaters()[NUM_OF_UPDATERS - 1];

    return last_updater;
}

static int default_its_me(const Item *i) {
    (void) i;

    return 1;
}

static int is_backstage_passes(const Item *item) {
    return !strcmp(item->name, "Backstage passes to a TAFKAL80ETC concert");
}

static void clip_quality(Item *item);

static void default_update_item(Item *item) {
    item->sellIn = item->sellIn - 1;

    int decBy = item->sellIn < 0 ? 2 : 1;

    item->quality -= decBy;

    clip_quality(item);
}

static int backstage_passes_qd(int sellIn);

static void update_backstage_passes(Item *item) {
    item->sellIn = item->sellIn - 1;

    if (item->sellIn < 0) {
        item->quality = 0;
        return;
    }

    item->quality += backstage_passes_qd(item->sellIn);

    clip_quality(item);
}

static int backstage_passes_qd(int sellIn) {
    return (sellIn < 5) ? 3 :
           (sellIn < 10) ? 2 :
           1;
}

static void clip_quality(Item *item) {
    if (item->quality > 50) {
        item->quality = 50;
    } else if (item->quality < 0) {
        item->quality = 0;
    }
}
