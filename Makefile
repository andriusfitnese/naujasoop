CXX            = g++
CXXFLAGS       = -O3 -Wall -std=c++17

#DEQUE_ALL_SRCS = $(wildcard deque/*.cpp)
VECTOR_ALL_SRCS = $(wildcard vector/*.cpp)
VECTOR_LIB_SRCS = $(filter-out \
                    vector/vector.cpp)
#DEQUE_LIB_SRCS   = $(filter-out \
                     deque/dequemain.cpp \
                     deque/test.cpp       \
                     deque/catch.cpp     \
                     deque/catch_amalgamated.cpp,     \
                     $(DEQUE_ALL_SRCS))

BIN_DIR        = bin

#all: \
    $(BIN_DIR)/class_program  \
    $(BIN_DIR)/catch_tests.exe

all: \
    $(BIN_DIR)/catch_tests.exe

$(BIN_DIR):
	if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"

#$(BIN_DIR)/class_program: deque/dequemain.cpp $(DEQUE_LIB_SRCS) | $(BIN_DIR)
	#$(CXX) $(CXXFLAGS) -o $@ deque/dequemain.cpp $(DEQUE_LIB_SRCS)

AMALGAMATED_SRC = vector/catch_amalgamated.cpp

$(BIN_DIR)/catch_tests.exe: vector/catch.cpp $(VECTOR_LIB_SRCS) $(AMALGAMATED_SRC) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I. -Ideque \
	    -o $@ vector/catch.cpp $(VECTOR_LIB_SRCS) $(AMALGAMATED_SRC)


clean:
	if exist "$(BIN_DIR)" rmdir /S /Q "$(BIN_DIR)"
