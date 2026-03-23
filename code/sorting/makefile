CXX = g++
CXXFLAGS = -std=c++17
TARGET = sorting
PRIN_DIR = .
DIR = algorithms
SOURCES = $(PRIN_DIR)/sorting.cpp\
		  $(DIR)/mergesort.cpp \
		  $(DIR)/quicksort.cpp \
		  $(DIR)/sort.cpp
HEADER = $(DIR)/sorting.h

OBJS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGET)
run: $(TARGET)
	./$(TARGET)