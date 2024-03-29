# CS 474's Project 4: Assembly Language Interpreter

## Author: Geo Gonzalez

##### Finished: 12/01/2022

## Project Description
An interpreter program that takes in a file with a series of Assembly Language commands and executes them while displaying changes in all the proper registers as each line is executed.   

## Folder Structure Explanation:

> src folder - Contains the main .h and .cpp files needed to run the project. Main.cpp depends on the others.

> tests folder - Contains all SAL instruction files used to test the project.

> utils folder - Contains assignment PDF.

## Root level files

> .clang-format & gitignore - irrelevant to the program's running, used only locally.

> makefile - simple and easy way to run project with just a single word.

## How to run project:

### Option A
1. Using Docker, open project in Dev Container. Type `make` in command line to run project.

### Option B

1. If make is intalled on the local machine, simply typing `make` on the command line will run the project.
2. If make is not installed but chocolatey package manager is, make can be installed with `choco install make`.
3. pass a valid file name when prompted. The file may be located in the `tests` folder or it may simply be in the `root directory`.

### Option C

1. If neither of the above is an option, the project can be compiled directly by typing the following on the command line: `g++ .\src\main.cpp .\src\Instructions.cpp .\src\ALI.cpp -Isrc -o project4.exe`.
2. Now that it is compiled, do `.\project4.exe` to run the compiled file.
3. pass a valid file name when prompted. The file may be located in the `tests` folder or it may simply be in the `root directory`.

Commands for using the Assembly Language Interpreter calculator are presented when the program begins and after every loop.
