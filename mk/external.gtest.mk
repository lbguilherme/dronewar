
LIBGTEST := $(BUILD)/external/gtest/libgtest.a
GTEST_LINK := -L$(BUILD)/external/gtest -lgtest -lgtest_main -pthread

gtest: $(LIBGTEST)

$(LIBGTEST):
	@echo "Building   gtest ..."
	@mkdir -p $(BUILD)/external/gtest
	@cd $(BUILD)/external/gtest && cmake ../../../external/gtest -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang > /dev/null
	@cd $(BUILD)/external/gtest && $(MAKE) > /dev/null
	@mkdir -p $(BUILD)/external/include
	@cp -r $(BUILD)/../external/gtest/include/gtest $(BUILD)/external/include

