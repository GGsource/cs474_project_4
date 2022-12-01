all: compile run

tests: compile_tests run_tests

compile:
	g++ .\lib\main.cpp .\lib\Instructions.cpp .\lib\Memory.cpp -Ilib -o project4
run:
	project4

clean:
	erase *.exe