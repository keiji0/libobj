CC = g++
PACKAGE_NAME = obj
PACKAGE_LIBNAME = lib$(PACKAGE_NAME).a
OBJS = buffer.o string.o mpool.o
INCLUDEDIR = include
TEST_FILES = $(wildcard *.test.cpp)

TEST_INCLUDE_FILE = "obj/test.hpp"
TEST_FLAG = __TEST__
INSTALL = /usr/bin/install

.PHONY: all clean test install

all: $(PACKAGE_LIBNAME)

# install: $(PACKAGE_LIBNAME)
# $(INSTALL) -m 444 $< $(HOME)/lib;
# ranlib $(HOME)/lib/$<;
# $(INSTALL) -d $(HOME)/obj;
# cp -f *.hpp $(HOME)/include/obj/

test:
	@for i in $(TEST_FILES:.test.cpp=.test); do \
		make $$i;\
	done
	@for i in $(TEST_FILES:.test.cpp=.test); do \
		sh ./test $$i;\
	done

clean:
	rm -f *.o *.test *.a

$(PACKAGE_LIBNAME): $(OBJS)
	@ar rcsv $@ $(OBJS)

%.o: %.cpp
	$(CC) -Wall -O2 -I$(INCLUDEDIR) -c $<

%.test: %.test.cpp
	$(CC) -Wall -O2 -I$(INCLUDEDIR) -D$(TEST_FLAG) -include "$(@:.test=.hpp)" -include "iostream" -include $(TEST_INCLUDE_FILE) -o $@ $< $(filter %.o, $^) $(filter %.a, $^)

%.print: %.cpp
	$(CC) -E -I$(INCLUDEDIR) $<

buffer.o: buffer.cpp buffer.hpp
buffer.test: buffer.test.cpp buffer.o string.o
string.o: string.cpp string.hpp
string.test: string.test.cpp string.o
mpool.o: mpool.cpp mpool.hpp
mpool.test: mpool.test.cpp mpool.o
schain.test: schain.hpp schain.test.cpp mpool.o buffer.o
type.test: type.test.cpp type.hpp
xml.test: xml.test.cpp buffer.o
string_list.test: string_list.test.cpp string_list.hpp
util.test: util.hpp util.test.cpp
error.test: error.test.cpp error.hpp buffer.o
algorithm.test: algorithm.test.cpp algorithm.hpp
buffer_format.test: buffer_format.hpp buffer_format.test.cpp buffer.o string.o
guess.o: guess.cpp guess_tab.cpp
guess.test: guess.o
