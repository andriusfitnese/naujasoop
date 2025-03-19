CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17

VECTOR_SRCS = $(wildcard vector/*.cpp)
DEQUE_SRCS = $(wildcard deque/*.cpp)
LIST_SRCS = $(wildcard list/*.cpp)

BIN_DIR = bin

all: $(BIN_DIR)/vector_program $(BIN_DIR)/deque_program $(BIN_DIR)/list_program

$(BIN_DIR):
	if not exist $(BIN_DIR) mkdir $(BIN_DIR)

$(BIN_DIR)/vector_program: $(VECTOR_SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(VECTOR_SRCS)

$(BIN_DIR)/deque_program: $(DEQUE_SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(DEQUE_SRCS)

$(BIN_DIR)/list_program: $(LIST_SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(LIST_SRCS)

clean:
	if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)