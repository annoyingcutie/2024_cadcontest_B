# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Output executable name
TARGET = RC

# Source files
SRCS = main.cpp read.cpp def.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header files
HEADERS = read.h def.h 

# Default rule
all: $(TARGET)

# Link the object files to create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each source file into an object file
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
