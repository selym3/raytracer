LIBS     := -lsfml-graphics -lsfml-window -lsfml-system
FLAGS    := -O3 -std=c++20
COMPILER := clang++


all:
	$(COMPILER) ${FLAGS) $(LIBS) main.cpp -o ./bin/main
	