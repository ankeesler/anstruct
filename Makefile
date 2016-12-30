
#
# Building
#

CC = clang
CXX = clang++

CINCLUDES = -I. -Isrc/core
CDEFINES =
CFLAGS = -g -MD -Wall -Werror -O0 $(CINCLUDES) $(CDEFINES)

CXXINCLUDES = -I. -Isrc/core
CXXDEFINES =
CXXFLAGS = -g -MD -Wall -Werror -O0 $(CXXINCLUDES) $(CXXDEFINES)

LD = clang
LDXX = clang++

LDFLAGS =
LDXXFLAGS =

SRC_DIR = src
BIN_DIR = bin
TST_DIR = tst

VPATH += $(shell find $(SRC_DIR) $(TST_DIR) -type d)

ifdef DEBUG
  DEBUGPOSTFIX = -debug
  CDEFINES += -DTST_VERBOSE
  CXXDEFINES += -DTST_VERBOSE
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

  ifeq ($(LNG),c)
    COMPILER=$(CC)
    COMPILERFLAGS=$(CFLAGS)
    LINKER=$(LD)
    LINKERFLAGS=$(LDFLAGS)
  else ifeq ($(LNG),cpp)
    COMPILER=$(CXX)
    COMPILERFLAGS=$(CXXFLAGS)
    LINKER=$(LDXX)
    LINKERFLAGS=$(LDXXFLAGS)
  else
    $(error Unknown language $(LNG). Please select from c or cpp.)
  endif
endif
$(BIN_DIR)/%-$(LNG)$(DEBUGPOSTFIX).o: %.$(LNG) | $(BIN_DIR)
	$(COMPILER) $(COMPILERFLAGS) -o $@ -c $<

TST_SRC=$(TST_DIR)/$(LNG)/$(STR)-tst.$(LNG)
IMP_SRC=$(SRC_DIR)/$(STR)/$(LNG)/$(STR)-$(IMP).$(LNG)
SRC=$(TST_SRC) $(IMP_SRC)
OBJ=$(patsubst %.$(LNG),$(BIN_DIR)/%-$(LNG)$(DEBUGPOSTFIX).o,$(notdir $(SRC)))
EXE=$(BIN_DIR)/$(STR)-$(IMP)-$(LNG)$(DEBUGPREFIX)-tst
$(EXE): $(OBJ)
	$(LINKER) $(LINKERFLAGS) -o $@ $^

.PHONY: test
test: $(EXE)
	./$(EXE)
