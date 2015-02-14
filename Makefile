MODULES := $(notdir $(wildcard modules/*))

MAKE_CPP := $(MAKE) --no-print-directory -f ../../Makefile.cpp.mk

all: prepare
	@:

prepare: $(addprefix prepare-,$(MODULES))

clean: $(addprefix clean-,$(MODULES))
	@rm -rf build

prepare-%:
	$(eval $@_TASK := prepare)
	$(eval $@_MOD := $(subst $($@_TASK)-,,$@))
	@echo [$($@_TASK)] $($@_MOD)
	@$(MAKE_CPP) -C modules/$($@_MOD) $($@_TASK) MODULE=$($@_MOD)

clean-%:
	$(eval $@_TASK := clean)
	$(eval $@_MOD := $(subst $($@_TASK)-,,$@))
	@echo [$($@_TASK)] $($@_MOD)
	@$(MAKE_CPP) -C modules/$($@_MOD) $($@_TASK) MODULE=$($@_MOD)

