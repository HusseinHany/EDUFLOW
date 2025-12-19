# Makefile for EDUFLOW

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = .

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Target executable
TARGET = $(BINDIR)/eduflow

# Default target
all: $(TARGET)

# Create obj directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Link object files to create executable
$(TARGET): $(OBJDIR) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Rebuild everything
rebuild: clean all

.PHONY: all clean rebuild
