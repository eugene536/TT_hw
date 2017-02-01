CXX=g++
CXXFLAGS=-std=c++11 -O3 -g -march=native -ffast-math -mtune=native
INCLUDE=-Iinclude
SRC_FILES=source/*.cpp source/**/*.cpp

all: 
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SRC_FILES) -o TT_hw

debug: 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -DDEBUG  $(SRC_FILES) -o TT_hw_test

with_smart_ptr: 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -DDEBUG -DUSE_SMART_POINTER $(SRC_FILES) -o TT_hw

clean:
	rm -f TT_hw_test TT_hw



