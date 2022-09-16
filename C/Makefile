CPPUTEST_HOME = CppUTest

USER_DIR = .

CPPFLAGS += -I$(CPPUTEST_HOME)/include
CFLAGS += -g -Wall -Wextra
CPP_ONLY_FLAGS = -std=c++11
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

all : GildedRoseUnitTests GildedRoseTextTests GildedRoseApprovalTests

updaters.o: $(USER_DIR)/updaters.c brie_updater.c sulfuras_updater.c
	$(CC) $(CFLAGS) -c updaters.c -c brie_updater.c -c sulfuras_updater.c

GildedRose.o : $(USER_DIR)/GildedRose.c updaters.o brie_updater.o sulfuras_updater.o

GildedRoseUnitTests : $(USER_DIR)/GildedRoseUnitTests.cc GildedRose.o
	$(CXX) $(CPPFLAGS) $(CPP_ONLY_FLAGS) $(CFLAGS) -o $@ $(USER_DIR)/GildedRoseUnitTests.cc GildedRose.o updaters.o brie_updater.o $(LD_LIBRARIES)

GildedRoseApprovalTests : $(USER_DIR)/GildedRoseApprovalTests.cc GildedRose.o
	$(CXX) $(CPPFLAGS) $(CPP_ONLY_FLAGS) $(CFLAGS) -o $@ $(USER_DIR)/GildedRoseApprovalTests.cc GildedRose.o updaters.o brie_updater.o sulfuras_updater.o $(LD_LIBRARIES)

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
