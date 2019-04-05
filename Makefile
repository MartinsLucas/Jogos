COMPILER = g++

RMDIR = rm -rdf

RM = rm -f

DEP_FLAGS = -M -MT $@ -MT $(BIN_PATH)/$(*F).o -MP -MF$@

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

INC_PATHS = -I$(INC_PATH) $(addprefix -I,$(SDL_INC_PATH))

FLAGS = -std=c++11 -Wall -pedantic -Wextra -Wno-unused-parameter -Werror=init-self

DFLAGS = -ggdb - O0 -DDEBUG

RFLAGS = -O3 -mtune=native

INC_PATH = include
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep

CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
INC_FILES = $(wildcard $(INC_PATH)/*.h)
FILE_NAMES = $(sort $(notdir $(CPP_FILES:.cpp)) $(notdir $(INC_FILES:.h=)))
DEP_FILES = $(addprefix $(DEP_PATH)/,$(addsuffix .d,$(FILE_NAMES)))
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))

EXEC = JOGO

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
		$(COMPILER) -o $@ $^ $(LINK_PATH) $(LIBS) $(FLAGS)

$(BIN_PATH)/%.o: $(DEP_PATH)/%.d | folders
		$(COMPILER) $(INC_PATHS) $(addprefix $(SRC_PATH)/,$(notdir $(<:.d=.cpp))) -c $(FLAGS) -o $@

$(DEP_PATH)/%.d: $(SRC_PATH)/%.cpp | folders
		$(COMPILER) $(INC_PATHS) $< $(DEP_FLAGS) $(FLAGS)

.PRECIOUS: $(DEP_FILES)
.PHONY: release debug clean folders help

clean:
		-$(RMDIR) $(DEP_PATH)
		-$(RMDIR) $(BIN_PATH)
		-$(RM) $(EXEC)

release: FLAGS += (RFLAGS)
release: $(EXEC)

debug: FLAGS += (DFLAGS)
debug: $(EXEC)

folders:
ifeq ($(OS), Windows_NT)
		@if NOT exists $(DEP_PATH) (mkdir $(DEP_PATH))
		@if NOT exists $(BIN_PATH) (mkdir $(BIN_PATH))
		@if NOT exists $(INC_PATH) (mkdir $(INC_PATH))
		@if NOT exists $(SRC_PATH) (mkdir $(SRC_PATH))
else
		@mkdir -p $(DEP_PATH) $(BIN_PATH) $(INC_PATH) $(SRC_PATH)
endif

print-% : ; @echo $* = $($*)

help:
ifeq ($(OS), Windows_NT)
		@echo.
endif
		@echo Available targets:
		@echo - release:	Builds the release version.
		@echo - debug:		Builds the debug version.
		@echo - clean:		Cleans generated files.
		@echo - folders:	Generates project directories.
		@echo - help:			Shows this help.
ifeq ($(OS), Windows_NT)
		@echo.
endif

.SECONDEXPANSION:
-include $$(DEP_FILES)
