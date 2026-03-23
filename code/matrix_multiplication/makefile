CXX = g++
CXXFLAGS = -std=c++17
TARGET = matrix_multiplication
PRIN_DIR = .
DIR = algorithms
SOURCES = $(PRIN_DIR)/matrix_multiplication.cpp \
		  $(DIR)/naive.cpp \
		  $(DIR)/strassen.cpp
HEADER = $(DIR)/matrix.h

OBJS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGET)
run: $(TARGET)
	./$(TARGET)