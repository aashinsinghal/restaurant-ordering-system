CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
TARGET   := bin/restaurant
SRCS     := $(wildcard src/*.cpp)
OBJS     := $(SRCS:src/%.cpp=build/%.o)

.PHONY: all clean

all: bin build $(TARGET)

bin:
	mkdir -p bin

build:
	mkdir -p build

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build bin
