#include <string.h>

#include "brie_updater.h"

static int its_me(const Item*);
static void update(Item*);

Updater *get_brie_updater() {
    static Updater updaterr = {.its_me = its_me, .update = update};

    return &updaterr;
}

static int its_me(const Item* item){
    return !strcmp(item->name, "Aged Brie");
}

static void update(Item* item) {
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
