//////////////////////////////////////////////////////////////////////////////////
// Author: Geo Gonzalez
//  Name: main.cpp
//  Date: November 28th 2022
//  Description: This is the main file for Project 4, building an Assembly
//  Language Interpreter in C++.
//////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <iostream>

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
}