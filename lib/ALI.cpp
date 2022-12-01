#include "ALI.h"
#include "Instructions.h"
#include <iostream>
#include <string>
#include <unordered_map>

// Constructor
ALI::ALI() {
	internalProgramArray = new Instruction *[128];
	for (int i = 0; i < 128; i++) {
		internalProgramArray[i] = nullptr;
	}
	internalDataArray = new std::string[128];
	registerA = registerB = pc = zeroResultBit = overflowBit = prevhc = curhc =
		0;
	mc = 0;
	symbolAddresses = new std::unordered_map<std::string, int>;
	loopWarn = false;
}
// Destructor
ALI::~ALI() {
	for (int i = 0; i < 128; i++) {
		delete internalProgramArray[i];
	}
	delete[] internalProgramArray;
	delete[] internalDataArray;
	delete symbolAddresses;
}

// Executing a single line of instruction
void ALI::executeSingle() {
	internalProgramArray[pc]->execute();
	curhc += 1;
	if (prevhc + 1000 == curhc) {
		loopWarn = true;
	}
}

// Check if pc is beyond its bounds, if so an end has been reached
bool ALI::reachedEnd() {
	if (pc >= 128 || pc < 0)
		return true;
	return false;
}

// Allow ALI to be printed to console
void ALI::print() {
	// DONE: implement printing ALI

	// Print instructions first
	std::cout << _title("Instructions", '-');
	for (int i = 0; i < 128; i++) {
		if (this->internalProgramArray[i] != nullptr) {
			std::cout << std::to_string(i) << ". ";
			internalProgramArray[i]->print();
			if (i == this->pc) {
				std::cout << "      <===== PC is currently here";
			}
			std::cout << std::endl;
		}
	}
	// Print data section next
	std::cout << _title("Memory", '-');
	if (this->mc > 0) {
		for (int i = 0; i < this->mc; i++) {
			std::cout << std::to_string(i + 128) + ". " +
							 this->internalDataArray[i]
					  << std::endl;
		}
	} else {
		std::cout << _title("Memory is currently empty.", ' ');
	}

	// Print Bits and registers
	std::cout << _title("Bits & Regs", '-');
	std::cout << "zeroResultBit = " << std::to_string(this->zeroResultBit)
			  << std::endl;
	std::cout << "overflowBit = " << std::to_string(this->overflowBit)
			  << std::endl;
	std::cout << "registerA = " << std::to_string(this->registerA) << std::endl;
	std::cout << "registerB = " << std::to_string(this->registerB) << std::endl;
	std::cout << _title("Symbol Table", '-');
	std::cout << printSymbolMap(*(this->symbolAddresses));
	std::cout << std::endl;
}

// DONE: Implement _title
std::string ALI::_title(std::string s, char delimiter) {
	int sidelength = (50 - s.length()) / 2;
	std::string side = std::string(sidelength, delimiter);
	return side + s + side + "\n";
}
// DONE: Implement printing symbols
std::string ALI::printSymbolMap(std::unordered_map<std::string, int> map) {
	std::string s;
	for (auto &pair : map) {
		s += "{" + pair.first + ": " + std::to_string(pair.second) + "}\n";
	}
	return s;
}