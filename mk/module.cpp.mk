.SECONDARY:

BUILD := ../../build
INCLUDES := $(wildcard include/*.hpp)
SRCS := $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
DEPS := $(patsubst src/%.cpp, $(BUILD)/deps/$(MODULE)/%.d, $(SRCS))
OBJS := $(patsubst src/%.cpp, $(BUILD)/objs/$(MODULE)/%.o, $(SRCS))
LIBRARY := $(BUILD)/lib$(MODULE).a

CXX = clang++ -g -std=c++14 -Wall -Wextra -I$(BUILD)/include -fdiagnostics-color=auto
AR = ar rcs

build: prepare check $(LIBRARY)
	@:

prepare: $(patsubst include/%.hpp,$(BUILD)/include/$(MODULE)/%,$(INCLUDES))
	@:
	
check: prepare $(patsubst include/%.hpp,$(BUILD)/include/$(MODULE)/%.hpp_checked,$(INCLUDES))
	@:

$(BUILD)/include/$(MODULE)/%: include/%.hpp $(BUILD)/include/$(MODULE)/%.hpp
	@echo "#pragma once" > $@
	@echo "#include \""$(notdir $<)"\"" >> $@

$(BUILD)/include/$(MODULE)/%.hpp: include/%.hpp
	@mkdir -p $(dir $@)
	@cp $< $(dir $@)

$(BUILD)/include/$(MODULE)/%.hpp_checked: include/%.hpp
	@echo "Checking  "$<" ..."
	@echo "#include <$(MODULE)/"$<">" > $@.cpp
	@cd .. && $(CXX) -Wno-pragmas -fsyntax-only -I$(MODULE)/$(BUILD)/include -I. $(MODULE)/$@.cpp
	@rm $@.cpp
	@touch $@

$(BUILD)/deps/$(MODULE)/%.d: src/%.cpp prepare
	@mkdir -p $(dir $@)
	@gcc -I$(BUILD)/include -nostdinc -MF$@ -MG -MM -MP -MT$@ -MT$(patsubst $(BUILD)/deps/$(MODULE)/%.d,$(BUILD)/objs/$(MODULE)/%.o,$@) $<

$(BUILD)/objs/$(MODULE)/%.o: src/%.cpp
	@echo "Compiling  "$@" ..."
	@mkdir -p $(dir $@)
	@$(CXX) -c $< -o $@

$(LIBRARY): $(OBJS)
	@echo "Creating   "$@" ..."
	@mkdir -p $(dir $@)
	@$(AR) $@ $^

-include $(DEPS)

clean:
	@rm -rf $(BUILD)/include/$(MODULE)

