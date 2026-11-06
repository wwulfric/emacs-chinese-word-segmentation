ifeq ($(shell $(CXX) --version | grep -o clang), clang)
	ifeq ($(shell uname -o), Android)
		CXXFLAGS += -std=c++11
	else
		CXXFLAGS += -std=c++17
	endif
endif

all: cnws
.PHONY: all test clean
test: cnws
	python3 -m unittest discover -s test -v
cnws: cnws.cpp
	$(CXX) $(CXXFLAGS) -Icppjieba/deps/limonp/include -Icppjieba/include -O3 -o cnws cnws.cpp
clean:
	rm -f *.a *.o cnws
