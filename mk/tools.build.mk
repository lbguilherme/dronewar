
CXXFLAGS = -g -std=c++14 -pedantic -stdlib=libc++ -Wall -Wextra -Wshadow

INC := -I$(BUILD)/include -I$(BUILD)/external/include
CXX := clang++ $(CXXFLAGS) -fdiagnostics-color=auto $(INC) -DDEBUG
AR := ar rcs
