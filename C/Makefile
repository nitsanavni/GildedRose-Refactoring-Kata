USER_DIR = .

CFLAGS += -g -Wall -Wextra

all : GildedRoseTextTests

GildedRose.o : $(USER_DIR)/GildedRose.c

GildedRoseTextTests.o : $(USER_DIR)/GildedRoseTextTests.c

GildedRoseTextTests : GildedRoseTextTests.o GildedRose.o
	$(CC) $^ -o $@

clean :
	rm -f $(TESTS) $(TEXTTESTS) *.o *~

text: GildedRoseTextTests
	./GildedRoseTextTests

test: GildedRoseTextTests
	./GildedRoseTextTests | python3 -m approvaltests -t gilded-rose