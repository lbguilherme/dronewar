
INC := -I$(BUILD)/include -I$(BUILD)/external/include
CXX := clang++ -g -std=c++14 -stdlib=libc++ -Wall -Wextra -Wshadow -fdiagnostics-color=auto $(INC) -DDEBUG
AR := ar rcs
