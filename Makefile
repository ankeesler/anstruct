.PHONY:
all: test-all

#
# Building
#

CC = clang
CXX = clang++

CINCLUDES = -I. -Isrc/core
CDEFINES =
COPTIMIZE =
CFLAGS = -MD -Wall -Werror $(COPTIMIZE) $(CINCLUDES) $(CDEFINES)

CXXINCLUDES = -I. -Isrc/core
CXXDEFINES =
CXXOPTIMIZE =
CXXFLAGS = -MD -Wall -Werror $(CXXOPTIMIZE) $(CXXINCLUDES) $(CXXDEFINES)

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

ifdef OPTIMIZE
	COPTIMIZE += -Oz
	CXXOPTIMIZE += -Oz
endif
ifndef OPTIMIZE
	COPTIMIZE += -g -O0
	CXXOPTIMIZE += -g -O0
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

.PHONY: queue-array-cpp
queue-array-cpp:
	make test STR=queue IMP=array LNG=cpp

.PHONY: queue-array-c
queue-array-c:
	make test STR=queue IMP=array LNG=c

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

$(BIN_DIR)/%-$(LNG)$(DEBUGPOSTFIX).s: %.$(LNG) | $(BIN_DIR)
	$(COMPILER) $(COMPILERFLAGS) -o $@ -S $<

$(BIN_DIR)/%.o.nm: $(BIN_DIR)/%.o | $(BIN_DIR)
	nm -n $< > $@

$(BIN_DIR)/%.o.size: $(BIN_DIR)/%.o | $(BIN_DIR)
	size $< > $@

TST_SRC=$(TST_DIR)/$(LNG)/$(STR)-tst.$(LNG)
IMP_SRC=$(SRC_DIR)/$(STR)/$(LNG)/$(STR)-$(IMP).$(LNG)
SRC=$(TST_SRC) $(IMP_SRC)

BASEFILE=$(patsubst %.$(LNG),$(BIN_DIR)/%-$(LNG)$(DEBUGPOSTFIX).,$(notdir $(SRC)))
OBJ=$(patsubst %, %o, $(BASEFILE))
ASM=$(patsubst %, %s, $(BASEFILE))
NMS=$(patsubst %, %o.nm, $(BASEFILE))
SIZ=$(patsubst %, %o.size, $(BASEFILE))

EXE=$(BIN_DIR)/$(STR)-$(IMP)-$(LNG)$(DEBUGPREFIX)-tst
$(EXE): $(OBJ) | $(ASM) $(NMS) $(SIZ)
	$(LINKER) $(LINKERFLAGS) -o $@ $^

.PHONY: test
test: $(EXE)
	./$(EXE)

.PHONY: test-all
test-all:
	./test.sh