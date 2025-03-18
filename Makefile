CXX = g++
CXXFLAGS = -O3 -Wall -std=c++14

VECTOR_SRCS = $(wildcard vector/*.cpp)
DEQUE_SRCS = $(wildcard deque/*.cpp)
LIST_SRCS = $(wildcard list/*.cpp)

BIN_DIR = bin

all: $(BIN_DIR)/vector_program $(BIN_DIR)/deque_program $(BIN_DIR)/list_program

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/vector_program: $(VECTOR_SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(VECTOR_SRCS)

$(BIN_DIR)/deque_program: $(DEQUE_SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(DEQUE_SRCS)

$(BIN_DIR)/list_program: $(LIST_SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(LIST_SRCS)

clean:
	del /Q $(BIN_DIR)\vector_program.exe $(BIN_DIR)\deque_program.exe $(BIN_DIR)\list_program.exe