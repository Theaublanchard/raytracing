# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Targets
TARGET = myprogram

# Source files
SRCS = main.cpp camera.cpp objects.cpp  vector.cpp
# SRCS = *.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) 

.PHONY: all clean
