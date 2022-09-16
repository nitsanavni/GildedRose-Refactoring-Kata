#include <string.h>

#include "sulfuras_updater.h"

static int its_me(const Item *);

static void update(Item *);

Updater *get_sulfuras_updater() {
    static Updater updaterr = {.its_me = its_me, .update = update};

    return &updaterr;
}

static int its_me(const Item *item) {
    return !strcmp(item->name, "Sulfuras, Hand of Ragnaros");
}

static void update(Item *item) {
    (void) item;
    // do nothing
}
