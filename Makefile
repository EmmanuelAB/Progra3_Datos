all:
	g++ *.cpp
run:
	@./a.out
leaks:
	@valgrind --leak-check=full --show-leak-kinds=all ./a.out
doxy:
	doxygen doxyfile
