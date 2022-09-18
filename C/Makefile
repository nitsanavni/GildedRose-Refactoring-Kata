CPPUTEST_HOME = CppUTest

USER_DIR = .

CPPFLAGS += -I$(CPPUTEST_HOME)/include
CFLAGS += -g -Wall -Wextra -ftest-coverage -fprofile-arcs
CPP_ONLY_FLAGS = -std=c++11
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

all : GildedRoseUnitTests GildedRoseTextTests GildedRoseApprovalTests

clean-cov:
	git clean -fx -- *.g*

GildedRose.o : $(USER_DIR)/GildedRose.c clean-cov

GildedRoseUnitTests : $(USER_DIR)/GildedRoseUnitTests.cc GildedRose.o
	$(CXX) $(CPPFLAGS) $(CPP_ONLY_FLAGS) $(CFLAGS) -o $@ $(USER_DIR)/GildedRoseUnitTests.cc GildedRose.o $(LD_LIBRARIES)

GildedRoseApprovalTests.o : $(USER_DIR)/GildedRoseApprovalTests.cc
	$(CXX) $(CPPFLAGS) $(CPP_ONLY_FLAGS) $(CFLAGS) -c -o $@ $(USER_DIR)/GildedRoseApprovalTests.cc

GildedRoseApprovalTests : $(USER_DIR)/GildedRoseApprovalTests.o GildedRose.o
	$(CXX) $(CPPFLAGS) $(CPP_ONLY_FLAGS) $(CFLAGS) -o $@ $(USER_DIR)/GildedRoseApprovalTests.o GildedRose.o $(LD_LIBRARIES)

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
	./GildedRoseApprovalTests; \
	gcov GildedRose.c; \
	grep \#\# GildedRose.c.g* | head -n 5 || true
