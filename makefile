CXX ?= g++
CFLAGS = -g -Wall -Wextra -std=c++17

BUILD_PATH = build
BIN_PATH = $(BUILD_PATH)/bin
BIN = cube_solver

PCH_SRC = include/pch.h
PCH_OUT = include/pch.h.gch

SRC_EXT = cpp
SRC_PATH = src
INCL_PATH = -I include/

SRC = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
OBJ = $(SRC:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
DEPS = $(OBJ:.o=.d)

.PHONY : default_target
default_target : release

.PHONY : release
release : export CXXFLAGS := $(CXXFLAGS) $(CFLAGS)
release : dirs
	@$(MAKE) all

.PHONY : dirs
dirs :
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJ))
	@mkdir -p $(BIN_PATH)

.PHONY : clean
clean :
	@echo "Deleting $(BIN) symlink"
	@$(RM) $(BIN)
	@echo "Deleting directories"
	@$(RM) -r $(BIN_PATH)
	@$(RM) -r $(BUILD_PATH)
	@echo "Deleting pre-compiled headers ($(PCH_OUT))"
	@$(RM) $(PCH_OUT)

.PHONY : all
all : $(BIN_PATH)/$(BIN)
	@echo "Making symlink: $(BIN) -> $<"
	@$(RM) $(BIN)
	@ln -s $(BIN_PATH)/$(BIN) $(BIN)

$(BIN_PATH)/$(BIN) : $(OBJ)
	@echo "Linking: $@"
	$(CXX) $(OBJ) -o $@ ${libs}

-include $(DEPS)

$(PCH_OUT) : $(PCH_SRC)
	@echo "Pre-compiling headers: $< -> $@"
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BUILD_PATH)/%.o : $(SRC_PATH)/%.$(SRC_EXT) $(PCH_OUT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) -include $(PCH_SRC) $(INCL_PATH) -MP -MMD -c $< -o $@
