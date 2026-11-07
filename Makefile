CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
LDLIBS = -lpqxx -lpq

TARGET = a3
SOURCES = src/main.cxx src/students.cxx

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean