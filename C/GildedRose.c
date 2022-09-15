#include <string.h>
#include <stdio.h>

#include "GildedRose.h"

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
    int i;
    
    for (i = 0; i < size; i++)
    {
        Item * item = items + i;
        if (strcmp(item->name, "Aged Brie") && strcmp(item->name, "Backstage passes to a TAFKAL80ETC concert"))
        {
            if (item->quality > 0)
            {
                if (strcmp(item->name, "Sulfuras, Hand of Ragnaros"))
                {
                    item->quality = item->quality - 1;
                }
            }
        }
        else
        {
            if (item->quality < 50)
            {
                item->quality = item->quality + 1;

                if (!strcmp(item->name, "Backstage passes to a TAFKAL80ETC concert"))
                {
                    if (item->sellIn < 11)
                    {
                        if (item->quality < 50)
                        {
                            item->quality = item->quality + 1;
                        }
                    }

                    if (item->sellIn < 6)
                    {
                        if (item->quality < 50)
                        {
                            item->quality = item->quality + 1;
                        }
                    }
                }
            }
        }

        if (strcmp(item->name, "Sulfuras, Hand of Ragnaros"))
        {
            item->sellIn = item->sellIn - 1;
        }

        if (item->sellIn < 0)
        {
            if (strcmp(item->name, "Aged Brie"))
            {
                if (strcmp(item->name, "Backstage passes to a TAFKAL80ETC concert"))
                {
                    if (item->quality > 0)
                    {
                        if (strcmp(item->name, "Sulfuras, Hand of Ragnaros"))
                        {
                            item->quality = item->quality - 1;
                        }
                    }
                }
                else
                {
                    item->quality = item->quality - item->quality;
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
}
