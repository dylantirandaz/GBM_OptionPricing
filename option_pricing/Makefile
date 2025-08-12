# Makefile for Option Pricing Project
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -I include
SRCDIR = src
INCDIR = include
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = option_pricing

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: test_compilation.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) test_compilation.cpp $(SRCDIR)/option.cpp $(SRCDIR)/european_option.cpp $(SRCDIR)/asian_option.cpp $(SRCDIR)/monte_carlo.cpp -o test_compilation

clean:
	rm -f $(OBJECTS) $(TARGET) test_compilation.exe test_compilation

windows:
	cl /EHsc /I include src\*.cpp /Fe:option_pricing.exe

.PHONY: all clean test windows
