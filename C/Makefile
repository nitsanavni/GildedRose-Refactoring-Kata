CPPUTEST_HOME = CppUTest

USER_DIR = .

CPPFLAGS += -I$(CPPUTEST_HOME)/include
CFLAGS += -g -Wall -Wextra -ftest-coverage -fprofile-arcs
CPP_ONLY_FLAGS = -std=c++11
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

all : GildedRoseUnitTests GildedRoseTextTests GildedRoseApprovalTests

updaters.o: $(USER_DIR)/updaters.c brie_updater.c sulfuras_updater.c backstage_passes_updater.c clip_quality.c
	$(CC) $(CFLAGS) -c updaters.c -c brie_updater.c -c sulfuras_updater.c -c backstage_passes_updater.c -c clip_quality.c

GildedRose.o : $(USER_DIR)/GildedRose.c updaters.o brie_updater.o sulfuras_updater.o backstage_passes_updater.o clip_quality.o

GildedRoseUnitTests : $(USER_DIR)/GildedRoseUnitTests.cc GildedRose.o
	$(CXX) $(CPPFLAGS) $(CPP_ONLY_FLAGS) $(CFLAGS) -o $@ $(USER_DIR)/GildedRoseUnitTests.cc GildedRose.o updaters.o brie_updater.o backstage_passes_updater.o backstage_passes_updater.o $(LD_LIBRARIES)

GildedRoseApprovalTests : $(USER_DIR)/GildedRoseApprovalTests.cc GildedRose.o
	$(CXX) $(CPPFLAGS) $(CPP_ONLY_FLAGS) $(CFLAGS) -o $@ $(USER_DIR)/GildedRoseApprovalTests.cc GildedRose.o updaters.o brie_updater.o sulfuras_updater.o backstage_passes_updater.o clip_quality.o $(LD_LIBRARIES)

GildedRoseTextTests.o : $(USER_DIR)/GildedRoseTextTests.c

GildedRoseTextTests : GildedRoseTextTests.o GildedRose.o
	$(CC) $^ -o $@

clean :
	rm -f $(TESTS) $(TEXTTESTS) *.o *~

check-syntax:
	gcc $(CPPFLAGS) -o /dev/null -S ${CHK_SOURCES}

text: GildedRoseTextTests
	./GildedRoseTextTests

unit: GildedRoseUnitTests
	./GildedRoseUnitTests

approvals: GildedRoseApprovalTests
	./GildedRoseApprovalTests
