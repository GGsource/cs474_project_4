#include "Instructions.h"
#include "Memory.h"

std::string SAL::to_s() {
	// TODO: Implement printing SAL
	return "print SAL was called...";
}
// TODO: SAL Needs a virtual destructor that derived classes can call

DEC::DEC(std::string givenSymbol, Memory &memory) {
	// FIXME: MOVE THIS TO INITIALIZATION LIST
	opCode = "DEC";
	argType = "STRING";
	arg = givenSymbol;
	symbol = givenSymbol;
	mem = &memory;
}

void DEC::execute() {
	mem->internalDataArray[mem->mc] = "xxx";
	mem->symbolAddresses->at(symbol) = mem->mc;
	mem->mc += 1;
	mem->pc += 1;
}