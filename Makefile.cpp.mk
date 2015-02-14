.SECONDARY:

BUILD := ../../build

INCLUDES := $(wildcard include/*.hpp)

all:
	@echo $(INCLUDES)

prepare: $(patsubst include/%.hpp,$(BUILD)/include/$(MODULE)/%,$(INCLUDES))
	@:
	
$(BUILD)/include/$(MODULE)/%: include/%.hpp $(BUILD)/include/$(MODULE)/%.hpp
	@echo "#pragma once" > $@
	@echo "#include \""$(notdir $<)"\"" >> $@

$(BUILD)/include/$(MODULE)/%.hpp: include/%.hpp
	@mkdir -p $(dir $@)
	@cp $< $(dir $@)

clean:
	@rm -rf $(BUILD)/include/$(MODULE)

