MODULES := $(notdir $(wildcard modules/*))

MAKE_CPP_MODULE := $(MAKE) --no-print-directory -f ../../mk/module.cpp.mk

BUILD := build

all: calcs build
	@:

include mk/tools.build.mk
include mk/external.gtest.mk
include mk/calcs.latex.mk

.PHONY: calcs
calcs: build/calcs.pdf
	@:

test: build/testrunner
	@build/testrunner

$(BUILD)/testrunner: build build-test
	@mkdir -p build
	@$(CXX) $(wildcard $(BUILD)/testobjs/**/*.o) -o $@ $(GTEST_LINK) -L$(BUILD) $(addprefix -l,$(MODULES))

test2: build/test2
	@build/test2

build/test2: build test.cpp
	@mkdir -p build
	@$(CXX) test.cpp -o $@ -L$(BUILD) $(addprefix -l,$(MODULES))

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
	@rm -rf build doc

.PHONY: doc
doc: prepare
	@doxygen -s
	@find doc -type f -iname '*.html' -exec sed -i -r "s/<div class=\"fragment\"(.*?);(.*?)\{/<div class=\"fragment\"\\1;\{/g" {} +;

define PROCESS_CPP_MODULE
$(eval $@_TASK := $1)
$(eval $@_MOD := $(subst $($@_TASK)-,,$@))
@+$(MAKE_CPP_MODULE) -C modules/$($@_MOD) $($@_TASK) MODULE=$($@_MOD)
endef
