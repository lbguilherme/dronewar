.SECONDARY:

ROOT := ../..
BUILD := $(ROOT)/build
INCLUDES := $(wildcard include/*.hpp)

SRCS := $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
OBJS := $(patsubst src/%.cpp, $(BUILD)/objs/$(MODULE)/%.o, $(SRCS))

TESTS := $(wildcard test/*.cpp) $(wildcard test/**/*.cpp)
TESTOBJS := $(patsubst test/%.cpp, $(BUILD)/testobjs/$(MODULE)/%.o, $(TESTS))

DEPS := $(patsubst src/%.cpp, $(BUILD)/deps/$(MODULE)/%.d, $(SRCS)) $(patsubst test/%.cpp, $(BUILD)/testdeps/$(MODULE)/%.d, $(TESTS))

LIBRARY := $(BUILD)/lib$(MODULE).a

INC := -I$(BUILD)/include -I$(BUILD)/external/include
CXX := clang++ -g -std=c++14 -Wall -Wextra -Wshadow -fdiagnostics-color=auto $(INC) -DDEBUG
AR := ar rcs

include $(ROOT)/mk/external.gtest.mk

build: prepare check $(LIBRARY)
	@:

build-test: $(TESTOBJS)
	@:

prepare: $(patsubst include/%.hpp,$(BUILD)/include/$(MODULE)/%,$(INCLUDES))
	@:
	
check: prepare $(patsubst include/%.hpp,$(BUILD)/includecheck/$(MODULE)/%,$(INCLUDES))
	@:

$(BUILD)/include/$(MODULE)/%: include/%.hpp
	@mkdir -p $(dir $@)
	@echo "#pragma once" > $@
	@echo "#include \""$(ROOT)/modules/$(MODULE)/$<"\"" >> $@

$(BUILD)/includecheck/$(MODULE)/%: include/%.hpp
	@mkdir -p $(dir $@)
	@echo "Checking   "$(MODULE)/$<" ..."
	@echo "#include <$(MODULE)/"$<">" > $@.cpp
	@cd .. && $(CXX) -fsyntax-only -I$(MODULE)/$(BUILD)/include -I. $(MODULE)/$@.cpp
	@rm $@.cpp
	@touch $@

$(BUILD)/deps/$(MODULE)/%.d: src/%.cpp prepare
	@mkdir -p $(dir $@)
	@gcc -I$(BUILD)/include -nostdinc -MF$@ -MG -MM -MP -MT$@ -MT$(patsubst $(BUILD)/deps/$(MODULE)/%.d,$(BUILD)/objs/$(MODULE)/%.o,$@) $<

$(BUILD)/testdeps/$(MODULE)/%.d: test/%.cpp prepare
	@mkdir -p $(dir $@)
	@gcc -I$(BUILD)/include -nostdinc -MF$@ -MG -MM -MP -MT$@ -MT$(patsubst $(BUILD)/testdeps/$(MODULE)/%.d,$(BUILD)/testobjs/$(MODULE)/%.o,$@) $<

$(BUILD)/objs/$(MODULE)/%.o: src/%.cpp
	@echo "Compiling  "$(MODULE)/$<" ..."
	@mkdir -p $(dir $@)
	@$(CXX) -c $< -o $@

$(BUILD)/testobjs/$(MODULE)/%.o: test/%.cpp
	@echo "Compiling  "$(MODULE)/$<" ..."
	@mkdir -p $(dir $@)
	@$(CXX) -c $< -o $@

$(LIBRARY): $(OBJS)
	@echo "Creating   "$(notdir $@)" ..."
	@mkdir -p $(dir $@)
	@$(AR) $@ $^

-include $(DEPS)
