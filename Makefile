# Compiler Settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra 
LDFLAGS = 

# Output Executable Name
TARGET = dungeon_crawler

# 1. Automatic Source Discovery
# Finds all .cpp files in the current directory (main.cpp, Game.cpp, etc.)
SRCS = $(wildcard *.cpp)

# Generates a list of .o files (main.o, Game.o...)
OBJS = $(SRCS:.cpp=.o)

# --- TARGETS ---

# Default Target (Release Mode)
# Compiles with -O2 (Standard optimization)
all: CXXFLAGS += -O2
all: $(TARGET)

# Debug Target
# Compiles with -O0 (No optimization) and -g (Debug symbols) for GDB/Valgrind
debug: CXXFLAGS += -O0 -g
debug: clean $(TARGET)
	@echo "Build complete with Debug flags (-O0 -g)"

# The Linker Step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compilation Step (Generic rule for all .cpp files)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- UTILITY TARGETS ---

# Run with Valgrind
# Usage: make valgrind
valgrind: debug
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET)

# Run with Time
# Usage: make time
time: all
	time ./$(TARGET)

# Clean Up
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all debug clean valgrind time