all: compile run

compile:
	g++ .\src\main.cpp .\src\Instructions.cpp .\src\ALI.cpp -Isrc -o project4
run:
	project4

clean:
	erase *.exe