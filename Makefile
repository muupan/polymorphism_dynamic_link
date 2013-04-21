CXX=g++
TARGETS=a.out
CXXFLAGS=-std=c++0x
DYLIB_SRCS=cat.cpp dog.cpp
DYLIBS=$(DYLIB_SRCS:.cpp=.so)

all: $(TARGETS) $(DYLIBS)

$(TARGETS):
	$(CXX) $(CXXFLAGS) main.cpp

.SUFFIXES: .so
.cpp.so:
	$(CXX) $(CXXFLAGS) -shared $< -o $@

.PHONY: clean
clean:
	$(RM) *.o *.so $(TARGETS)
