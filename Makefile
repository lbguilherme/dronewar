MODULES := $(notdir $(wildcard modules/*))

MAKE_CPP_MODULE := $(MAKE) --no-print-directory -f ../../mk/module.cpp.mk

BUILD := build
CXX := clang++ -g -std=c++14 -fdiagnostics-color=auto

all: build
	@:

test: build/testrunner
	@build/testrunner

$(BUILD)/testrunner: $(addprefix build-test-,$(MODULES)) $(LIBGTEST) 
	@mkdir -p build
	@$(CXX) $(wildcard $(BUILD)/testobjs/**/*.o) -o $@ $(GTEST_LINK) -L$(BUILD) $(addprefix -l,$(MODULES))

build-test-%:
	$(call PROCESS_CPP_MODULE,build-test)

build: $(addprefix build-,$(MODULES))
	@:

build-%:
	$(call PROCESS_CPP_MODULE,build)

prepare: $(addprefix prepare-,$(MODULES))
	@:

prepare-%:
	$(call PROCESS_CPP_MODULE,prepare)

clean: $(addprefix clean-,$(MODULES))
	@rm -rf build

clean-%:
	$(call PROCESS_CPP_MODULE,clean)

.PHONY: doc
doc:
	@rm -rf doc
	@doxygen -s

include mk/external.gtest.mk

define PROCESS_CPP_MODULE
$(eval $@_TASK := $1)
$(eval $@_MOD := $(subst $($@_TASK)-,,$@))
@$(MAKE_CPP_MODULE) -C modules/$($@_MOD) $($@_TASK) MODULE=$($@_MOD)
endef

