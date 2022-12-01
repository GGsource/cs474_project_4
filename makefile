all: compile run

tests: compile_tests run_tests

compile:
	g++ .\lib\main.cpp .\lib\Instructions.cpp .\lib\Memory.cpp -Wall -o output.exe
run:
	output.exe

clean:
	erase *.exe