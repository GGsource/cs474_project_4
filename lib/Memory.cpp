#include "Memory.h"
#include "Instructions.h"
#include <iostream>
#include <string>
#include <unordered_map>

// Constructor
Memory::Memory() {
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
Memory::~Memory() {
	for (int i = 0; i < 128; i++) {
		delete internalProgramArray[i];
	}
	delete[] internalProgramArray;
	delete[] internalDataArray;
	delete symbolAddresses;
}

// Executing a single line of instruction
void Memory::executeSingle() {
	internalProgramArray[pc]->execute();
	curhc += 1;
	if (prevhc + 1000 == curhc) {
		loopWarn = true;
	}
}

// Check if pc is beyond its bounds, if so an end has been reached
bool Memory::reachedEnd() {
	if (pc >= 128 || pc < 0)
		return true;
	return false;
}

// Allow memory to be printed to console
std::string Memory::to_s() {
	// DONE: implement printing memory

	// Print instructions first
	std::string returnString = _title("Instructions", '-');
	for (int i = 0; i < 128; i++) {
		if (this->internalProgramArray[i] != nullptr) {
			returnString +=
				std::to_string(i) + ". " + internalProgramArray[i]->to_s();
			if (i == this->pc) {
				returnString += "      <===== PC is currently here";
			}
			returnString += "\n";
		}
	}
	// Print data section next
	returnString += _title("Memory", '-');
	if (this->mc > 0) {
		for (int i = 0; i < this->mc; i++) {
			returnString += std::to_string(i + 128) + ". " +
							this->internalDataArray[i] + "\n";
		}
	} else {
		returnString += _title("Memory is currently empty.", ' ');
	}

	// Print Bits and registers
	returnString += _title("Bits & Regs", '-');
	returnString +=
		"zeroResultBit = " + std::to_string(this->zeroResultBit) + "\n";
	returnString += "overflowBit = " + std::to_string(this->overflowBit) + "\n";
	returnString += "registerA = " + std::to_string(this->registerA) + "\n";
	returnString += "registerB = " + std::to_string(this->registerB) + "\n";
	returnString += _title("Symbol Table", '-');
	returnString += printSymbolMap(*(this->symbolAddresses));

	return returnString;
}

// DONE: Implement _title
std::string Memory::_title(std::string s, char delimiter) {
	int sidelength = (50 - s.length()) / 2;
	std::string side = std::string(sidelength, delimiter);
	return side + s + side + "\n";
}
// DONE: Implement printing symbols
std::string Memory::printSymbolMap(std::unordered_map<std::string, int> map) {
	std::string s;
	for (auto &pair : map) {
		s += "{" + pair.first + ": " + std::to_string(pair.second) + "}\n";
	}
	return s;
}