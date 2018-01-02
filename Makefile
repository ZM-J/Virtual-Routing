CC := g++
FLAGS := -std=c++14 -Wall
INC_DIR := ./include/
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INCLUDE := -I$(INC_DIR)

$(BIN_DIR)/routing: $(BUILD_DIR)/controller.o $(BUILD_DIR)/client.o $(BUILD_DIR)/normal_node.o $(BUILD_DIR)/routing-dv.o $(BUILD_DIR)/routing-ls.o
	@mkdir -p bin
	$(CC) $(FLAGS) $(INCLUDE) $^ ./$(SRC_DIR)/main.cpp  -o $@ 

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp include/%.hpp
	@mkdir -p build
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf ./bin
	@rm -rf ./build