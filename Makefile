CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17

VECTOR_SRCS = $(wildcard vector/*.cpp)
DEQUE_SRCS := $(wildcard deque/*.cpp)
DEQUE_LIB_SRCS := $(filter-out deque/dequemain.cpp deque/test.cpp,$(DEQUE_SRCS))
LIST_SRCS = $(wildcard list/*.cpp)

BIN_DIR = bin

all: $(BIN_DIR)/vector_program $(BIN_DIR)/class_program $(BIN_DIR)/list_program $(BIN_DIR)/test.exe

$(BIN_DIR):
	if not exist $(BIN_DIR) mkdir $(BIN_DIR)

$(BIN_DIR)/vector_program: $(VECTOR_SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(VECTOR_SRCS)

$(BIN_DIR)/list_program: $(LIST_SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(LIST_SRCS)

$(BIN_DIR)/class_program: deque/dequemain.cpp $(DEQUE_LIB_SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ deque/dequemain.cpp $(DEQUE_LIB_SRCS)

$(BIN_DIR)/test.exe: $(TEST_SRC) $(DEQUE_LIB_SRCS) | $(BIN_DIR)
    $(CXX) $(CXXFLAGS) -o $@ $(TEST_SRC) $(DEQUE_LIB_SRCS)

clean:
	if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)