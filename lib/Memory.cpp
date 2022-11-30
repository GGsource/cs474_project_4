#include "Memory.h"
#include "Instructions.h"
#include <string>
#include <unordered_map>

// Constructor
Memory::Memory() {
	internalProgramArray = new SAL[128];
	internalDataArray = new std::string[128];
	registerA = registerB = pc = zeroResultBit = overflowBit = prevhc = curhc =
		0;
	mc = 0;
	symbolAddresses = new std::unordered_map<std::string, int>;
	loopWarn = false;
}

// Executing a single line of instruction
void Memory::executeSingle() {
	internalProgramArray[pc].execute();
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
	// TODO: implement printing memory
	return "called Memory's to_s...";
}

std::string Memory::_title() {
	// TODO: Implement _title
	return "called _title...";
}