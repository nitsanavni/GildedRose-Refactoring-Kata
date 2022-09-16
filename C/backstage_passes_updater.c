#include <string.h>

#include "backstage_passes_updater.h"
#include "clip_quality.h"

static int its_me(const Item*);
static void update(Item*);

Updater *get_backstage_passes_updater() {
    static Updater updater = {.its_me = its_me, .update = update};

    return &updater;
}

static int its_me(const Item* item){
    return !strcmp(item->name, "Backstage passes to a TAFKAL80ETC concert");
}

static int backstage_passes_qd(int sellIn);

static void update(Item* item) {
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

