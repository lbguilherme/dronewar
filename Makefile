MODULES := $(notdir $(wildcard modules/*))

MAKE_CPP_MODULE := $(MAKE) --no-print-directory -f ../../mk/module.cpp.mk

BUILD := build
CXX := clang++ -g -std=c++14 -fdiagnostics-color=auto -DDEBUG

all: build
	@:

include mk/external.gtest.mk

test: build/testrunner
	@build/testrunner

$(BUILD)/testrunner: build build-test
	@mkdir -p build
	@$(CXX) $(wildcard $(BUILD)/testobjs/**/*.o) -o $@ $(GTEST_LINK) -L$(BUILD) $(addprefix -l,$(MODULES))

build-test: $(addprefix build-test-,$(MODULES))
	@:

build-test-%: $(LIBGTEST) build-%
	$(call PROCESS_CPP_MODULE,build-test)

build: $(addprefix build-,$(MODULES))
	@:

build-%:
	$(call PROCESS_CPP_MODULE,build)

prepare: $(addprefix prepare-,$(MODULES))
	@:

prepare-%:
	$(call PROCESS_CPP_MODULE,prepare)

clean:
	@rm -rf build

.PHONY: doc
doc:
	@rm -rf doc
	@doxygen -s

define PROCESS_CPP_MODULE
$(eval $@_TASK := $1)
$(eval $@_MOD := $(subst $($@_TASK)-,,$@))
@+$(MAKE_CPP_MODULE) -C modules/$($@_MOD) $($@_TASK) MODULE=$($@_MOD)
endef
