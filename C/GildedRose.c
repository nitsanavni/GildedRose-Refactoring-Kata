#include <string.h>
#include <stdio.h>

#include "GildedRose.h"
#include "updaters.h"


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


void
update_quality(Item items[], int num_of_items) {
    init_updaters();

    for (int i = 0; i < num_of_items; i++) {
        Item *item = items + i;

        find_updater_for(item)->update(item);
    }
}
