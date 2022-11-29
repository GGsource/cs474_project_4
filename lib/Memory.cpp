#include "Memory.h"
#include <unordered_map>

// Constructor
Memory::Memory() {
	registerA = registerB = pc = zeroResultBit = overflowBit = prevhc = curhc =
		0;
	mc = 128;
}

// index access operator
std::string Memory::operator[](int ndx) const { return internalArray[ndx]; }

// TESTME: does this assign properly?
//  index assignment operator
std::string &Memory::operator[](int ndx) { return internalArray[ndx]; }

void Memory::executeSingle() {
	// internalArray[pc].execute
	// internalArray in ruby held SAL class objects, and numbers.
	// TODO: Look into map that has items of different types.
}