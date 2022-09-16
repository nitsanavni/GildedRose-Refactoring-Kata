#include <stdlib.h>
#include <string.h>

#include "updaters.h"

const int NUM_OF_UPDATERS = 4;

static struct Updater *updaters;
static struct Updater *default_updater;

static void init_updaters();

Updater *find_updater_for(const Item *param) {
    init_updaters();

    for (int u = 0; u < NUM_OF_UPDATERS; u++) {
        if (updaters[u].its_me(param)) {
            return &updaters[u];
        }
    }

    return default_updater;
}

static int default_its_me(const Item *i);

static void default_update_item(Item *item);

static int is_backstage_passes(const Item *item);

static void update_backstage_passes(Item *item);

static int is_brie(const Item *item);

static void update_brie(Item *item);

static int is_sulfuras(const Item *item);

static void noop_update(Item *item);

static void init_updaters() {
    if (updaters) {
        return;
    }

    Updater _default_updater = {.its_me = default_its_me, .update = default_update_item};
    Updater backstage_passes_updater = {.its_me = is_backstage_passes, .update = update_backstage_passes};
    Updater brie_updater = {.its_me = is_brie, .update = update_brie};
    Updater sulfuras_updater = {.its_me = is_sulfuras, .update = noop_update};

    // should ever be freed?
    updaters = malloc(sizeof(Updater) * NUM_OF_UPDATERS);

    updaters[0] = sulfuras_updater;
    updaters[1] = brie_updater;
    updaters[2] = backstage_passes_updater;
    // should be kept last
    updaters[3] = _default_updater;

    default_updater = &updaters[3];
}

static int default_its_me(const Item *i) {
    (void) i;

    return 1;
}

static int false(const Item *i) {
    (void) i;
    return 0;
}

static int is_sulfuras(const Item *item) {
    return !strcmp(item->name, "Sulfuras, Hand of Ragnaros");
}

static void noop_update(Item *item) {
    // do nothing
    (void) item;
}

static int is_brie(const Item *item) {
    return !strcmp(item->name, "Aged Brie");
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

static void update_brie(Item *item) {
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

static void clip_quality(Item *item) {
    if (item->quality > 50) {
        item->quality = 50;
    } else if (item->quality < 0) {
        item->quality = 0;
    }
}
