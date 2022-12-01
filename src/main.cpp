//////////////////////////////////////////////////////////////////////////////////
// Author: Geo Gonzalez
//  Name: main.cpp
//  Date: November 28th 2022
//  Description: This is the main file for Project 4, building an Assembly
//  Language Interpreter in C++.
//////////////////////////////////////////////////////////////////////////////////
#include "ALI.h"
#include "Instructions.h"
#include "algorithm"
#include <cctype>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

// TODO: Make readme.md file for graders

// Function for trimming the whitespace off of strings
std::string &rtrim(std::string &givenString,
				   const char *terminatingChar = " \t\n\r\f\v") {
	givenString.erase(givenString.find_last_not_of(terminatingChar) + 1);
	return givenString;
}

int main() {
	// Tell user to give input
	std::cout << "Please provide the file name for the file you'd like to work "
				 "with: ";
	std::string input;
	// Get their input
	std::cin >> input;
	// Trim white space if present
	input = rtrim(input);
	// Check if folder exists for test files
	std::ifstream f(("tests/" + input).c_str());
	if (f.good()) {
		input = "tests/" + input;
	}
	// Should now have correct folder of file
	ALI mem;

	std::ifstream input_file(input);
	if (!input_file.is_open()) {
		std::cerr << "Could not open file '" << input << "'" << std::endl;
		return EXIT_FAILURE;
	}

	// Populate the program array with instructions
	std::string line;
	int i = 0;
	while (i <= 127 && getline(input_file, line)) {
		mem.internalProgramArray[i] = parseInstruction(line, mem);
		i += 1;
	}

	// Main Loop
	while (!mem.reachedEnd()) {
		// First print the memory structure
		mem.print();
		// Now print the command options
		std::cout << "s - Execute a single line of code, starting from the "
					 "instruction at memory address 0; update the PC, the "
					 "registers and memory according to the instruction; and "
					 "print the value of the registers, the zero bit, the "
					 "overflow bit, and only the memory locations that store "
					 "source code or program data after the line is executed."
				  << std::endl;
		std::cout << "a - Execute all the instructions until a halt "
					 "instruction is encountered or there are no more "
					 "instructions to be executed. The program's source code "
					 "and data used by the program are printed."
				  << std::endl;
		std::cout << "q - Quit the command loop." << std::endl;
		std::cout << "\nPlease input your command: ";
		// Get user command
		std::string cmd;
		std::cin >> cmd;
		cmd = rtrim(cmd);

		// Execute the user's wish
		if (cmd == "s") {
			mem.executeSingle();
		} else if (cmd == "a") {
			while (!mem.reachedEnd()) {
				mem.executeSingle();
				if (mem.loopWarn) {
					std::cout << mem.curhc
							  << " lines have been run so far, there might be "
								 "an endless loop. Continue? y/n: ";
					std::string response;
					std::cin >> response;
					response = rtrim(response);
					std::transform(
						response.begin(), response.end(), response.begin(),
						[](unsigned char c) { return std::tolower(c); });
					if (response == "n") {
						break;
					} else {
						mem.prevhc = mem.curhc;
						mem.loopWarn = false;
					}
				}
			}
			mem.print();
			break;
		} else if (cmd == "q") {
			break;
		} else {
			std::cout << "Invalid command! Please try again." << std::endl;
		}
	}
	// Program is ending, say goodbye to user
	if (mem.pc > 127) {
		std::cout << "Reached end of source file, ";
	} else if (mem.pc < 0) {
		std::cout << "Halt command was encountered, ";
	}
	std::cout << "Exiting Project 4, goodbye!" << std::endl;
}