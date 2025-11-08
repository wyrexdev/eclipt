TARGET   := Ecplit
CXX      := g++
CXXFLAGS := -std=c++20 -O2 -Wall -Wextra -Iinclude
LDFLAGS  := $(shell pkg-config --libs glfw3 vulkan 2>/dev/null || echo "-lglfw -lvulkan -ldl -lGL -lglad")

SRC_DIR  := src
INC_DIR  := include
OBJ_DIR  := build/obj
BIN_DIR  := build/bin

SRC := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

DIRS := $(sort $(dir $(OBJ)))

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)
	@echo "[✔] Build complete -> $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "[✗] Cleaned"

rebuild: clean all

print:
	@echo "Sources:" $(SRC)
	@echo "Objects:" $(OBJ)

.PHONY: all clean rebuild print