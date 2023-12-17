ifeq ($(OS),Windows_NT)
	COMPILATION = g++ .\src\main.cpp .\src\Instructions.cpp .\src\ALI.cpp -Isrc -o project4.exe
	COMP_RUN = project4.exe
	CLEAN = rm -force -recurse -verbose *.exe
else
	COMPILATION = g++ ./src/main.cpp ./src/Instructions.cpp ./src/ALI.cpp -Isrc -o project4.exe
	COMP_RUN = ./project4.exe
	CLEAN = rm -rfv *.exe

all: compile run

compile:
	$(COMPILATION)
run:
	$(COMP_RUN)

clean:
	$(CLEAN)

endif