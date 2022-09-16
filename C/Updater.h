#ifndef C_UPDATER_H
#define C_UPDATER_H

typedef int (*ItsMe)(const Item *);

typedef void (*Update)(Item *);

typedef const struct Updater {
    ItsMe its_me;

    Update update;
} Updater;

#endif //C_UPDATER_H
