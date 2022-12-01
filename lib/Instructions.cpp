#include "Instructions.h"
#include <cmath>
#include <iostream>
#include <string>

// SAL Constructor
SAL::SAL(Memory &memory, std::string givenOpCode, std::string givenArgType,
		 std::string givenArg)
	: mem(&memory), opCode(givenOpCode), argType(givenArgType), arg(givenArg) {}

// DONE: Implement printing SAL
std::string SAL::to_s() {
	std::string s;

	if (!opCode.empty()) {
		s += opCode;
	};

	if (!arg.empty()) {
		s += " with " + argType + " argument of " + arg;
	}
	return s;
}
// TODO: SAL Needs a virtual destructor that derived classes can call
// TODO: Use valgrind to check for leaks

// DONE: DEC - Declares a symbolic variable & stores in memory
DEC::DEC(std::string givenSymbol, Memory &givenMemory)
	: SAL(givenMemory, "DEC", "STRING", givenSymbol) {}
void DEC::execute() {
	mem->internalDataArray[mem->mc] = "xxx";
	mem->symbolAddresses->at(arg) = mem->mc;
	mem->mc += 1;
	mem->pc += 1;
}
// DONE: LDX - LDA and LDB take given symbol value and store it in the register
LDX::LDX(std::string instruction, std::string givenSymbol, Memory &givenMemory)
	: SAL(givenMemory, instruction, "STRING", givenSymbol) {}
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
LDI::LDI(std::string givenVal, Memory &givenMemory)
	: SAL(givenMemory, "LDI", "NUMBER", givenVal) {}
void LDI::execute() {
	mem->registerA = std::stoi(arg);
	mem->pc += 1;
}

// DONE: STR - Stores content of accumulator into data memory at address of
// symbol.
STR::STR(std::string givenSymbol, Memory &givenMemory)
	: SAL(givenMemory, "STR", "STRING", givenSymbol) {}
void STR::execute() {
	mem->internalDataArray[mem->symbolAddresses->at(arg)] =
		std::to_string(mem->registerA);
	mem->pc += 1;
}

// DONE: XCH - Exchanges the content registers A and B.
XCH::XCH(Memory &givenMemory) : SAL(givenMemory, "XCH", "NONE", "") {}
void XCH::execute() {
	int temp = mem->registerA;
	mem->registerA = mem->registerB;
	mem->registerB = temp;
	mem->pc += 1;
}

// DONE: JMP - Transfers control to instruction at address number in program
// memory.
JMP::JMP(std::string givenAddress, Memory &givenMemory)
	: SAL(givenMemory, "JMP", "NUMBER", givenAddress) {}
void JMP::execute() { mem->pc = std::stoi(arg); }

// DONE: JXS - JZS & JVS Transfer control to instruction at address number if
// the zero-result bit or overlfow bit is set respectively.
JXS::JXS(std::string givenAddress, std::string instruction, Memory &givenMemory)
	: SAL(givenMemory, instruction, "NUMBER", givenAddress) {}
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
ADD::ADD(Memory &givenMemory) : SAL(givenMemory, "ADD", "NONE", "") {}
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
HLT::HLT(Memory &givenMemory) : SAL(givenMemory, "HLT", "NONE", "") {}
void HLT::execute() { mem->pc = -1; }

SAL *parseInstruction(std::string line, Memory &memory) {
	std::string instruction = line.substr(0, 3);
	std::string arg = line.substr(3);

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

	} else if (instruction == "JZS" || instruction == "JVS") {
		return new JXS(arg, instruction, memory);

	} else if (instruction == "ADD") {
		return new ADD(memory);
	} else if (instruction == "HLT") {
		return new HLT(memory);
	}
	return nullptr;
}