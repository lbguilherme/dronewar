MODULES := $(notdir $(wildcard modules/*))

MAKE_CPP_MODULE := $(MAKE) --no-print-directory -f ../../mk/module.cpp.mk

all: build
	@:

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



define PROCESS_CPP_MODULE
$(eval $@_TASK := $1)
$(eval $@_MOD := $(subst $($@_TASK)-,,$@))
@$(MAKE_CPP_MODULE) -C modules/$($@_MOD) $($@_TASK) MODULE=$($@_MOD)
endef

