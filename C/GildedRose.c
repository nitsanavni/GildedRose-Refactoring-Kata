#include <string.h>
#include <stdio.h>

#include "GildedRose.h"

void update_item_quality(Item *item);

Item*
init_item(Item* item, const char *name, int sellIn, int quality)
{
    item->sellIn = sellIn;
    item->quality = quality;
    item->name = strdup(name);
    
    return item;
}

extern char* 
print_item(char* buffer, Item* item) 
{
    sprintf(buffer, "%s, %d, %d", item->name, item->sellIn, item->quality);
}

void 
update_quality(Item items[], int size) 
{
    for (int i = 0; i < size; i++)
    {
        update_item_quality(items + i);
    }
}

void update_item_quality(Item *item) {
    int not_brie = strcmp(item->name, "Aged Brie");
    int not_backstage_passes = strcmp(item->name, "Backstage passes to a TAFKAL80ETC concert");
    int not_sulfuras = strcmp(item->name, "Sulfuras, Hand of Ragnaros");

    if (!not_brie || !not_backstage_passes || !not_sulfuras) {
        if (item->quality < 50) {
            item->quality = item->quality + 1;

            if (!not_backstage_passes) {
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
        }
    } else {
        if (item->quality > 0) {
            item->quality = item->quality - 1;
        }
    }

    if (not_sulfuras)
    {
        item->sellIn = item->sellIn - 1;
    }

    if (item->sellIn < 0)
    {
        if (not_brie)
        {
            if (not_backstage_passes)
            {
                if (item->quality > 0)
                {
                    if (not_sulfuras)
                    {
                        item->quality = item->quality - 1;
                    }
                }
            }
            else
            {
                item->quality = 0;
            }
        }
        else
        {
            if (item->quality < 50)
            {
                item->quality = item->quality + 1;
            }
        }
    }
}
