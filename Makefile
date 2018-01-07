CC := g++
FLAGS := -std=c++14 -Wall -pthread -g
INC_DIR := ./include/
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INCLUDE := -I$(INC_DIR)

$(BIN_DIR)/routing: $(BUILD_DIR)/route_message.o $(BUILD_DIR)/route_node.o $(BUILD_DIR)/route_algo.o $(BUILD_DIR)/route_dv.o $(BUILD_DIR)/route_ls.o $(BUILD_DIR)/socket_sender.o $(BUILD_DIR)/socket_receiver.o $(BUILD_DIR)/thread_safe_queue.o $(BUILD_DIR)/args.o
	@mkdir -p bin
	$(CC) $(FLAGS) $(INCLUDE) $^ ./$(SRC_DIR)/main.cpp  -o $@ 

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.h
	@mkdir -p build
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf ./bin
	@rm -rf ./build
