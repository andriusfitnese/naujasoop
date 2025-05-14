CXX            = g++
CXXFLAGS       = -O3 -Wall -std=c++17

BIN_DIR       := bin
CATCH_AMALG   := vector/catch_amalgamated.cpp
VECTOR_ALL_SRCS = $(wildcard vector/*.cpp)

VECTOR_LIB_SRCS := $(filter-out \
    vector/vector.cpp \
    vector/catch_amalgamated.cpp \
    vector/catch.cpp, \
    $(VECTOR_ALL_SRCS))

.PHONY: all clean
all: \
	$(BIN_DIR)/catch_tests.exe

$(BIN_DIR):
	if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"

$(BIN_DIR)/catch_tests.exe: vector/catch.cpp $(VECTOR_LIB_SRCS) $(CATCH_AMALG) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I. -Ivector \
	    -o $@ vector/catch.cpp $(VECTOR_LIB_SRCS) $(CATCH_AMALG)

clean:
	if exist "$(BIN_DIR)" rmdir /S /Q "$(BIN_DIR)"