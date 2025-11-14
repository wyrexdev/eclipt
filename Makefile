TARGET   := Ecplit
CXX      := g++
CXXFLAGS := -std=c++20 -O2 -Wall -Wextra -Iinclude
LDFLAGS  := -lglfw -lvulkan -ldl -lGL

SRC_DIR  := src
OBJ_DIR  := build/obj
BIN_DIR  := build/bin

CPP_SRC := $(shell find $(SRC_DIR) -type f -name '*.cpp')
C_SRC   := $(shell find $(SRC_DIR) -type f -name '*.c')

CPP_OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CPP_SRC))
C_OBJ   := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRC))

OBJ := $(CPP_OBJ) $(C_OBJ)

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)
	@echo "[✔] Build complete -> $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -O2 -Iinclude -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "[✗] Cleaned"

run:
	./build/bin/Ecplit

rebuild: clean all

print:
	@echo "CPP Sources:" $(CPP_SRC)
	@echo "C Sources:" $(C_SRC)
	@echo "Objects:" $(OBJ)

.PHONY: all clean rebuild print
