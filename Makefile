CXXFLAGS += -I./
CXXFLAGS += -std=c++11 -Wall -g -c -o

LIB_FILES := -levent -lglog -lgflags -L/usr/local/lib -lgtest -lgtest_main -lpthread

CPP_SOURCES := ./monitor/registry.cc \


CPP_OBJECTS := $(CPP_SOURCES:.cc=.o)


TESTS := ./monitor/counter_unittest \
	./monitor/gauge_unittest \


all: $(CPP_OBJECTS) $(TESTS)
.cc.o:
	$(CXX) $(CXXFLAGS) $@ $<

./monitor/counter_unittest: ./monitor/counter_unittest.o
	$(CXX) -o $@ $< $(CPP_OBJECTS) $(LIB_FILES)
./monitor/counter_unittest.o: ./monitor/counter_unittest.cc
	$(CXX) $(CXXFLAGS) $@ $<

./monitor/gauge_unittest: ./monitor/gauge_unittest.o
	$(CXX) -o $@ $< $(CPP_OBJECTS) $(LIB_FILES)
./monitor/gauge_unittest.o: ./monitor/gauge_unittest.cc
	$(CXX) $(CXXFLAGS) $@ $<

clean:
	rm -fr monitor/*.o
	rm -fr $(TESTS)
