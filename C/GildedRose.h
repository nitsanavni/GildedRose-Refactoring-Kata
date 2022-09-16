#ifndef ROSE_INCLUDED
#define ROSE_INCLUDED

#include "Item.h"

extern Item* init_item(Item* item, const char *name, int sellIn, int quality);
extern void update_quality(Item items[], int num_of_items);
extern char* print_item(char* buffer, Item* item);

#endif