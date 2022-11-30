#include "Instructions.h"
#include <cmath>
#include <string>

std::string SAL::to_s() {
	// TODO: Implement printing SAL
	return "print SAL was called...";
}
// TODO: SAL Needs a virtual destructor that derived classes can call

// DONE: DEC - Declares a symbolic variable & stores in memory
DEC::DEC(std::string givenSymbol, Memory &memory) {
	// FIXME: convert this to initialization list
	opCode = "DEC";
	argType = "STRING";
	arg = givenSymbol;
	mem = &memory;
}
void DEC::execute() {
	mem->internalDataArray[mem->mc] = "xxx";
	mem->symbolAddresses->at(arg) = mem->mc;
	mem->mc += 1;
	mem->pc += 1;
}
// DONE: LDX - LDA and LDB take given symbol value and store it in the register
LDX::LDX(std::string instruction, std::string givenSymbol, Memory &memory) {
	opCode = instruction;
	argType = "STRING";
	arg = givenSymbol;
	mem = &memory;
}
void LDX::execute() {
	if (opCode == "LDA") {
		mem->registerA =
			std::stoi(mem->internalDataArray[mem->symbolAddresses->at(arg)]);
	} else {
		mem->registerB =
			std::stoi(mem->internalDataArray[mem->symbolAddresses->at(arg)]);
	}
	mem->pc += 1;
}

// DONE: LDI - Loads the integer value into the accumulator register. The value
// could be negative
LDI::LDI(std::string givenVal, Memory &memory) {
	opCode = "LDI";
	argType = "NUMBER";
	mem = &memory;
	arg = givenVal;
}
void LDI::execute() {
	mem->registerA = std::stoi(arg);
	mem->pc += 1;
}

// DONE: STR - Stores content of accumulator into data memory at address of
// symbol.
STR::STR(std::string givenSymbol, Memory &memory) {
	opCode = "STR";
	argType = "STRING";
	arg = givenSymbol;
	mem = &memory;
}
void STR::execute() {
	mem->internalDataArray[mem->symbolAddresses->at(arg)] =
		std::to_string(mem->registerA);
	mem->pc += 1;
}

// DONE: XCH - Exchanges the content registers A and B.
XCH::XCH(Memory &memory) {
	opCode = "XCH";
	argType = "NONE";
	mem = &memory;
}
void XCH::execute() {
	int temp = mem->registerA;
	mem->registerA = mem->registerB;
	mem->registerB = temp;
	mem->pc += 1;
}

// DONE: JMP - Transfers control to instruction at address number in program
// memory.
JMP::JMP(std::string givenAddress, Memory &memory) {
	opCode = "JMP";
	argType = "NUMBER";
	mem = &memory;
	arg = givenAddress;
}
void JMP::execute() { mem->pc = std::stoi(arg); }

// DONE: JXS - JZS & JVS Transfer control to instruction at address number if
// the zero-result bit or overlfow bit is set respectively.
JXS::JXS(std::string givenAddress, std::string instruction, Memory &memory) {
	opCode = instruction;
	argType = "NUMBER";
	mem = &memory;
	arg = givenAddress;
}
void JXS::execute() {
	if ((opCode == "JZS" && mem->zeroResultBit == 1) ||
		(opCode == "JVS" && mem->overflowBit == 1)) {
		mem->pc = std::stoi(arg);
	} else {
		mem->pc += 1;
	}
}

// DONE: ADD - Adds registers A and B. Sum is stored in A. The overflow and
// zero-result bits are set or cleared
ADD::ADD(Memory &memory) {
	opCode = "ADD";
	argType = "NONE";
	mem = &memory;
}
void ADD::execute() {
	if ((mem->registerA + mem->registerB) > (pow(2, 31) - 1) ||
		(mem->registerA + mem->registerB) < -1 * (pow(2, 31))) {
		mem->overflowBit = 1;
	} else {
		mem->overflowBit = 0;
		mem->registerA += mem->registerB;
	}
	if (mem->registerA == 0) {
		mem->zeroResultBit = 1;
	} else {
		mem->zeroResultBit = 0;
	}
	mem->pc += 1;
}
// DONE: HLT - Terminates program execution.
HLT::HLT(Memory &memory) {
	opCode = "HLT";
	argType = "NONE";
	mem = &memory;
}
void HLT::execute() { mem->pc = -1; }

SAL *parseInstruction(std::string line, Memory &memory) {
	// TESTME: this part is likely to be wrong
	std::string instruction = line.substr(0, line.find(""));
	std::string arg = line.substr(line.find(""));

	if (instruction == "DEC") {
		return new DEC(arg, memory);
	} else if (instruction == "LDA" || instruction == "LDB") {
		return new LDX(instruction, arg, memory);
	} else if (instruction == "LDI") {
		return new LDI(arg, memory);

	} else if (instruction == "STR") {
		return new STR(arg, memory);

	} else if (instruction == "XCH") {
		return new XCH(memory);

	} else if (instruction == "JMP") {
		return new JMP(arg, memory);

	} else if (instruction == "JXS") {
		return new JXS(arg, instruction, memory);

	} else if (instruction == "ADD") {
		return new ADD(memory);
	} else if (instruction == "HLT") {
		return new HLT(memory);
	}
	return NULL;
}