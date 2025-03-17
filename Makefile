SRC_DIR := ./src
OBJ_DIR := ./obj

CXX := g++
CXXFLAGS := -c -Wall -Werror -pedantic

SOURCES := main.cpp http_server.cpp read_data_and_build_response.cpp logger.cpp http_parser.cpp
SRCS := $(addprefix $(SRC_DIR)/, $(SOURCES))

OBJS := $(addprefix $(OBJ_DIR)/, $(SOURCES:.cpp=.o))

TARGET := http-server

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)
