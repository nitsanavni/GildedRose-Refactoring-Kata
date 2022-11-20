CPPUTEST_HOME = CppUTest

USER_DIR = .

CPPFLAGS += -I$(CPPUTEST_HOME)/include
CFLAGS += -g -Wall -Wextra
CPP_ONLY_FLAGS = -std=c++11

all : GildedRoseTextTests


GildedRose.o : $(USER_DIR)/GildedRose.c

GildedRoseTextTests.o : $(USER_DIR)/GildedRoseTextTests.c

GildedRoseTextTests : GildedRoseTextTests.o GildedRose.o
	$(CC) $^ -o $@

clean :
	rm -f $(TESTS) $(TEXTTESTS) *.o *~

check-syntax:
	gcc $(CPPFLAGS) -o /dev/null -S ${CHK_SOURCES}

text: GildedRoseTextTests
	./GildedRoseTextTests

test: GildedRoseTextTests
	./GildedRoseTextTests | python3 -m approvaltests -t gilded-rose