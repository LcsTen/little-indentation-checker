CXX = g++
CXXFLAGS = -Wall -Wextra -Wshadow -Werror

all: little-indentation-checker

little-indentation-checker: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

auto-check: little-indentation-checker
	./little-indentation-checker --tab main.cpp Makefile

.PHONY: auto-check
