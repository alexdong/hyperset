# Makefile adapted from http://bit.ly/9CNavO
# To generate release code, `make mode=release`
#

BOOST_INCLUDE_DIR=/user/include/boost/
THRIFT_INCLUDE_DIR=/usr/local/include/thrift
THRIFT_LIB=thrift

PLATFORM := $(shell uname -m)
ifeq ($(PLATFORM), i686)
BOOST_THREAD_LIB=boost_thread
BOOST_UNIT_TEST_FRAMEWORK=boost_unit_test_framework
endif
ifeq ($(PLATFORM), x86_64)
BOOST_THREAD_LIB=boost_thread-mt
BOOST_UNIT_TEST_FRAMEWORK=boost_unit_test_framework-mt
endif

SERVER_OBJECTS=hyperset.o hyperset.o hyperset_types.o

CXX=g++
LDFLAGS=-L/usr/local/lib -l$(BOOST_THREAD_LIB) \
		-lgflags -lglog

ifeq ($(mode), release)
	CXXFLAGS=-I$(THRIFT_INCLUDE_DIR) \
			 -Wno-deprecated -Wall -O2 -DNDEBUG \
			 -fno-builtin-malloc -fno-builtin-calloc \
			 -fno-builtin-realloc -fno-builtin-free
else
	CXXFLAGS=-I$(THRIFT_INCLUDE_DIR) \
			 -Wno-deprecated -Wall -O0 -pg -g -fprofile-arcs -ftest-coverage
endif

all: test

server: core.o $(SERVER_OBJECTS)
	$(CXX) -o hyperset core.o $(SERVER_OBJECTS) $(LDFLAGS) -l$(THRIFT) -ltcmalloc

test: core.o test_core.o
	$(CXX) -o test test_core.o core.o \
	    $(LDFLAGS) -l$(BOOST_UNIT_TEST_FRAMEWORK)  \
	./test

coverage: test
	./test
	lcov --directory . --capture --output-file app.info
	genhtml --output-directory ./cov_html ./app.info
	firefox ./cov_html/index.html

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<  -o $@

thrift: clean
	thrift -strict -gen cpp hyperset.thrift
	thrift -strict -gen py hyperset.thrift

clean:
	rm -f hyperset core test *.o *.out *.gcda *.gcno *.d app.info tags
	rm -f gprof.output
	rm -r -f cov_html
	rm -r -f gen-cpp
	rm -r -f gen-py
	ctags -R .
