
#
# Building
#

CC = clang
CXX = clang++

C_INCLUDES = -I. -Isrc/core
C_DEFINES =
CFLAGS = -g -MD -Wall -Werror -O0 $(C_INCLUDES) $(C_DEFINES)

CXX_INCLUDES = -I. -Isrc/core
CXX_DEFINES =
CXXFLAGS = -MD -Wall -Werror -O0 $(CXX_INCLUDES) $(CXX_DEFINES)

SRC_DIR = src
BIN_DIR = bin
TST_DIR = tst

VPATH += $(shell find $(SRC_DIR) $(TST_DIR) -type d)

ifdef DEBUG
  DEBUGPREFIX = debug-
	C_DEFINES += -DTST_VERBOSE
endif

-include $(wildcard $(BIN_DIR)/*.d)

$(BIN_DIR):
	mkdir $@

#
# Utility
#

.PHONY: echo-%
echo-%:
	@echo $($(patsubst echo-%,%,$@))

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)
	find . -name "*~" | xargs rm

#
# Testing
#

LNG =
STR =
IMP =
ifeq ($(MAKECMDGOALS),test)
  ifndef LNG
    $(error Must define LNG has c or cpp.)
  endif
  ifndef STR
    $(error Must defin STR as an struct.)
  endif
  ifndef IMP
    $(error Must defin IMP as an implementation.)
  endif
endif

$(BIN_DIR)/$(DEBUGPREFIX)%-c.o: %.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(BIN_DIR)/$(DEBUGPREFIX)%-cpp.o: %.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

TST_SRC=$(TST_DIR)/$(LNG)/$(STR)-tst.$(LNG)
IMP_SRC=$(SRC_DIR)/$(STR)/$(LNG)/$(STR)-$(IMP).$(LNG)
SRC=$(TST_SRC) $(IMP_SRC)
OBJ=$(patsubst %.$(LNG),$(DEBUGPREFIX)%-$(LNG).o,$(notdir $(SRC)))
EXE=$(BIN_DIR)/$(DEBUGPREFIX)$(STR)-$(IMP)-$(LNG)-test
$(EXE): $(OBJ)
	$(CC) -o $@ $^

.PHONY: test
test: $(EXE)
	./$(EXE)
