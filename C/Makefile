CPPUTEST_HOME = CppUTest

USER_DIR = .

CPPFLAGS += -I$(CPPUTEST_HOME)/include
CFLAGS += -g -Wall -Wextra
CPP_ONLY_FLAGS = -std=c++11
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

all : GildedRoseUnitTests GildedRoseTextTests GildedRoseApprovalTests

GildedRose.o : $(USER_DIR)/GildedRose.c

GildedRoseUnitTests : $(USER_DIR)/GildedRoseUnitTests.cc GildedRose.o
	$(CXX) $(CPPFLAGS) $(CPP_ONLY_FLAGS) $(CFLAGS) -o $@ $(USER_DIR)/GildedRoseUnitTests.cc GildedRose.o $(LD_LIBRARIES)

GildedRoseApprovalTests : $(USER_DIR)/GildedRoseApprovalTests.cc GildedRose.o
	$(CXX) $(CPPFLAGS) $(CPP_ONLY_FLAGS) $(CFLAGS) -o $@ $(USER_DIR)/GildedRoseApprovalTests.cc GildedRose.o $(LD_LIBRARIES)

GildedRoseTextTests.o : $(USER_DIR)/GildedRoseTextTests.c

GildedRoseTextTests : GildedRoseTextTests.o GildedRose.o
	$(CC) $^ -o $@

clean :
	rm -f $(TESTS) $(TEXTTESTS) *.o *~

check-syntax:
	gcc $(CPPFLAGS) -o /dev/null -S ${CHK_SOURCES}

text: all
	./GildedRoseTextTests

unit: all
	./GildedRoseUnitTests

approvals: all
	./GildedRoseApprovalTests
