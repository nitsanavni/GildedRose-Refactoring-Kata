#ifndef C_UPDATERS_H
#define C_UPDATERS_H

#include "Updater.h"

void init_updaters();

Updater *find_updater_for(const Item *param);

#endif //C_UPDATERS_H
